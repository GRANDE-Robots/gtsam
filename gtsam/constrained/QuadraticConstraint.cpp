/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation,
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file    QuadraticConstraint.cpp
 * @brief   Quadratic constraint implementations.
 * @author  Frank Dellaert
 */

#include <gtsam/base/GenericValue.h>
#include <gtsam/constrained/QuadraticConstraint.h>
#include <gtsam/nonlinear/Values.h>

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace gtsam {
namespace {

/* ************************************************************************* */
double SenseSign(QuadraticConstraint::Sense sense) {
  return sense == QuadraticConstraint::Sense::GreaterEqual ? -1.0 : 1.0;
}

/* ************************************************************************* */
Matrix VectorOrMatrixAsMatrix(const Values& values, Key key) {
  const Value& value = values.at(key);
  if (const auto* vectorValue =
          dynamic_cast<const GenericValue<Vector>*>(&value)) {
    return vectorValue->value();
  }
  if (const auto* matrixValue =
          dynamic_cast<const GenericValue<Matrix>*>(&value)) {
    return matrixValue->value();
  }
  throw std::invalid_argument(
      "QuadraticConstraint: only Vector and Matrix Values entries are "
      "supported.");
}

/* ************************************************************************* */
Vector ConstraintError(const QuadraticConstraint& constraint,
                       const Values& values, OptionalMatrixVecType H) {
  std::vector<Matrix> blocks;
  DenseIndex totalRows = 0;
  DenseIndex columns = 0;
  for (Key key : constraint.keys()) {
    Matrix block = VectorOrMatrixAsMatrix(values, key);
    if (columns && block.cols() != columns) {
      throw std::invalid_argument("QuadraticConstraint: column counts differ.");
    }
    columns = block.cols();
    totalRows += block.rows();
    blocks.push_back(std::move(block));
  }
  if (totalRows != constraint.A().rows()) {
    throw std::invalid_argument(
        "QuadraticConstraint: stacked value dimension does not match A.");
  }
  Matrix X(totalRows, columns);
  DenseIndex offset = 0;
  for (const Matrix& block : blocks) {
    X.middleRows(offset, block.rows()) = block;
    offset += block.rows();
  }
  const Matrix AX = constraint.A() * X;
  const double sign = SenseSign(constraint.sense());
  if (H) {
    H->resize(blocks.size());
    const Matrix gradient =
        sign * (constraint.A() + constraint.A().transpose()) * X;
    offset = 0;
    for (size_t index = 0; index < blocks.size(); ++index) {
      const Matrix blockGradient =
          gradient.middleRows(offset, blocks[index].rows());
      const Eigen::Map<const Vector> vectorized(blockGradient.data(),
                                                blockGradient.size());
      (*H)[index] = vectorized.transpose();
      offset += blocks[index].rows();
    }
  }
  return Vector1(sign * ((X.transpose() * AX).trace() - constraint.b()));
}

}  // namespace

/* ************************************************************************* */
QuadraticConstraint::QuadraticConstraint(const KeyVector& keys, const Matrix& A,
                                         double b, Sense sense, double sigma)
    : keys_(keys), A_(A), b_(b), sense_(sense), sigma_(sigma) {
  if (keys_.empty()) {
    throw std::invalid_argument("QuadraticConstraint: keys must not be empty.");
  }
  KeyVector sorted = keys_;
  std::sort(sorted.begin(), sorted.end());
  if (std::adjacent_find(sorted.begin(), sorted.end()) != sorted.end()) {
    throw std::invalid_argument("QuadraticConstraint: keys must be unique.");
  }
  if (A_.rows() != A_.cols()) {
    throw std::invalid_argument("QuadraticConstraint: A must be square.");
  }
  if (sigma_ <= 0.0) {
    throw std::invalid_argument("QuadraticConstraint: sigma must be positive.");
  }
}

/* ************************************************************************* */
NonlinearInequalityConstraint::shared_ptr
QuadraticConstraint::createInequalityFactor() const {
  if (isEquality()) {
    throw std::invalid_argument(
        "QuadraticConstraint: equality constraints cannot create inequality "
        "factors.");
  }
  return std::make_shared<QuadraticInequalityConstraintFactor>(*this);
}

/* ************************************************************************* */
Vector QuadraticEqualityConstraintFactor::unwhitenedError(
    const Values& values, OptionalMatrixVecType H) const {
  return ConstraintError(constraint_, values, H);
}

/* ************************************************************************* */
Vector QuadraticInequalityConstraintFactor::unwhitenedExpr(
    const Values& values, OptionalMatrixVecType H) const {
  return ConstraintError(constraint_, values, H);
}

}  // namespace gtsam

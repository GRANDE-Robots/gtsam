/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation,
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file    AugmentedLagrangianOptimizer.cpp
 * @brief   Augmented Lagrangian method for nonlinear constrained optimization.
 * @author  Yetong Zhang
 * @author  Frank Dellaert (codex assisted)
 * @date    Aug 3, 2024
 */

#include <gtsam/constrained/AugmentedLagrangianOptimizer.h>
#include <gtsam/constrained/QuadraticConstraint.h>
#include <gtsam/base/GenericValue.h>
#include <gtsam/linear/HessianFactor.h>
#include <gtsam/linear/GaussianFactorGraph.h>
#include <gtsam/constrained/QpCost.h>
#include <typeinfo>
#include <gtsam/nonlinear/NonlinearMultifrontalSolver.h>
#include <gtsam/constrained/LinearConstraint.h>
#include <gtsam/nonlinear/internal/LevenbergMarquardtState.h>
#include <gtsam/linear/linearExceptions.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <stdexcept>

using std::cout, std::endl, std::setprecision, std::setw;

namespace gtsam {
namespace {

void RequireFinite(double value) {
  if (!std::isfinite(value)) {
    throw std::runtime_error(
        "AugmentedLagrangianOptimizer encountered a nonfinite evaluation");
  }
}

void RequireFinite(const Vector& vector) {
  if (!vector.allFinite()) {
    throw std::runtime_error(
        "AugmentedLagrangianOptimizer encountered a nonfinite vector");
  }
}

void RequireFiniteJacobians(gtsam::OptionalMatrixVecType jacobians) {
  if (jacobians) {
    for (const Matrix& jacobian : *jacobians) {
      if (!jacobian.allFinite()) {
        throw std::runtime_error(
            "AugmentedLagrangianOptimizer encountered a nonfinite Jacobian");
      }
    }
  }
}

/**
 * Preserve exact quadratic-constraint curvature in the LM local model.
 * Gauss--Newton drops residual*Hessian(h), material for affine epigraph
 * objectives. Error and gradient stay unchanged; LM damps and accepts its
 * step against the actual nonlinear merit function.
 */
GaussianFactor::shared_ptr AddQuadraticCurvature(
    const GaussianFactor::shared_ptr& gaussian,
    const QuadraticConstraint& constraint, const Values& values,
    double coefficient) {
  HessianFactor base(*gaussian);
  Matrix augmented = base.augmentedInformation();
  std::vector<DenseIndex> rows, columns, dimensions;
  for (Key key : constraint.keys()) {
    const Value& value = values.at(key);
    if (const auto* vector = dynamic_cast<const GenericValue<Vector>*>(&value)) {
      rows.push_back(vector->value().size());
      columns.push_back(1);
    } else if (const auto* matrix =
                   dynamic_cast<const GenericValue<Matrix>*>(&value)) {
      rows.push_back(matrix->value().rows());
      columns.push_back(matrix->value().cols());
    } else {
      throw std::invalid_argument("quadratic curvature needs vector/matrix values");
    }
    dimensions.push_back(rows.back() * columns.back());
  }
  DenseIndex rowOffset = 0, valueRowOffset = 0;
  for (size_t i = 0; i < rows.size(); ++i) {
    DenseIndex colOffset = 0, valueColOffset = 0;
    for (size_t j = 0; j < rows.size(); ++j) {
      if (columns[i] != columns[j])
        throw std::invalid_argument("quadratic curvature column counts differ");
      const Matrix block =
          constraint.A().block(rowOffset, colOffset, rows[i], rows[j]) +
          constraint.A().block(colOffset, rowOffset, rows[j], rows[i]).transpose();
      for (DenseIndex column = 0; column < columns[i]; ++column)
        augmented.block(valueRowOffset + column * rows[i],
                        valueColOffset + column * rows[j], rows[i], rows[j]) +=
            coefficient * block;
      colOffset += rows[j];
      valueColOffset += dimensions[j];
    }
    rowOffset += rows[i];
    valueRowOffset += dimensions[i];
  }
  std::vector<Matrix> blocks;
  std::vector<Vector> linear;
  DenseIndex offset = 0;
  for (size_t i = 0; i < dimensions.size(); ++i) {
    DenseIndex second = offset;
    for (size_t j = i; j < dimensions.size(); ++j) {
      blocks.push_back(augmented.block(
          offset, second, dimensions[i], dimensions[j]));
      second += dimensions[j];
    }
    linear.push_back(augmented.block(offset, valueRowOffset, dimensions[i], 1));
    offset += dimensions[i];
  }
  return std::make_shared<HessianFactor>(
      constraint.keys(), blocks, linear, augmented(valueRowOffset, valueRowOffset));
}

/**
 * A factor that adds a constant bias term to an original factor's unwhitened
 * error. The augmented Lagrangian uses this to represent the equality term
 *
 *   lambda^T h(x) + (rho / 2) ||h(x)||^2
 *     = (rho / 2) ||h(x) + lambda / rho||^2
 *       - ||lambda||^2 / (2 rho).
 *
 * The noise model remains attached to both the original factor and this
 * wrapper. Only this wrapper's noise model is applied to the biased residual;
 * evaluating originalFactor_->unwhitenedError does not apply the original
 * factor's noise model a second time.
 */
class BiasedFactor : public NoiseModelFactor {
 protected:
  using Base = NoiseModelFactor;
  using This = BiasedFactor;

  // Original factor whose raw error and Jacobians are reused.
  Base::shared_ptr originalFactor_;
  Vector bias_;

 public:
  using shared_ptr = std::shared_ptr<This>;

  /// Default constructor for I/O only.
  BiasedFactor() = default;

  /**
   * Construct a biased view of an existing factor.
   *
   * @param originalFactor Original factor on x.
   * @param bias Constant added to its unwhitened error.
   */
  BiasedFactor(const Base::shared_ptr& originalFactor, const Vector& bias)
      : Base(originalFactor->noiseModel(), originalFactor->keys()),
        originalFactor_(originalFactor),
        bias_(bias) {}

  /**
   * Error function *without* the noise model, conventionally z-h(x). Override
   * this method to finish implementing an N-way factor. If the optional
   * argument is specified, it also computes the derivatives in `jacobians`.
   * Here the result is the original factor's unwhitened error plus the fixed
   * bias, and the Jacobians are unchanged because the bias is constant.
   */
  Vector unwhitenedError(
      const Values& values,
      gtsam::OptionalMatrixVecType jacobians = nullptr) const override {
    Vector error = originalFactor_->unwhitenedError(values, jacobians);
    RequireFinite(error);
    RequireFiniteJacobians(jacobians);
    error += bias_;
    RequireFinite(error);
    return error;
  }

  GaussianFactor::shared_ptr linearize(const Values& values) const override {
    auto gaussian = Base::linearize(values);
    const auto* quadratic =
        dynamic_cast<const QuadraticEqualityConstraintFactor*>(originalFactor_.get());
    if (!quadratic) return gaussian;
    const double sigma = noiseModel()->sigmas()(0);
    const double coefficient = unwhitenedError(values)(0) / (sigma * sigma);
    return AddQuadraticCurvature(
        gaussian, quadratic->quadraticConstraint(), values, coefficient);
  }

  /// Print the biased factor.
  void print(const std::string& label, const KeyFormatter& keyFormatter =
                                           DefaultKeyFormatter) const override {
    cout << label << "BiasedFactor " << bias_.transpose()
         << " version of:" << endl;
    originalFactor_->print(label, keyFormatter);
  }

  /// Return a deep copy.
  NonlinearFactor::shared_ptr clone() const override {
    return std::static_pointer_cast<NonlinearFactor>(
        NonlinearFactor::shared_ptr(new This(*this)));
  }
};

/**
 * Least-squares factor for a scalar Powell--Hestenes--Rockafellar (PHR)
 * inequality augmented Lagrangian. For a whitened inequality g(x) <= 0,
 * nonnegative multiplier lambda, and direct penalty rho > 0, the PHR term is
 *
 *   [max(0, lambda + rho g(x))^2 - lambda^2] / (2 rho).
 *
 * The second term is constant in x, so LM can minimize the equivalent residual
 *
 *   r(x) = max(0, lambda + rho g(x)) / sqrt(rho).
 *
 * See Nocedal and Wright, Numerical Optimization, 2nd ed., Chapter 17, for the
 * PHR inequality augmented Lagrangian and projected multiplier update.
 */
class PhrInequalityFactor : public NoiseModelFactor {
 protected:
  using Base = NoiseModelFactor;
  using This = PhrInequalityFactor;

  NonlinearInequalityConstraint::shared_ptr constraint_;
  double lambda_;
  double penalty_;

 public:
  /// Construct a scalar PHR factor at fixed multiplier and direct penalty.
  PhrInequalityFactor(
      const NonlinearInequalityConstraint::shared_ptr& constraint,
      double lambda, double penalty)
      : Base(noiseModel::Unit::Create(1), constraint->keys()),
        constraint_(constraint),
        lambda_(lambda),
        penalty_(penalty) {
    if (constraint_->dim() != 1) {
      throw std::invalid_argument(
          "AugmentedLagrangianOptimizer supports scalar inequalities only");
    }
  }

  /// Evaluate the exact shifted-ramp residual and its piecewise Jacobians.
  Vector unwhitenedError(
      const Values& values,
      gtsam::OptionalMatrixVecType jacobians = nullptr) const override {
    Vector expression;
    if (jacobians) {
      // Convert both g and dg/dx to whitened constraint coordinates so sigma
      // provides the same fixed scaling in the merit function and diagnostics.
      expression = constraint_->unwhitenedExpr(values, jacobians);
      RequireFinite(expression(0));
      RequireFiniteJacobians(jacobians);
      constraint_->noiseModel()->WhitenSystem(*jacobians, expression);
    } else {
      expression = constraint_->unwhitenedExpr(values);
      RequireFinite(expression(0));
      expression = constraint_->whitenedExpr(values);
    }

    RequireFinite(expression(0));
    RequireFiniteJacobians(jacobians);

    // On the inactive branch lambda + rho*g <= 0, max(0, .) and its selected
    // boundary derivative are zero.
    const double shifted = lambda_ + penalty_ * expression(0);
    RequireFinite(shifted);
    if (shifted <= 0.0) {
      if (jacobians) {
        for (Matrix& jacobian : *jacobians) {
          jacobian.setZero();
        }
      }
      return Vector1::Zero();
    }

    // On the active branch r=(lambda+rho*g)/sqrt(rho), hence
    // dr/dx=sqrt(rho)*dg/dx.
    const double sqrtPenalty = std::sqrt(penalty_);
    if (jacobians) {
      for (Matrix& jacobian : *jacobians) {
        jacobian *= sqrtPenalty;
      }
    }
    RequireFiniteJacobians(jacobians);
    const double residual = shifted / sqrtPenalty;
    RequireFinite(residual);
    return Vector1(residual);
  }

  GaussianFactor::shared_ptr linearize(const Values& values) const override {
    auto gaussian = Base::linearize(values);
    const auto* quadratic =
        dynamic_cast<const QuadraticInequalityConstraintFactor*>(constraint_.get());
    if (!quadratic) return gaussian;
    const double shifted =
        lambda_ + penalty_ * constraint_->whitenedExpr(values)(0);
    if (shifted <= 0.0) return gaussian;
    const auto& specification = quadratic->quadraticConstraint();
    const double sign =
        specification.sense() == QuadraticConstraint::Sense::GreaterEqual ? -1.0 : 1.0;
    return AddQuadraticCurvature(
        gaussian, specification, values,
        shifted * sign / specification.sigma());
  }

  /// Return a deep copy.
  NonlinearFactor::shared_ptr clone() const override {
    return std::static_pointer_cast<NonlinearFactor>(
        NonlinearFactor::shared_ptr(new This(*this)));
  }
};

// Exact direct-vector QCQP merit differences; generic manifold/noise factors
// retain the original optimizer. No feasibility or stationarity rule changes.
struct MeritDifference {
  long double reduction = 0.0L;
  long double arithmeticScale = 0.0L;
  long double correction = 0.0L;
  long double inheritedError = 0.0L;
  void add(long double term) {
    const long double y = term - correction;
    const long double next = reduction + y;
    correction = (next - reduction) - y;
    reduction = next;
    arithmeticScale += std::abs(term);
  }
  bool positive() const {
    return std::isfinite(reduction) && reduction >
        inheritedError + 64.0L * std::numeric_limits<long double>::epsilon() * arithmeticScale;
  }
};

struct ExpressionIncrement {
  long double value, increment, valueError, incrementError;
};
ExpressionIncrement ScaledIncrement(const MeritDifference& value,
                                   const MeritDifference& increment,
                                   long double scale) {
  const long double epsilon=64.L*std::numeric_limits<long double>::epsilon();
  return {scale*value.reduction,scale*increment.reduction,
          std::abs(scale)*epsilon*(value.arithmeticScale+std::abs(value.reduction)),
          std::abs(scale)*epsilon*(increment.arithmeticScale+std::abs(increment.reduction))};
}
long double MeritIncrementError(const ExpressionIncrement& e,
                               long double multiplier,long double rho) {
  return rho*std::abs(e.increment)*e.valueError +
      (std::abs(multiplier)+rho*(std::abs(e.value)+e.valueError+
       std::abs(e.increment)+e.incrementError))*e.incrementError;
}

Matrix DirectMatrix(const Values& values, Key key) {
  const auto& value = values.at(key);
  if (const auto* v = dynamic_cast<const GenericValue<Vector>*>(&value))
    return v->value();
  if (const auto* m = dynamic_cast<const GenericValue<Matrix>*>(&value))
    return m->value();
  throw std::invalid_argument("stable QCQP merit requires direct vector/matrix values");
}

ExpressionIncrement QuadraticIncrement(
    const QuadraticConstraint& constraint, const Values& oldValues,
    const Values& newValues) {
  DenseIndex rows = 0, cols = 0;
  for (Key key : constraint.keys()) {
    const Matrix value = DirectMatrix(oldValues, key);
    rows += value.rows();
    if (cols && cols != value.cols())
      throw std::invalid_argument("stable QCQP column mismatch");
    cols = value.cols();
  }
  using Extended = Eigen::Matrix<long double, Eigen::Dynamic, Eigen::Dynamic>;
  Extended x(rows, cols), d(rows, cols);
  DenseIndex offset = 0;
  for (Key key : constraint.keys()) {
    const Matrix before = DirectMatrix(oldValues, key);
    const Matrix after = DirectMatrix(newValues, key);
    if (before.rows()!=after.rows() || before.cols()!=after.cols())
      throw std::invalid_argument("stable QCQP value shape changed");
    x.middleRows(offset, before.rows()) = before.cast<long double>();
    d.middleRows(offset, before.rows()) =
        after.cast<long double>() - before.cast<long double>();
    offset += before.rows();
  }
  const Matrix& a = constraint.A();
  MeritDifference value, increment;
  value.add(-static_cast<long double>(constraint.b()));
  for (DenseIndex col=0; col<cols; ++col)
    for (DenseIndex i=0; i<rows; ++i)
      for (DenseIndex j=0; j<rows; ++j) {
        value.add(x(i,col)*a(i,j)*x(j,col));
        increment.add(d(i,col)*a(i,j)*x(j,col));
        increment.add(x(i,col)*a(i,j)*d(j,col));
        increment.add(d(i,col)*a(i,j)*d(j,col));
      }
  const long double scale =
      (constraint.sense()==QuadraticConstraint::Sense::GreaterEqual ? -1.L : 1.L)
      / constraint.sigma();
  return ScaledIncrement(value,increment,scale);
}

MeritDifference HessianReduction(const HessianFactor& hessian,
                                 const VectorValues& delta) {
  MeritDifference result;
  if (hessian.empty()) return result;
  const Vector d = delta.vector(hessian.keys());
  const Matrix augmented = hessian.augmentedInformation();
  const DenseIndex n = d.size();
  for (DenseIndex i=0; i<n; ++i) {
    result.add(static_cast<long double>(augmented(i,n))*d(i));
    for (DenseIndex j=0; j<n; ++j)
      result.add(-0.5L*static_cast<long double>(d(i))*augmented(i,j)*d(j));
  }
  return result;
}

std::vector<ExpressionIncrement> LinearIncrement(
    const LinearConstraint& constraint, const Values& before,
    const Values& after) {
  const auto& factor = constraint.factor();
  const Matrix augmented = factor.augmentedJacobianUnweighted();
  const Vector b = factor.getb();
  std::vector<long double> x,d;
  for (Key key : factor.keys()) {
    const Matrix old = DirectMatrix(before,key), next = DirectMatrix(after,key);
    for (DenseIndex col=0; col<old.cols(); ++col)
      for (DenseIndex row=0; row<old.rows(); ++row) {
        x.push_back(old(row,col));
        d.push_back(static_cast<long double>(next(row,col))-old(row,col));
      }
  }
  std::vector<ExpressionIncrement> result;
  for (DenseIndex row=0; row<b.size(); ++row) {
    MeritDifference value,increment;
    value.add(-static_cast<long double>(b(row)));
    for (size_t col=0; col<x.size(); ++col) {
      value.add(static_cast<long double>(augmented(row,col))*x[col]);
      increment.add(static_cast<long double>(augmented(row,col))*d[col]);
    }
    const long double sign = constraint.sense()==LinearConstraint::Sense::GreaterEqual ? -1.L : 1.L;
    const long double scale = sign/constraint.sigmas()(row);
    result.push_back(ScaledIncrement(value,increment,scale));
  }
  return result;
}

MeritDifference CostReduction(const QpCost& cost, const Values& before,
                              const Values& after) {
  const auto& factor=cost.hessianFactor();
  const Matrix augmented=factor.augmentedInformation();
  std::vector<long double> x,d;
  for (Key key : factor.keys()) {
    const Matrix old=DirectMatrix(before,key),next=DirectMatrix(after,key);
    for (DenseIndex col=0; col<old.cols(); ++col)
      for (DenseIndex row=0; row<old.rows(); ++row) {
        x.push_back(old(row,col));
        d.push_back(static_cast<long double>(next(row,col))-old(row,col));
      }
  }
  MeritDifference result;
  for (size_t i=0; i<d.size(); ++i) {
    result.add(static_cast<long double>(augmented(i,d.size()))*d[i]);
    for (size_t j=0; j<d.size(); ++j) {
      result.add(-x[i]*augmented(i,j)*d[j]);
      result.add(-0.5L*d[i]*augmented(i,j)*d[j]);
    }
  }
  return result;
}

bool ExactQcqpMerit(const ConstrainedOptProblem& problem) {
  for (const auto& cost : problem.costs())
    if (cost && typeid(*cost)!=typeid(QpCost)) return false;
  for (const auto& c : problem.eConstraints())
    if (typeid(*c)!=typeid(QuadraticEqualityConstraintFactor) &&
        typeid(*c)!=typeid(LinearEqualityConstraintFactor)) return false;
  for (const auto& c : problem.iConstraints())
    if (typeid(*c)!=typeid(QuadraticInequalityConstraintFactor) &&
        typeid(*c)!=typeid(LinearInequalityConstraintFactor)) return false;
  return true;
}

class StableQcqpLM : public LevenbergMarquardtOptimizer {
  const ConstrainedOptProblem& problem_;
  AugmentedLagrangianState subproblem_;

  MeritDifference actualReduction(const Values& before, const Values& after,
                                  const VectorValues& realized) const {
    MeritDifference result;
    for (const auto& cost : problem_.costs()) {
      if (!cost) continue;
      const MeritDifference local = CostReduction(*dynamic_cast<const QpCost*>(cost.get()),before,after);
      result.add(local.reduction);
      result.arithmeticScale += local.arithmeticScale;
    }
    for (size_t i=0; i<problem_.eConstraints().size(); ++i) {
      const auto* quadratic = dynamic_cast<const QuadraticEqualityConstraintFactor*>(problem_.eConstraints()[i].get());
      std::vector<ExpressionIncrement> components;
      if (quadratic) components.push_back(QuadraticIncrement(quadratic->quadraticConstraint(),before,after));
      else components=LinearIncrement(dynamic_cast<const LinearEqualityConstraintFactor*>(problem_.eConstraints()[i].get())->linearConstraint(),before,after);
      const long double rho=subproblem_.muEq;
      for (size_t row=0; row<components.size(); ++row) {
        const long double h=components[row].value,dh=components[row].increment;
        result.inheritedError += MeritIncrementError(components[row],subproblem_.lambdaEq[i](row),rho);
        result.add(-static_cast<long double>(subproblem_.lambdaEq[i](row))*dh);
        result.add(-rho*h*dh);
        result.add(-0.5L*rho*dh*dh);
      }
    }
    for (size_t i=0; i<problem_.iConstraints().size(); ++i) {
      const auto* quadratic = dynamic_cast<const QuadraticInequalityConstraintFactor*>(problem_.iConstraints()[i].get());
      const auto component = quadratic
          ? QuadraticIncrement(quadratic->quadraticConstraint(),before,after)
          : LinearIncrement(dynamic_cast<const LinearInequalityConstraintFactor*>(problem_.iConstraints()[i].get())->linearConstraint(),before,after).at(0);
      const long double g=component.value,dg=component.increment;
      const long double rho = subproblem_.muIneq;
      result.inheritedError += MeritIncrementError(component,subproblem_.lambdaIneq[i],rho);
      const long double shifted = subproblem_.lambdaIneq[i] + rho*g;
      const long double next = shifted + rho*dg;
      if (shifted>0.L && next>0.L) {
        result.add(-shifted*dg);
        result.add(-0.5L*rho*dg*dg);
      } else {
        const long double oldPositive = std::max(0.L,shifted);
        const long double newPositive = std::max(0.L,next);
        result.add((oldPositive-newPositive)*(oldPositive+newPositive)/(2.L*rho));
      }
    }
    return result;
  }

 public:
  StableQcqpLM(const NonlinearFactorGraph& graph, const Values& values,
               const LevenbergMarquardtParams& params,
               const ConstrainedOptProblem& problem,
               const AugmentedLagrangianState& subproblem)
      : LevenbergMarquardtOptimizer(graph,values,params),
        problem_(problem), subproblem_(subproblem) {}

  GaussianFactorGraph::shared_ptr iterate() override {
    auto linear = linearize();
    const bool useMultifrontal = ensureMultifrontalSolver(params_, state_->values);
    if (useMultifrontal) nonlinearMultifrontalSolver_->load(*linear);
    VectorValues diagonal;
    if (params_.dampingParams.diagonalDamping && !useMultifrontal) {
      diagonal = linear->hessianDiagonal();
      for (auto& entry : diagonal)
        entry.second = entry.second.cwiseMax(params_.dampingParams.minDiagonal)
            .cwiseMin(params_.dampingParams.maxDiagonal).cwiseSqrt();
    }
    auto* state = static_cast<internal::LevenbergMarquardtState*>(state_.get());
    while (true) {
      const double triedLambda = state->lambda;
      bool solved = false, accepted = false;
      MeritDifference predicted, actual;
      Values next;
      try {
        VectorValues proposed;
        if (useMultifrontal) {
          nonlinearMultifrontalSolver_->eliminateInPlace(triedLambda);
          proposed = nonlinearMultifrontalSolver_->updateSolution();
        } else {
          proposed = solve(buildDampedSystem(*linear,diagonal),params_);
        }
        // A solved cap direction may overshoot the nonlinear merit. Try
        // bounded fractions of that same direction from the same base point.
        // Keep the original full-step prediction gate, merit and tolerances.
        const double directionalDerivative =
            triedLambda >= params_.lambdaUpperBound
                ? linear->gradientAtZero().dot(proposed) : 0.0;
        const bool capDescent = triedLambda >= params_.lambdaUpperBound &&
            std::isfinite(directionalDerivative) && directionalDerivative < 0.0;
        for (size_t contractions = 0; ; ++contractions) {
          solved = false;
          predicted = MeritDifference{};
          actual = MeritDifference{};
          const VectorValues trial = contractions == 0
              ? proposed : std::ldexp(1.0, -int(contractions)) * proposed;
          next = state->values.retract(trial);
          const VectorValues realized = state->values.localCoordinates(next);
          const double stepNorm = realized.norm();
          if (stepNorm > 0.0 && std::isfinite(stepNorm)) {
            solved = true;
            for (const auto& factor : *linear) {
              if (!factor) continue;
              const auto local = HessianReduction(HessianFactor(*factor),realized);
              predicted.add(local.reduction);
              predicted.arithmeticScale += local.arithmeticScale;
            }
            if (predicted.positive()) {
              actual = actualReduction(state->values,next,realized);
              accepted = actual.positive() &&
                  actual.reduction/predicted.reduction>params_.minModelFidelity;
            }
          }
          if (accepted || !capDescent || !solved || contractions == 64 ||
              (contractions == 0 && !predicted.positive())) break;
        }
      } catch (const IndeterminateSystemException&) {
        solved = false;
      }
      if (params_.verbosityLM>=LevenbergMarquardtParams::TRYLAMBDA)
        std::cout << std::setprecision(17) << "stable_qcqp lambda=" << triedLambda
          << " solved=" << solved << " predicted=" << predicted.reduction
          << " actual=" << actual.reduction << " accepted=" << accepted << std::endl;
      if (accepted) {
        const double newError = graph().error(next);
        if (!std::isfinite(newError)) return linear;
        state_ = state->decreaseLambda(params_,
            static_cast<double>(actual.reduction/predicted.reduction),
            std::move(next),newError);
        return linear;
      }
      // A rejected cap attempt exhausts the search. Otherwise clamp the next
      // attempt to the cap, so the configured boundary is actually tried.
      if (triedLambda>=params_.lambdaUpperBound) return linear;
      state->increaseLambda(params_);
      // Repeated successful decreases may underflow damping to zero. A
      // refused undamped step then needs the configured positive seed;
      // multiplying zero cannot resume the bounded damping search.
      if (triedLambda == 0.0 && state->lambda == 0.0 &&
          std::isfinite(params_.lambdaInitial) && params_.lambdaInitial > 0.0) {
        state->lambda = params_.lambdaInitial;
      }
      state->lambda = std::min(state->lambda,params_.lambdaUpperBound);
      if (!(state->lambda>triedLambda)) return linear;
    }
  }
};

struct Diagnostics {
  double generalizedConstraintViolation = 0.0;
  double primalInequalityViolation = 0.0;
  double complementarity = 0.0;
};

/* ************************************************************************* */
double InfinityNorm(const Vector& vector) {
  RequireFinite(vector);
  return vector.size() == 0 ? 0.0 : vector.cwiseAbs().maxCoeff();
}

/* ************************************************************************* */
double AugmentedLagrangianStationarity(const NonlinearFactorGraph& graph,
                                       const Values& values) {
  // A finite reduced gradient cannot certify a nonfinite merit value.
  RequireFinite(graph.error(values));
  const VectorValues gradient = graph.linearize(values)->gradientAtZero();
  double infinityNorm = 0.0;
  for (const auto& keyGradient : gradient) {
    infinityNorm = std::max(infinityNorm, InfinityNorm(keyGradient.second));
  }
  return infinityNorm;
}

/* ************************************************************************* */
Diagnostics EvaluateDiagnostics(const ConstrainedOptProblem& problem,
                                const Values& values,
                                const AugmentedLagrangianState& subproblem) {
  Diagnostics diagnostics;
  RequireFinite(subproblem.muEq);
  RequireFinite(subproblem.muIneq);

  // Equality feasibility contributes ||h(x)||_inf to theta.
  for (const auto& constraint : problem.eConstraints()) {
    diagnostics.generalizedConstraintViolation =
        std::max(diagnostics.generalizedConstraintViolation,
                 InfinityNorm(constraint->whitenedError(values)));
  }

  const auto& inequalities = problem.iConstraints();
  for (size_t i = 0; i < inequalities.size(); ++i) {
    const double expression = inequalities.at(i)->whitenedExpr(values)(0);
    const double lambda = subproblem.lambdaIneq.at(i);
    RequireFinite(expression);
    RequireFinite(lambda);

    // q=max(g,-lambda/rho) makes the projected multiplier update
    // lambda^+=max(0,lambda+rho*g)=lambda+rho*q. Thus q=0 encodes primal
    // feasibility and complementarity, including inactive inequalities.
    const double lowerBound = -lambda / subproblem.muIneq;
    RequireFinite(lowerBound);
    const double projectedResidual = std::max(expression, lowerBound);
    const double shifted = lambda + subproblem.muIneq * expression;
    RequireFinite(shifted);
    const double projectedLambda = std::max(0.0, shifted);
    RequireFinite(projectedResidual);
    const double complementarity = projectedLambda * expression;
    RequireFinite(complementarity);

    // BCL accepts a multiplier update using
    // theta=max(||h||_inf,||q||_inf), not merely max(g,0).
    diagnostics.generalizedConstraintViolation =
        std::max(diagnostics.generalizedConstraintViolation,
                 std::abs(projectedResidual));
    // Report primal violation and complementarity separately for diagnosis.
    diagnostics.primalInequalityViolation = std::max(
        diagnostics.primalInequalityViolation, std::max(0.0, expression));
    diagnostics.complementarity = std::max(
        diagnostics.complementarity, std::abs(complementarity));
  }

  return diagnostics;
}

/* ************************************************************************* */
void InitializeBclSchedule(const AugmentedLagrangianParams& params,
                           double penalty, AugmentedLagrangianState* state) {
  // Conn--Gould--Toint use an inverse penalty mu. With rho=1/mu, their
  // alpha=min(mu,gamma_1) becomes alpha=min(1/rho,gamma_1).
  state->bclAlpha = std::min(1.0 / penalty, params.bclGamma1);
  state->bclOmega =
      params.bclOmega0 * std::pow(state->bclAlpha, params.bclAlphaOmega);
  state->bclEta =
      params.bclEta0 * std::pow(state->bclAlpha, params.bclAlphaEta);
}

/* ************************************************************************* */
bool AggressiveConverged(const AugmentedLagrangianState& state,
                         const AugmentedLagrangianState& previousState,
                         const AugmentedLagrangianParams& params) {
  if (state.violation() < params.absoluteViolationTolerance &&
      state.cost < params.absoluteCostTolerance) {
    return true;
  }
  return std::abs(state.violation() - previousState.violation()) <
             params.relativeViolationTolerance &&
         std::abs(state.cost - previousState.cost) <
             params.relativeCostTolerance;
}

/* ************************************************************************* */
AugmentedLagrangianUpdateType CombinedUpdateType(bool multiplierUpdated,
                                                 bool penaltyUpdated) {
  if (multiplierUpdated && penaltyUpdated) {
    return AugmentedLagrangianUpdateType::MultiplierAndPenalty;
  }
  if (multiplierUpdated) {
    return AugmentedLagrangianUpdateType::Multiplier;
  }
  if (penaltyUpdated) {
    return AugmentedLagrangianUpdateType::Penalty;
  }
  return AugmentedLagrangianUpdateType::None;
}

}  // namespace

/* ************************************************************************* */
void AugmentedLagrangianState::initializeLagrangeMultipliers(
    const ConstrainedOptProblem& problem) {
  lambdaEq.clear();
  lambdaEq.reserve(problem.eConstraints().size());
  for (const auto& constraint : problem.eConstraints()) {
    lambdaEq.push_back(Vector::Zero(constraint->dim()));
  }
  lambdaIneq.assign(problem.iConstraints().size(), 0.0);
}

/* ************************************************************************* */
std::tuple<AugmentedLagrangianOptimizer::State, double, double>
AugmentedLagrangianOptimizer::iterate(const State& state, double muEq,
                                      double muIneq) const {
  // Validate the fixed-parameter augmented-Lagrangian subproblem.
  validateConfiguration();
  if (!std::isfinite(muEq) || !std::isfinite(muIneq) ||
      muEq <= 0.0 || muIneq <= 0.0) {
    throw std::invalid_argument("ALM direct penalties must be positive");
  }
  if (p_->updatePolicy == AugmentedLagrangianUpdatePolicy::BCL &&
      muEq != muIneq) {
    // Algorithm 1 of Conn--Gould--Toint has one inverse penalty mu_k for the
    // complete constraint vector c(x). In direct notation rho_k=1/mu_k, the
    // same rho must therefore weight h and the PHR inequality terms. Separate
    // penalties would require a new vector-valued schedule and a new definition
    // of alpha_k, so it would no longer be the paper's BCL update policy.
    // Constraint sigmas still provide fixed relative block scaling. The
    // Aggressive policy remains free to use separate equality/inequality rho.
    throw std::invalid_argument(
        "BCL Algorithm 1 requires muEq == muIneq (one common direct penalty "
        "rho)");
  }

  // Hold multipliers and penalties fixed while solving the inner problem.
  State subproblemState = state;
  subproblemState.muEq = muEq;
  subproblemState.muIneq = muIneq;
  if (subproblemState.lambdaEq.size() != problem_.eConstraints().size() ||
      subproblemState.lambdaIneq.size() != problem_.iConstraints().size()) {
    if (subproblemState.lambdaEq.empty() &&
        subproblemState.lambdaIneq.empty()) {
      subproblemState.initializeLagrangeMultipliers(problem_);
    } else {
      throw std::invalid_argument(
          "ALM multiplier dimensions do not match constraints");
    }
  }
  if (p_->updatePolicy == AugmentedLagrangianUpdatePolicy::BCL &&
      (subproblemState.bclOmega <= 0.0 || subproblemState.bclEta <= 0.0)) {
    // Initialize omega_k and eta_k when iterate() is called directly.
    InitializeBclSchedule(*p_, muEq, &subproblemState);
  }

  const auto start = std::chrono::steady_clock::now();

  // Construct the merit function at (lambda_k,rho_k), then run unconstrained
  // LM from x_k. Multiplier updates happen only after x_{k+1} is available.
  const NonlinearFactorGraph augmentedLagrangian =
      augmentedLagrangianFunction(subproblemState);
  const SharedOptimizer optimizer = ExactQcqpMerit(problem_)
      ? std::make_shared<StableQcqpLM>(augmentedLagrangian, state.values,
                                     p_->lmParams, problem_, subproblemState)
      : createUnconstrainedOptimizer(augmentedLagrangian, state.values);

  double stationarity =
      AugmentedLagrangianStationarity(augmentedLagrangian, optimizer->values());
  if (p_->updatePolicy == AugmentedLagrangianUpdatePolicy::BCL) {
    // The paper stops its projected inner solve when the projected gradient is
    // at most omega_k. Because this implementation substitutes unconstrained
    // LM, it uses s_k=||grad_x L_rho(x,lambda_k)||_inf <= omega_k.
    // Solving more tightly than the declared terminal stationarity target
    // can exhaust finite precision before feasibility can be improved.
    subproblemState.bclOmega = std::max(
        subproblemState.bclOmega, p_->absoluteStationarityTolerance);
    while (stationarity > subproblemState.bclOmega &&
           optimizer->iterations() < p_->lmParams.maxIterations) {
      const size_t previousIterations = optimizer->iterations();
      optimizer->iterate();
      stationarity = AugmentedLagrangianStationarity(augmentedLagrangian,
                                                     optimizer->values());
      if (optimizer->iterations() == previousIterations) {
        break;
      }
    }
  } else {
    // Preserve the historical Aggressive behavior of letting LM use its own
    // convergence checks and iteration cap for every outer subproblem.
    optimizer->optimize();
    stationarity = AugmentedLagrangianStationarity(augmentedLagrangian,
                                                   optimizer->values());
  }

  // Evaluate objective and all policy diagnostics at the returned point
  // x_{k+1}; evaluating at x_k was the old sequencing error.
  State solvedState = subproblemState;
  solvedState.iteration = state.iteration + 1;
  solvedState.setValues(optimizer->values(), problem_);
  RequireFinite(solvedState.cost);
  RequireFinite(solvedState.eqConstraintViolation);
  RequireFinite(solvedState.ineqConstraintViolation);
  solvedState.unconstrainedIterations = optimizer->iterations();
  solvedState.totalUnconstrainedIterations =
      state.totalUnconstrainedIterations + solvedState.unconstrainedIterations;
  solvedState.augmentedLagrangianStationarity = stationarity;
  solvedState.innerStationarityTolerance = subproblemState.bclOmega;
  const Diagnostics diagnostics =
      EvaluateDiagnostics(problem_, solvedState.values, subproblemState);
  solvedState.generalizedConstraintViolation =
      diagnostics.generalizedConstraintViolation;
  solvedState.primalInequalityViolation = diagnostics.primalInequalityViolation;
  solvedState.complementarity = diagnostics.complementarity;
  solvedState.updateType = AugmentedLagrangianUpdateType::None;
  solvedState.converged = false;

  double nextMuEq = muEq;
  double nextMuIneq = muIneq;
  if (p_->updatePolicy == AugmentedLagrangianUpdatePolicy::Aggressive) {
    // Aggressive always performs projected dual ascent at x_{k+1}, then grows
    // each penalty independently if its violation did not decrease enough.
    solvedState.innerConverged = true;
    updateLagrangeMultiplier(subproblemState, &solvedState);
    std::tie(nextMuEq, nextMuIneq) = updatePenaltyParameter(state, solvedState);
    const bool multiplierUpdated =
        !problem_.eConstraints().empty() || !problem_.iConstraints().empty();
    const bool penaltyUpdated = nextMuEq != muEq || nextMuIneq != muIneq;
    solvedState.updateType =
        CombinedUpdateType(multiplierUpdated, penaltyUpdated);
  } else {
    solvedState.innerConverged = stationarity <= subproblemState.bclOmega;

    // If LM exhausts its cap before s_k<=omega_k, Algorithm 1's inner condition
    // was not met: keep both lambda and rho unchanged and return the best
    // point.
    if (solvedState.innerConverged) {
      if (solvedState.generalizedConstraintViolation <=
          subproblemState.bclEta) {
        // Successful BCL iteration (theta_k<=eta_k):
        //   lambda_h^+ = lambda_h + rho*h,
        //   lambda_g^+ = max(0,lambda_g + rho*g),
        // while rho stays fixed.
        for (size_t i = 0; i < problem_.eConstraints().size(); ++i) {
          solvedState.lambdaEq.at(i) +=
              muEq *
              problem_.eConstraints().at(i)->whitenedError(solvedState.values);
        }
        for (size_t i = 0; i < problem_.iConstraints().size(); ++i) {
          const double expression = problem_.iConstraints().at(i)->whitenedExpr(
              solvedState.values)(0);
          const double shifted = solvedState.lambdaIneq.at(i) + muEq * expression;
          RequireFinite(shifted);
          solvedState.lambdaIneq.at(i) = std::max(0.0, shifted);
        }
        solvedState.updateType = AugmentedLagrangianUpdateType::Multiplier;

        // Tighten the next inner and feasibility targets using the unchanged
        // alpha_k, as in the accepted branch of Algorithm 1.
        solvedState.bclOmega =
            subproblemState.bclOmega *
            std::pow(subproblemState.bclAlpha, p_->bclBetaOmega);
        solvedState.bclEta = subproblemState.bclEta *
                             std::pow(subproblemState.bclAlpha, p_->bclBetaEta);
      } else {
        // Unsuccessful BCL iteration (theta_k>eta_k): hold lambda fixed,
        // increase direct rho by 1/tau, recompute alpha, and reset omega/eta.
        nextMuEq = muEq * p_->bclPenaltyIncreaseRate;
        nextMuIneq = nextMuEq;
        solvedState.updateType = AugmentedLagrangianUpdateType::Penalty;
        InitializeBclSchedule(*p_, nextMuEq, &solvedState);
      }
    }
  }

  for (const Vector& multiplier : solvedState.lambdaEq) {
    InfinityNorm(multiplier);
  }
  for (double multiplier : solvedState.lambdaIneq) {
    RequireFinite(multiplier);
  }
  RequireFinite(nextMuEq);
  RequireFinite(nextMuIneq);

  solvedState.time =
      std::chrono::duration<double>(std::chrono::steady_clock::now() - start)
          .count();
  return {solvedState, nextMuEq, nextMuIneq};
}

/* ************************************************************************* */
Values AugmentedLagrangianOptimizer::optimize() const {
  validateConfiguration();
  progress_.clear();

  // Construct the initial primal-dual state with zero multipliers.
  State state(0, initialValues_, problem_);
  RequireFinite(state.cost);
  RequireFinite(state.eqConstraintViolation);
  RequireFinite(state.ineqConstraintViolation);
  state.initializeLagrangeMultipliers(problem_);
  if (!p_->initialInequalityMultipliers.empty()) {
    if (p_->initialInequalityMultipliers.size() != state.lambdaIneq.size() ||
        !std::all_of(p_->initialInequalityMultipliers.begin(),
                     p_->initialInequalityMultipliers.end(),
                     [](double value) { return std::isfinite(value) && value >= 0.0; }))
      throw std::invalid_argument("initial inequality multipliers do not match constraints");
    state.lambdaIneq = p_->initialInequalityMultipliers;
  }

  double muEq = p_->initialMuEq;
  double muIneq = p_->initialMuIneq;
  if (p_->updatePolicy == AugmentedLagrangianUpdatePolicy::BCL) {
    // BCL uses one common direct penalty and the paper-derived initial
    // stationarity/feasibility schedule.
    muEq = p_->bclInitialPenalty;
    muIneq = p_->bclInitialPenalty;
    InitializeBclSchedule(*p_, muEq, &state);
  }
  state.muEq = muEq;
  state.muIneq = muIneq;
  logInitialState(state);

  // Solve fixed-parameter subproblems and apply the selected outer policy.
  while (true) {
    const State previousState = state;
    std::tie(state, muEq, muIneq) = iterate(previousState, muEq, muIneq);

    if (p_->updatePolicy == AugmentedLagrangianUpdatePolicy::BCL) {
      // Inner convergence describes whether LM met the current BCL
      // subproblem schedule. The final KKT residuals can meet their declared
      // absolute tolerances even when that schedule has tightened further
      // than the required solution accuracy.
      state.converged =
          state.augmentedLagrangianStationarity <=
              p_->absoluteStationarityTolerance &&
          state.generalizedConstraintViolation <=
              p_->absoluteViolationTolerance;
    } else {
      state.converged = AggressiveConverged(state, previousState, *p_);
    }
    logIteration(state);

    if (state.converged || !state.innerConverged ||
        state.iteration >= p_->maxIterations) {
      break;
    }
  }

  return state.values;
}

/* ************************************************************************* */
NonlinearFactorGraph AugmentedLagrangianOptimizer::augmentedLagrangianFunction(
    const State& state, double /*epsilon*/) const {
  validateConfiguration();
  if (!std::isfinite(state.muEq) || !std::isfinite(state.muIneq) ||
      state.muEq <= 0.0 || state.muIneq <= 0.0) {
    throw std::invalid_argument("ALM direct penalties must be positive");
  }
  if (state.lambdaEq.size() != problem_.eConstraints().size() ||
      state.lambdaIneq.size() != problem_.iConstraints().size()) {
    throw std::invalid_argument(
        "ALM multiplier dimensions do not match constraints");
  }

  // Initialize the merit graph with the original least-squares costs.
  NonlinearFactorGraph graph = problem_.costs();

  // Add equality factors. Each graph error is
  // (rho/2)||h+lambda/rho||^2
  //   = lambda^T h + (rho/2)||h||^2 + ||lambda||^2/(2 rho).
  // The final term is independent of x and can be omitted during LM.
  const auto& equalities = problem_.eConstraints();
  for (size_t i = 0; i < equalities.size(); ++i) {
    const auto& constraint = equalities.at(i);
    InfinityNorm(state.lambdaEq.at(i));
    Vector bias = state.lambdaEq.at(i) / state.muEq;
    bias = bias.cwiseProduct(constraint->sigmas());
    InfinityNorm(bias);
    graph.emplace_shared<BiasedFactor>(constraint->penaltyFactor(state.muEq),
                                       bias);
  }

  // Add exact PHR factors for scalar g<=0. Each graph error is
  // max(0,lambda+rho*g)^2/(2 rho), which differs from the mathematical PHR
  // term only by the x-independent constant lambda^2/(2 rho).
  const auto& inequalities = problem_.iConstraints();
  for (size_t i = 0; i < inequalities.size(); ++i) {
    RequireFinite(state.lambdaIneq.at(i));
    if (state.lambdaIneq.at(i) < 0.0) {
      throw std::invalid_argument("ALM inequality multipliers must be nonnegative");
    }
    graph.emplace_shared<PhrInequalityFactor>(
        inequalities.at(i), state.lambdaIneq.at(i), state.muIneq);
  }

  return graph;
}

/* ************************************************************************* */
void AugmentedLagrangianOptimizer::updateLagrangeMultiplier(
    const State& subproblemState, State* solvedState) const {
  // Perform dual ascent on equality multipliers using h(x_{k+1}). Constraint
  // violation is the gradient of the dual function with respect to lambda.
  const auto& equalities = problem_.eConstraints();
  solvedState->lambdaEq.resize(equalities.size());
  for (size_t i = 0; i < equalities.size(); ++i) {
    const Vector violation =
        equalities.at(i)->whitenedError(solvedState->values);
    const double stepSize = std::min(
        p_->maxDualStepSizeEq, subproblemState.muEq * p_->dualStepSizeFactorEq);
    solvedState->lambdaEq.at(i) =
        subproblemState.lambdaEq.at(i) + stepSize * violation;
  }

  // Perform projected dual ascent on inequality multipliers using g(x_{k+1})
  // and projection onto lambda>=0.
  const auto& inequalities = problem_.iConstraints();
  solvedState->lambdaIneq.resize(inequalities.size());
  for (size_t i = 0; i < inequalities.size(); ++i) {
    const double violation =
        inequalities.at(i)->whitenedExpr(solvedState->values)(0);
    const double stepSize =
        std::min(p_->maxDualStepSizeIneq,
                 subproblemState.muIneq * p_->dualStepSizeFactorIneq);
    const double shifted =
        subproblemState.lambdaIneq.at(i) + stepSize * violation;
    RequireFinite(shifted);
    solvedState->lambdaIneq.at(i) = std::max(0.0, shifted);
  }
}

/* ************************************************************************* */
std::pair<double, double> AugmentedLagrangianOptimizer::updatePenaltyParameter(
    const State& previousState, const State& solvedState) const {
  // Aggressive keeps separate penalties and increases a block's rho when its
  // violation has not contracted by muIncreaseThreshold.
  double muEq = solvedState.muEq;
  if (!problem_.eConstraints().empty() &&
      solvedState.eqConstraintViolation >=
          p_->muIncreaseThreshold * previousState.eqConstraintViolation) {
    muEq *= p_->muEqIncreaseRate;
  }

  double muIneq = solvedState.muIneq;
  if (!problem_.iConstraints().empty() &&
      solvedState.ineqConstraintViolation >=
          p_->muIncreaseThreshold * previousState.ineqConstraintViolation) {
    muIneq *= p_->muIneqIncreaseRate;
  }
  return {muEq, muIneq};
}

/* ************************************************************************* */
ConstrainedOptimizer::SharedOptimizer
AugmentedLagrangianOptimizer::createUnconstrainedOptimizer(
    const NonlinearFactorGraph& graph, const Values& values) const {
  // TODO(yetong): make compatible with all NonlinearOptimizers.
  return std::make_shared<LevenbergMarquardtOptimizer>(graph, values,
                                                       p_->lmParams);
}

/* ************************************************************************* */
void AugmentedLagrangianOptimizer::validateConfiguration() const {
  if (!p_) {
    throw std::invalid_argument("AugmentedLagrangianParams must not be null");
  }
  if (p_->ineqConstraintPenaltyFunction) {
    throw std::invalid_argument(
        "AugmentedLagrangianOptimizer requires exact PHR inequalities; custom "
        "smoothed inequality penalties are unsupported");
  }
  for (const auto& inequality : problem_.iConstraints()) {
    if (inequality->dim() != 1) {
      throw std::invalid_argument(
          "AugmentedLagrangianOptimizer supports scalar inequalities only");
    }
  }
  if (p_->initialMuEq <= 0.0 || p_->initialMuIneq <= 0.0 ||
      p_->muEqIncreaseRate <= 0.0 || p_->muIneqIncreaseRate <= 0.0 ||
      p_->absoluteStationarityTolerance < 0.0) {
    throw std::invalid_argument("Invalid Aggressive ALM parameters");
  }
  if (p_->bclInitialPenalty <= 0.0 || p_->bclPenaltyIncreaseRate <= 1.0 ||
      p_->bclOmega0 <= 0.0 || p_->bclEta0 <= 0.0 || p_->bclGamma1 <= 0.0 ||
      p_->bclAlphaOmega <= 0.0 || p_->bclBetaOmega <= 0.0 ||
      p_->bclAlphaEta <= 0.0 || p_->bclBetaEta <= 0.0) {
    throw std::invalid_argument("Invalid BCL ALM parameters");
  }
}

/* ************************************************************************* */
void AugmentedLagrangianOptimizer::logInitialState(const State& state) const {
  if (p_->verbose) {
    // Log title line.
    cout << setw(8) << "Iter"
         << "|" << setw(10) << "rhoEq"
         << "|" << setw(10) << "rhoIneq"
         << "|" << setw(10) << "cost"
         << "|" << setw(10) << "vio_e"
         << "|" << setw(10) << "vio_i"
         << "|" << setw(10) << "station"
         << "|" << setw(10) << "theta"
         << "|" << setw(10) << "lm_iters"
         << "|" << endl;

    // Log initial value line.
    cout << setw(8) << state.iteration << "|" << setw(10) << state.muEq << "|"
         << setw(10) << state.muIneq << "|" << setw(10) << setprecision(4)
         << state.cost << "|" << setw(10) << state.eqConstraintViolation << "|"
         << setw(10) << state.ineqConstraintViolation << "|" << setw(10) << "-"
         << "|" << setw(10) << "-"
         << "|" << setw(10) << "-"
         << "|" << endl;
  }
  // Store state.
  if (p_->storeOptProgress) {
    progress_.emplace_back(state);
  }
}

/* ************************************************************************* */
void AugmentedLagrangianOptimizer::logIteration(const State& state) const {
  if (p_->verbose) {
    cout << setw(8) << state.iteration << "|" << setw(10) << state.muEq << "|"
         << setw(10) << state.muIneq << "|" << setw(10) << setprecision(4)
         << state.cost << "|" << setw(10) << state.eqConstraintViolation << "|"
         << setw(10) << state.ineqConstraintViolation << "|" << setw(10)
         << state.augmentedLagrangianStationarity << "|" << setw(10)
         << state.generalizedConstraintViolation << "|" << setw(10)
         << state.unconstrainedIterations << "|" << endl;
  }
  // Store state.
  if (p_->storeOptProgress) {
    progress_.emplace_back(state);
  }
}

}  // namespace gtsam

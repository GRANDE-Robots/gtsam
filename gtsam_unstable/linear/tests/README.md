# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [testLPSolver.cpp](testLPSolver.cpp) | Test simple QP solver for a linear inequality constraint. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [MatrixConstants.h](../../../gtsam/base/MatrixConstants.h); [Testable.h](../../../gtsam/base/Testable.h); [FactorGraph-inst.h](../../../gtsam/inference/FactorGraph-inst.h); 8 other source includes; `gtsam` headers | None |
| [testLinearEquality.cpp](testLinearEquality.cpp) | Unit tests for LinearEquality. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [MatrixConstants.h](../../../gtsam/base/MatrixConstants.h); [TestableAssertions.h](../../../gtsam/base/TestableAssertions.h); [VectorConstants.h](../../../gtsam/base/VectorConstants.h); 3 other source includes; `gtsam` headers | None |
| [testQPSolver.cpp](testQPSolver.cpp) | Test simple QP solver for a linear inequality constraint. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [MatrixConstants.h](../../../gtsam/base/MatrixConstants.h); [Testable.h](../../../gtsam/base/Testable.h); [VectorConstants.h](../../../gtsam/base/VectorConstants.h); 2 other source includes; `gtsam` headers | [testLPSolver.cpp](testLPSolver.cpp) |

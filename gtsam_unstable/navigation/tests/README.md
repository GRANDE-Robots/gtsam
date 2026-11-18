# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [testEqVIOFilter.cpp](testEqVIOFilter.cpp) | Unit tests for the EqVIOFilter. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [TestableAssertions.h](../../../gtsam/base/TestableAssertions.h); [EqVIOFilter.h](../EqVIOFilter.h); C++ standard/system library | None |
| [testEqVIOGroup.cpp](testEqVIOGroup.cpp) | Unit tests for EqVIOGroup. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [TestableAssertions.h](../../../gtsam/base/TestableAssertions.h); [numericalDerivative.h](../../../gtsam/base/numericalDerivative.h); [EqVIOCommon.h](../EqVIOCommon.h); C++ standard/system library | None |
| [testEqVIOState.cpp](testEqVIOState.cpp) | Unit tests for VIOState manifold. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [TestableAssertions.h](../../../gtsam/base/TestableAssertions.h); [numericalDerivative.h](../../../gtsam/base/numericalDerivative.h); [EqVIOState.h](../EqVIOState.h); C++ standard/system library | None |
| [testEqVIOSymmetry.cpp](testEqVIOSymmetry.cpp) | Unit tests for VIO symmetry actions and lift helpers. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [GroupAction.h](../../../gtsam/base/GroupAction.h); [gtsam/base/Matrix.h](../../../gtsam/base/Matrix.h); [TestableAssertions.h](../../../gtsam/base/TestableAssertions.h); 6 other source includes; C++ standard/system library | None |

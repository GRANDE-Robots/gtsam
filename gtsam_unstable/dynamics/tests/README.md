# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [testPendulumFactors.cpp](testPendulumFactors.cpp) | Checks Pendulum Factors behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [MatrixConstants.h](../../../gtsam/base/MatrixConstants.h); [gtsam/inference/Symbol.h](../../../gtsam/inference/Symbol.h); [Pendulum.h](../Pendulum.h); `gtsam` headers | None |
| [testSimpleHelicopter.cpp](testSimpleHelicopter.cpp) | Checks Simple Helicopter behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [Vector.h](../../../gtsam/base/Vector.h); [VectorConstants.h](../../../gtsam/base/VectorConstants.h); [numericalDerivative.h](../../../gtsam/base/numericalDerivative.h); 4 other source includes; `gtsam` headers | [stats.html](../../../doc/stats.html) |
| [testVelocityConstraint3.cpp](testVelocityConstraint3.cpp) | Checks Velocity Constraint3 behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [MatrixConstants.h](../../../gtsam/base/MatrixConstants.h); [gtsam/inference/Symbol.h](../../../gtsam/inference/Symbol.h); [VelocityConstraint3.h](../VelocityConstraint3.h); `gtsam` headers | None |

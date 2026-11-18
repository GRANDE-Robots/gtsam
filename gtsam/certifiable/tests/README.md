# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [testLiftedSDPs.cpp](testLiftedSDPs.cpp) | Tests for QCQP-backed lifted SDP objective assembly. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [TestableAssertions.h](../../base/TestableAssertions.h); [LiftedSDPProblem.h](../LiftedSDPProblem.h); [QcqpProblem.h](../../constrained/QcqpProblem.h); 11 other source includes; C++ standard/system library | None |
| [testMosekSDP.cpp](testMosekSDP.cpp) | Test that MOSEK Fusion is installed and can solve an SDP. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); `fusion.h` | [gtsam/certifiable/tests/CMakeLists.txt](CMakeLists.txt) |
| [testRiemannianStaircase.cpp](testRiemannianStaircase.cpp) | Unit tests for the Burer-Monteiro Riemannian Staircase solver. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [TestableAssertions.h](../../base/TestableAssertions.h); [RiemannianStaircaseOptimizer.h](../RiemannianStaircaseOptimizer.h); [AugmentedLagrangianOptimizer.h](../../constrained/AugmentedLagrangianOptimizer.h); 9 other source includes; C++ standard/system library; `Eigen` headers | None |

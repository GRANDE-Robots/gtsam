# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [testBearingFactor.cpp](testBearingFactor.cpp) | Unit tests for BearingFactor Class. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [Pose2.h](../../geometry/Pose2.h); [Pose3.h](../../geometry/Pose3.h); [FixedJacobianFactor.h](../../linear/FixedJacobianFactor.h); 2 other source includes | None |
| [testBearingRangeFactor.cpp](testBearingRangeFactor.cpp) | Unit tests for BearingRangeFactor Class. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [Pose2.h](../../geometry/Pose2.h); [Pose3.h](../../geometry/Pose3.h); [FixedJacobianFactor.h](../../linear/FixedJacobianFactor.h); 2 other source includes | None |
| [testQuadraticRangeFactor.cpp](testQuadraticRangeFactor.cpp) | Unit tests for the CORA range term. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [TestableAssertions.h](../../base/TestableAssertions.h); [numericalDerivative.h](../../base/numericalDerivative.h); [QcqpProblem.h](../../constrained/QcqpProblem.h); 5 other source includes; C++ standard/system library | None |
| [testRISAM.cpp](testRISAM.cpp) | Unit tests for RISAM and supporting classes. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [numericalDerivative.h](../../base/numericalDerivative.h); [Point2.h](../../geometry/Point2.h); [Pose2.h](../../geometry/Pose2.h); 8 other source includes | None |
| [testRangeFactor.cpp](testRangeFactor.cpp) | Unit tests for RangeFactor Class. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [TestableAssertions.h](../../base/TestableAssertions.h); [Cal3_S2.h](../../geometry/Cal3_S2.h); [PinholeCamera.h](../../geometry/PinholeCamera.h); 5 other source includes | None |
| [testSerializationSam.cpp](testSerializationSam.cpp) | All serialization test in this directory. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [gtsam/base/serialization.h](../../base/serialization.h); [serializationTestHelpers.h](../../base/serializationTestHelpers.h); [Pose2.h](../../geometry/Pose2.h); 6 other source includes | [gtsam/sam/tests/CMakeLists.txt](CMakeLists.txt) |

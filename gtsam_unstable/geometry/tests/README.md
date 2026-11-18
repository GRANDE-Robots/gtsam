# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [testABC.cpp](testABC.cpp) | Test file for ABC (Attitude-Bias-Calibration) system components. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [MatrixConstants.h](../../../gtsam/base/MatrixConstants.h); [VectorConstants.h](../../../gtsam/base/VectorConstants.h); [numericalDerivative.h](../../../gtsam/base/numericalDerivative.h); 4 other source includes | [ABC.h](../ABC.h) |
| [testBearingS2.cpp](testBearingS2.cpp) | Tests for a bearing measurement on S2 for 3D bearing measurements. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [TestableAssertions.h](../../../gtsam/base/TestableAssertions.h); [VectorConstants.h](../../../gtsam/base/VectorConstants.h); [BearingS2.h](../BearingS2.h); `gtsam` headers | None |
| [testInvDepthCamera3.cpp](testInvDepthCamera3.cpp) | Checks Inv Depth Camera3 behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [Testable.h](../../../gtsam/base/Testable.h); [numericalDerivative.h](../../../gtsam/base/numericalDerivative.h); [Cal3_S2.h](../../../gtsam/geometry/Cal3_S2.h); 2 other source includes | None |
| [testPose3Upright.cpp](testPose3Upright.cpp) | Checks Pose3 Upright behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [TestableAssertions.h](../../../gtsam/base/TestableAssertions.h); [VectorConstants.h](../../../gtsam/base/VectorConstants.h); [numericalDerivative.h](../../../gtsam/base/numericalDerivative.h); 1 other source includes | None |
| [testSimPolygon2D.cpp](testSimPolygon2D.cpp) | Checks Sim Polygon2 D behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [TestableAssertions.h](../../../gtsam/base/TestableAssertions.h); [SimPolygon2D.h](../SimPolygon2D.h) | None |
| [testSimWall2D.cpp](testSimWall2D.cpp) | Checks Sim Wall2 D behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [TestableAssertions.h](../../../gtsam/base/TestableAssertions.h); [SimWall2D.h](../SimWall2D.h) | None |

# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [Failure.h](Failure.h) | Declares Failure types or operations. | C++ standard/system library | [Test.cpp](Test.cpp); [TestHarness.h](TestHarness.h); [TestRegistry.cpp](TestRegistry.cpp); 4 other source references |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [Test.cpp](Test.cpp) | Implements Test operations. | [Failure.h](Failure.h); [Test.h](Test.h); [TestRegistry.h](TestRegistry.h); [TestResult.h](TestResult.h) | None |
| [Test.h](Test.h) | Declares Test types or operations. | C++ standard/system library | [Test.cpp](Test.cpp); [TestHarness.h](TestHarness.h); [TestRegistry.cpp](TestRegistry.cpp); 10 other source references |
| [TestHarness.h](TestHarness.h) | Declares Test Harness types or operations. | [Failure.h](Failure.h); [Test.h](Test.h); [TestRegistry.h](TestRegistry.h); [TestResult.h](TestResult.h) | [testCholesky.cpp](../gtsam/base/tests/testCholesky.cpp); [testCudaBase.cpp](../gtsam/base/tests/testCudaBase.cpp); [testCudaNames.cpp](../gtsam/base/tests/testCudaNames.cpp); 399 other source references |
| [TestRegistry.cpp](TestRegistry.cpp) | Implements Test Registry operations. | [Failure.h](Failure.h); [Test.h](Test.h); [TestRegistry.h](TestRegistry.h); [TestResult.h](TestResult.h); C++ standard/system library | None |
| [TestRegistry.h](TestRegistry.h) | Declares Test Registry types or operations. | None | [Test.cpp](Test.cpp); [TestHarness.h](TestHarness.h); [TestRegistry.cpp](TestRegistry.cpp); 1 other source references |
| [TestResult.cpp](TestResult.cpp) | Implements Test Result operations. | [Failure.h](Failure.h); [TestResult.h](TestResult.h); C++ standard/system library | None |
| [TestResult.h](TestResult.h) | Declares Test Result types or operations. | None | [Test.cpp](Test.cpp); [TestHarness.h](TestHarness.h); [TestRegistry.cpp](TestRegistry.cpp); 4 other source references |

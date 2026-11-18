# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [testBTree.cpp](testBTree.cpp) | Checks BTree behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [BTree.h](../BTree.h); C++ standard/system library | None |
| [testDSF.cpp](testDSF.cpp) | unit tests for DSF. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [DSF.h](../DSF.h); C++ standard/system library | [testDSFVector.cpp](../../../gtsam/base/tests/testDSFVector.cpp) |
| [testFixedVector.cpp](testFixedVector.cpp) | Checks Fixed Vector behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [FixedVector.h](../FixedVector.h); `gtsam` headers | None |

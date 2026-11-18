# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [testFindSeparator.cpp](testFindSeparator.cpp) | Checks Find Separator behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [FindSeparator-inl.h](../FindSeparator-inl.h); [GenericGraph.h](../GenericGraph.h) | [gtsam_unstable/partition/tests/CMakeLists.txt](CMakeLists.txt) |
| [testGenericGraph.cpp](testGenericGraph.cpp) | Checks Generic Graph behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [GenericGraph.h](../GenericGraph.h); C++ standard/system library | None |
| [testNestedDissection.cpp](testNestedDissection.cpp) | Checks Nested Dissection behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); `GenericGraph.h`; `NonlinearTSAM.h`; `SubmapExamples.h`; `SubmapExamples3D.h`; 3 other declared imports/includes | [gtsam_unstable/partition/tests/CMakeLists.txt](CMakeLists.txt) |

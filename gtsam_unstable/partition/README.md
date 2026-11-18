# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [FindSeparator-inl.h](FindSeparator-inl.h) | Declares Find Separator inl types or operations. | [timing.h](../../gtsam/base/timing.h); [FindSeparator.h](FindSeparator.h); C++ standard/system library; `boost` headers; `metis.h` | [gtsam_unstable/CMakeLists.txt](../CMakeLists.txt); [NestedDissection-inl.h](NestedDissection-inl.h); [testFindSeparator.cpp](tests/testFindSeparator.cpp) |
| [FindSeparator.h](FindSeparator.h) | Declares Find Separator types or operations. | [Key.h](../../gtsam/inference/Key.h); [gtsam/inference/Symbol.h](../../gtsam/inference/Symbol.h); [PartitionWorkSpace.h](PartitionWorkSpace.h); C++ standard/system library | [gtsam_unstable/CMakeLists.txt](../CMakeLists.txt); [FindSeparator-inl.h](FindSeparator-inl.h) |
| [GenericGraph.cpp](GenericGraph.cpp) | Implements Generic Graph operations. | [DSFVector.h](../../gtsam/base/DSFVector.h); [GenericGraph.h](GenericGraph.h); C++ standard/system library | None |
| [GenericGraph.h](GenericGraph.h) | Declares Generic Graph types or operations. | [PartitionWorkSpace.h](PartitionWorkSpace.h); C++ standard/system library; `gtsam_unstable` headers | [GenericGraph.cpp](GenericGraph.cpp); [testFindSeparator.cpp](tests/testFindSeparator.cpp); [testGenericGraph.cpp](tests/testGenericGraph.cpp); 1 other source references |
| [NestedDissection-inl.h](NestedDissection-inl.h) | Declares Nested Dissection inl types or operations. | [NestedDissection.h](NestedDissection.h); `OrderedSymbols.h`; `partition` headers | [testNestedDissection.cpp](tests/testNestedDissection.cpp) |
| [NestedDissection.h](NestedDissection.h) | Declares Nested Dissection types or operations. | C++ standard/system library; `gtsam` headers | [NestedDissection-inl.h](NestedDissection-inl.h) |
| [PartitionWorkSpace.h](PartitionWorkSpace.h) | Declares Partition Work Space types or operations. | C++ standard/system library | [FindSeparator.h](FindSeparator.h); [GenericGraph.h](GenericGraph.h) |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [tests/](tests/README.md) | Indexes this maintained subfolder. | None | Developers |

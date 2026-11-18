# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [BTree.h](BTree.h) | purely functional binary tree. | C++ standard/system library | [stats.html](../../doc/stats.html); [base.md](../../gtsam/base/base.md); [DSF.h](DSF.h); 1 other source references |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [DSF.h](DSF.h) | An implementation of Disjoint set forests (see CLR page 446 and up). | [BTree.h](BTree.h); C++ standard/system library | [testDSF.cpp](tests/testDSF.cpp); [timeDSFvariants.cpp](../timing/timeDSFvariants.cpp) |
| [Dummy.cpp](Dummy.cpp) | Dummy class for testing MATLAB memory allocation. | [Dummy.h](Dummy.h); C++ standard/system library; `gtsam` headers | None |
| [Dummy.h](Dummy.h) | Dummy class for testing MATLAB memory allocation. | [global_includes.h](../../gtsam/global_includes.h); C++ standard/system library; `gtsam_unstable` headers; `gtsam` headers | [Dummy.cpp](Dummy.cpp) |
| [FixedVector.h](FixedVector.h) | Extension of boost's bounded_vector to allow for fixed size operation. | [Vector.h](../../gtsam/base/Vector.h); `gtsam` headers; `stdarg.h` | [testFixedVector.cpp](tests/testFixedVector.cpp) |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [tests/](tests/README.md) | Indexes this maintained subfolder. | None | Developers |

# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [base/](base/README.md) | Indexes this maintained subfolder. | None | Developers |
| [basis/](basis/README.md) | Indexes this maintained subfolder. | None | Developers |
| [certifiable/](certifiable/README.md) | Indexes this maintained subfolder. | None | Developers |
| [config.h.in](config.h.in) | Templates the generated config.h configuration. | None | [gtsam/CMakeLists.txt](CMakeLists.txt) |
| [constrained/](constrained/README.md) | Indexes this maintained subfolder. | None | Developers |
| [discrete/](discrete/README.md) | Indexes this maintained subfolder. | None | Developers |
| [geometry/](geometry/README.md) | Indexes this maintained subfolder. | None | Developers |
| [global_includes.h](global_includes.h) | Included from all GTSAM files. | [types.h](base/types.h); `gtsam` headers | [TimeTBB.cpp](../examples/TimeTBB.cpp); [ConcurrentMap.h](base/ConcurrentMap.h); [DSFVector.h](base/DSFVector.h); 17 other source references |
| [groups.dox](groups.dox) | Documents groups. | None | None |
| [gtsam.i](gtsam.i) | Declares gtsam wrapper interfaces or binding templates. | [Key.h](inference/Key.h); [gtsam/nonlinear/utilities.h](nonlinear/utilities.h) | [matlab/CMakeLists.txt](../matlab/CMakeLists.txt); [python/CMakeLists.txt](../python/CMakeLists.txt); [gtsam.tpl](../python/gtsam/gtsam.tpl); 2 other source references |
| [hybrid/](hybrid/README.md) | Indexes this maintained subfolder. | None | Developers |
| [inference/](inference/README.md) | Indexes this maintained subfolder. | None | Developers |
| [linear/](linear/README.md) | Indexes this maintained subfolder. | None | Developers |
| [mainpage.dox](mainpage.dox) | Documents mainpage. | None | None |
| [navigation/](navigation/README.md) | Indexes this maintained subfolder. | None | Developers |
| [nonlinear/](nonlinear/README.md) | Indexes this maintained subfolder. | None | Developers |
| [precompiled_header.h](precompiled_header.h) | Include headers that are used heavily, or are heavy to parse. | [ConcurrentMap.h](base/ConcurrentMap.h); [DSFVector.h](base/DSFVector.h); [FastDefaultAllocator.h](base/FastDefaultAllocator.h); [FastList.h](base/FastList.h); 39 other source includes | [gtsam/CMakeLists.txt](CMakeLists.txt) |
| [sam/](sam/README.md) | Indexes this maintained subfolder. | None | Developers |
| [sfm/](sfm/README.md) | Indexes this maintained subfolder. | None | Developers |
| [slam/](slam/README.md) | Indexes this maintained subfolder. | None | Developers |
| [symbolic/](symbolic/README.md) | Indexes this maintained subfolder. | None | Developers |

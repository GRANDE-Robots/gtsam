# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CCOLAMDSymbols.h](CCOLAMDSymbols.h) | Declares CCOLAMDSymbols types or operations. | None | [Ordering.cpp](../Ordering.cpp); [ccolamd_vendor.c](ccolamd_vendor.c); [suitesparse_config_vendor.c](suitesparse_config_vendor.c) |
| [CCOLAMDSymbolsUndef.h](CCOLAMDSymbolsUndef.h) | Declares CCOLAMDSymbols Undef types or operations. | None | [Ordering.cpp](../Ordering.cpp) |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [ccolamd_vendor.c](ccolamd_vendor.c) | Implements ccolamd vendor operations. | [ccolamd.c](../../3rdparty/CCOLAMD/Source/ccolamd.c); [CCOLAMDSymbols.h](CCOLAMDSymbols.h) | [gtsam/CMakeLists.txt](../../CMakeLists.txt) |
| [suitesparse_config_vendor.c](suitesparse_config_vendor.c) | Implements suitesparse config vendor operations. | [SuiteSparse_config.c](../../3rdparty/SuiteSparse_config/SuiteSparse_config.c); [CCOLAMDSymbols.h](CCOLAMDSymbols.h) | [gtsam/CMakeLists.txt](../../CMakeLists.txt) |

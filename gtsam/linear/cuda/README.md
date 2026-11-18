# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [DeviceSparseSpdSystem.cu](DeviceSparseSpdSystem.cu) | Persistent device storage for an int32 upper-CSR SPD system. | [DeviceSparseSpdSystem.h](DeviceSparseSpdSystem.h); C++ standard/system library | None |
| [DeviceSparseSpdSystem.h](DeviceSparseSpdSystem.h) | Persistent device storage for an int32 upper-CSR SPD system. | [DeviceArray.h](../../base/cuda/DeviceArray.h); [LinearSystem.h](LinearSystem.h); C++ standard/system library; `gtsam` headers | [gtsam/linear/CMakeLists.txt](../CMakeLists.txt); [DeviceSparseSpdSystem.cu](DeviceSparseSpdSystem.cu); [LinearSolver.h](LinearSolver.h); 6 other source references |
| [LinearSolver.cpp](LinearSolver.cpp) | Shared CUDA linear-solver session and backend selection. | [LinearSolver.h](LinearSolver.h); [CudssSpdSolver.h](internal/CudssSpdSolver.h); [DenseCholeskySolver.h](internal/DenseCholeskySolver.h); [PcgSolver.h](internal/PcgSolver.h); C++ standard/system library | None |
| [LinearSolver.h](LinearSolver.h) | Shared CUDA linear-solver session and backend selection. | [DeviceArray.h](../../base/cuda/DeviceArray.h); [DeviceSparseSpdSystem.h](DeviceSparseSpdSystem.h); [LinearSystem.h](LinearSystem.h); C++ standard/system library; `gtsam` headers | [gtsam/linear/CMakeLists.txt](../CMakeLists.txt); [LinearSolver.cpp](LinearSolver.cpp); [cuda_linear.i](cuda_linear.i); 12 other source references |
| [LinearSystem.h](LinearSystem.h) | Backend-independent views of the CUDA linear systems. | `cuda_runtime_api.h` | [gtsam/linear/CMakeLists.txt](../CMakeLists.txt); [DeviceSparseSpdSystem.h](DeviceSparseSpdSystem.h); [LinearSolver.h](LinearSolver.h); 3 other source references |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [cuda_linear.i](cuda_linear.i) | Declares cuda linear wrapper interfaces or binding templates. | [LinearSolver.h](LinearSolver.h) | [python/CMakeLists.txt](../../../python/CMakeLists.txt) |
| [internal/](internal/README.md) | Indexes this maintained subfolder. | None | Developers |

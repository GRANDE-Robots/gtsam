# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [Context.h](Context.h) | RAII owner of the CUDA stream and library handles. | [gtsam/base/cuda/Errors.h](Errors.h); `cuda_runtime_api.h` | [testCudaBase.cpp](../tests/testCudaBase.cpp); [testCudaNames.cpp](../tests/testCudaNames.cpp); [SparseLevenbergMarquardt.cpp](../../nonlinear/cuda/SparseLevenbergMarquardt.cpp); 4 other source references |
| [DeviceArray.h](DeviceArray.h) | Owning typed device allocation with transfer profiling. | [gtsam/base/cuda/Errors.h](Errors.h); C++ standard/system library; `cuda_runtime_api.h` | [testCudaBase.cpp](../tests/testCudaBase.cpp); [testCudaNames.cpp](../tests/testCudaNames.cpp); [DeviceSparseSpdSystem.h](../../linear/cuda/DeviceSparseSpdSystem.h); 15 other source references |
| [Errors.h](Errors.h) | Exception type and status checking for CUDA API calls. | C++ standard/system library; `cuda_runtime_api.h` | [Context.h](Context.h); [DeviceArray.h](DeviceArray.h); [PinnedHostArray.h](PinnedHostArray.h); 11 other source references |
| [PinnedHostArray.h](PinnedHostArray.h) | Owning pinned (page-locked) host allocation. | [gtsam/base/cuda/Errors.h](Errors.h); C++ standard/system library; `cuda_runtime_api.h` | [testCudaNames.cpp](../tests/testCudaNames.cpp); [PcgSolver.cu](../../linear/cuda/internal/PcgSolver.cu); [DeviceSparseJacobianNormalEquations.cu](../../nonlinear/cuda/internal/DeviceSparseJacobianNormalEquations.cu); 3 other source references |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |

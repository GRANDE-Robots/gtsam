# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [SfmLevenbergMarquardt.cu](SfmLevenbergMarquardt.cu) | Levenberg-Marquardt bundle adjustment that iterates on the GPU. | [Context.h](../../base/cuda/Context.h); [DeviceArray.h](../../base/cuda/DeviceArray.h); [gtsam/base/cuda/Errors.h](../../base/cuda/Errors.h); [NoiseModel.h](../../linear/NoiseModel.h); 14 other source includes; C++ standard/system library | None |
| [SfmLevenbergMarquardt.h](SfmLevenbergMarquardt.h) | Levenberg-Marquardt bundle adjustment that iterates on the GPU. | [gtsam/inference/Ordering.h](../../inference/Ordering.h); [LinearSolver.h](../../linear/cuda/LinearSolver.h); [LevenbergMarquardtParams.h](../../nonlinear/LevenbergMarquardtParams.h); [Values.h](../../nonlinear/Values.h); 3 other source includes; C++ standard/system library; `gtsam` headers | [SfmLevenbergMarquardt.cu](SfmLevenbergMarquardt.cu); [cuda_sfm.i](cuda_sfm.i); [testCudaSfm.cpp](../tests/testCudaSfm.cpp); 1 other source references |
| [SfmTypes.h](SfmTypes.h) | Trivially copyable measurement and noise types for CUDA SFM. | None | [gtsam/sfm/CMakeLists.txt](../CMakeLists.txt); [gtsam/sfm/cuda/SfmLevenbergMarquardt.h](SfmLevenbergMarquardt.h); [DeviceGeometryKernels.h](internal/DeviceGeometryKernels.h); 1 other source references |
| [cuda_sfm.i](cuda_sfm.i) | Declares cuda sfm wrapper interfaces or binding templates. | [GncOptimizer.h](../../nonlinear/GncOptimizer.h); [GncParams.h](../../nonlinear/GncParams.h); [LevenbergMarquardtParams.h](../../nonlinear/LevenbergMarquardtParams.h); [Values.h](../../nonlinear/Values.h); 3 other source includes | [python/CMakeLists.txt](../../../python/CMakeLists.txt) |
| [internal/](internal/README.md) | Indexes this maintained subfolder. | None | Developers |

# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [GncOutlierSampling.h](GncOutlierSampling.h) | Deterministic outlier sampling for GNC bundle-adjustment timing. | C++ standard/system library | [CudaSfmGncOptimizer.ipynb](../../gtsam/sfm/doc/CudaSfmGncOptimizer.ipynb); [testGncOutlierSampling.cpp](../../tests/testGncOutlierSampling.cpp); [timeCudaSFMBAL.cpp](timeCudaSFMBAL.cpp) |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [timeCudaSFMBAL.cpp](timeCudaSFMBAL.cpp) | time CUDA SFM/BA with BAL files. | [gtsam/base/cuda/Errors.h](../../gtsam/base/cuda/Errors.h); [gtsam/inference/Symbol.h](../../gtsam/inference/Symbol.h); [GaussianFactorGraph.h](../../gtsam/linear/GaussianFactorGraph.h); [BatchFactor.h](../../gtsam/nonlinear/BatchFactor.h); 9 other source includes; C++ standard/system library; `gtsam` headers | [CudaSfmGncOptimizer.ipynb](../../gtsam/sfm/doc/CudaSfmGncOptimizer.ipynb); [timing/README.md](../README.md) |

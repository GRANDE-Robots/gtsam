# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [SparseLevenbergMarquardt.cpp](SparseLevenbergMarquardt.cpp) | Levenberg-Marquardt with a persistent CUDA sparse linear system. | [Context.h](../../base/cuda/Context.h); [types.h](../../base/types.h); [LinearSolver.h](../../linear/cuda/LinearSolver.h); [BlockOrdering.h](../../linear/cuda/internal/BlockOrdering.h); 10 other source includes; C++ standard/system library; `cuda_runtime_api.h`; `gtsam` headers | [SparseLevenbergMarquardtOptimizer.ipynb](../doc/SparseLevenbergMarquardtOptimizer.ipynb) |
| [SparseLevenbergMarquardt.h](SparseLevenbergMarquardt.h) | Levenberg-Marquardt with a persistent CUDA sparse linear system. | [LinearSolver.h](../../linear/cuda/LinearSolver.h); [LevenbergMarquardtParams.h](../LevenbergMarquardtParams.h); [NonlinearFactorGraph.h](../NonlinearFactorGraph.h); [Values.h](../Values.h); C++ standard/system library; `gtsam` headers | [CUDA_LINEAR_SOLVERS.md](../../../doc/CUDA_LINEAR_SOLVERS.md); [gtsam/nonlinear/CMakeLists.txt](../CMakeLists.txt); [SparseLevenbergMarquardt.cpp](SparseLevenbergMarquardt.cpp); 7 other source references |
| [cuda_nonlinear.i](cuda_nonlinear.i) | Declares cuda nonlinear wrapper interfaces or binding templates. | [GncOptimizer.h](../GncOptimizer.h); [GncParams.h](../GncParams.h); [LevenbergMarquardtParams.h](../LevenbergMarquardtParams.h); [NonlinearFactorGraph.h](../NonlinearFactorGraph.h); 2 other source includes | [python/CMakeLists.txt](../../../python/CMakeLists.txt) |
| [internal/](internal/README.md) | Indexes this maintained subfolder. | None | Developers |

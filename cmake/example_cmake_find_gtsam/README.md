# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [main.cpp](main.cpp) | A 2D Pose SLAM example. | [Pose2.h](../../gtsam/geometry/Pose2.h); [Key.h](../../gtsam/inference/Key.h); [GaussNewtonOptimizer.h](../../gtsam/nonlinear/GaussNewtonOptimizer.h); [Marginals.h](../../gtsam/nonlinear/Marginals.h); 3 other source includes | None |

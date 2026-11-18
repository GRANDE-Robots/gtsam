# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [timeCudaSparseLM.cpp](timeCudaSparseLM.cpp) | time the general CUDA sparse Levenberg-Marquardt optimizer. | [Cal3_S2Stereo.h](../../gtsam/geometry/Cal3_S2Stereo.h); [Pose2.h](../../gtsam/geometry/Pose2.h); [Pose3.h](../../gtsam/geometry/Pose3.h); [StereoPoint2.h](../../gtsam/geometry/StereoPoint2.h); 10 other source includes; C++ standard/system library; `cuda_runtime_api.h` | None |

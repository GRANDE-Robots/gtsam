# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [EqVIOCommon.h](EqVIOCommon.h) | Common EqVIO math/data types for unstable navigation. | [Lie.h](../../gtsam/base/Lie.h); [gtsam/base/Matrix.h](../../gtsam/base/Matrix.h); [ProductLieGroup.h](../../gtsam/base/ProductLieGroup.h); [Vector.h](../../gtsam/base/Vector.h); 10 other source includes; C++ standard/system library; `gtsam_unstable` headers | [EqVIOState.h](EqVIOState.h); [EqVIOSymmetry.h](EqVIOSymmetry.h); [testEqVIOGroup.cpp](tests/testEqVIOGroup.cpp); 1 other source references |
| [EqVIOFilter.cpp](EqVIOFilter.cpp) | Standalone equivariant VIO filter. | [EqVIOFilter.h](EqVIOFilter.h); C++ standard/system library | None |
| [EqVIOFilter.h](EqVIOFilter.h) | Standalone equivariant VIO filter. | [EquivariantFilter.h](../../gtsam/navigation/EquivariantFilter.h); [EqVIOSymmetry.h](EqVIOSymmetry.h); C++ standard/system library; `gtsam_unstable` headers | [EqVIOReplayHelper.h](../examples/EqVIOReplayHelper.h); [gtsam_unstable.i](../gtsam_unstable.i); [EqVIOFilter.cpp](EqVIOFilter.cpp); 1 other source references |
| [EqVIOState.cpp](EqVIOState.cpp) | Dynamic EqVIO manifold state implementation. | [MatrixConstants.h](../../gtsam/base/MatrixConstants.h); [EqVIOState.h](EqVIOState.h) | None |
| [EqVIOState.h](EqVIOState.h) | Dynamic EqVIO manifold state. | [Lie.h](../../gtsam/base/Lie.h); [gtsam/base/Matrix.h](../../gtsam/base/Matrix.h); [Vector.h](../../gtsam/base/Vector.h); [Point3.h](../../gtsam/geometry/Point3.h); 2 other source includes; C++ standard/system library; `gtsam_unstable` headers | [gtsam_unstable.i](../gtsam_unstable.i); [EqVIOState.cpp](EqVIOState.cpp); [EqVIOSymmetry.h](EqVIOSymmetry.h); 2 other source references |
| [EqVIOSymmetry.cpp](EqVIOSymmetry.cpp) | EqVIO symmetry actions and lift helpers. | [EqVIOSymmetry.h](EqVIOSymmetry.h); C++ standard/system library | None |
| [EqVIOSymmetry.h](EqVIOSymmetry.h) | EqVIO symmetry actions and lift helpers. | [GroupAction.h](../../gtsam/base/GroupAction.h); [gtsam/base/Matrix.h](../../gtsam/base/Matrix.h); [Vector.h](../../gtsam/base/Vector.h); [EqVIOCommon.h](EqVIOCommon.h); 1 other source includes; `gtsam_unstable` headers | [EqVIOFilter.h](EqVIOFilter.h); [EqVIOSymmetry.cpp](EqVIOSymmetry.cpp); [testEqVIOSymmetry.cpp](tests/testEqVIOSymmetry.cpp) |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [tests/](tests/README.md) | Indexes this maintained subfolder. | None | Developers |

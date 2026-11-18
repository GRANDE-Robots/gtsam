# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [__init__.py](__init__.py) | Module definition file for GTSAM. | Python standard library; `gtsam`; `numpy` | None |
| [examples/](examples/README.md) | Indexes this maintained subfolder. | None | Developers |
| [gtsam.tpl](gtsam.tpl) | Declares gtsam wrapper interfaces or binding templates. | [gtsam/base/serialization.h](../../gtsam/base/serialization.h); [gtsam/base/utilities.h](../../gtsam/base/utilities.h); [optional_jacobian_pybind.h](optional_jacobian_pybind.h); `boost` headers; `gtsam` headers; `pybind11` headers; `python` headers | [python/CMakeLists.txt](../CMakeLists.txt) |
| [gtsfm.py](gtsfm.py) | Provides the gtsfm Python module. | `gtsam` | None |
| [imuBias.py](imuBias.py) | Provides the imu Bias Python module. | `gtsam` | None |
| [noiseModel.py](noiseModel.py) | Provides the noise Model Python module. | `gtsam` | None |
| [notebooks/](notebooks/README.md) | Indexes this maintained subfolder. | None | Developers |
| [optional_jacobian_pybind.h](optional_jacobian_pybind.h) | Declares optional jacobian pybind types or operations. | [gtsam/base/Matrix.h](../../gtsam/base/Matrix.h); [OptionalJacobian.h](../../gtsam/base/OptionalJacobian.h); C++ standard/system library; `pybind11` headers | [gtsam.tpl](gtsam.tpl); [python/gtsam/preamble/custom.h](preamble/custom.h); [gtsam_unstable.tpl](../gtsam_unstable/gtsam_unstable.tpl) |
| [preamble/](preamble/README.md) | Indexes this maintained subfolder. | None | Developers |
| [py.typed](py.typed) | Marks the Python package as providing typing information. | None | None |
| [specializations/](specializations/README.md) | Indexes this maintained subfolder. | None | Developers |
| [symbol_shorthand.py](symbol_shorthand.py) | Provides the symbol shorthand Python module. | `gtsam` | None |
| [tests/](tests/README.md) | Indexes this maintained subfolder. | None | Developers |
| [utils/](utils/README.md) | Indexes this maintained subfolder. | None | Developers |

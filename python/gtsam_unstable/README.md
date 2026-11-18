# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [__init__.py](__init__.py) | Defines the Python package's import surface. | `gtsam_unstable` | None |
| [examples/](examples/README.md) | Indexes this maintained subfolder. | None | Developers |
| [gtsam_unstable.tpl](gtsam_unstable.tpl) | Declares gtsam unstable wrapper interfaces or binding templates. | [gtsam/base/serialization.h](../../gtsam/base/serialization.h); [gtsam/base/utilities.h](../../gtsam/base/utilities.h); [NoiseModel.h](../../gtsam/linear/NoiseModel.h); [optional_jacobian_pybind.h](../gtsam/optional_jacobian_pybind.h); 2 other source includes; `boost` headers; `pybind11` headers | [python/CMakeLists.txt](../CMakeLists.txt) |
| [preamble.h](preamble.h) | Declares preamble types or operations. | None | [gtsam_unstable.tpl](gtsam_unstable.tpl); [DOCS.md](../../wrap/DOCS.md) |
| [py.typed](py.typed) | Marks the Python package as providing typing information. | None | None |
| [specializations/](specializations/README.md) | Indexes this maintained subfolder. | None | Developers |
| [tests/](tests/README.md) | Indexes this maintained subfolder. | None | Developers |

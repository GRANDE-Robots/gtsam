# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [arg_policies.h](arg_policies.h) | Declares arg policies types or operations. | [gtsam/base/Matrix.h](../../../gtsam/base/Matrix.h) | [python/gtsam/preamble/geometry.h](geometry.h); [python/gtsam/preamble/gtsam.h](gtsam.h); [python/gtsam/preamble/navigation.h](navigation.h); 1 other source references |
| [base.h](base.h) | Declares base types or operations. | None | None |
| [basis.h](basis.h) | Declares basis types or operations. | None | None |
| [cameras.h](cameras.h) | Declares cameras types or operations. | None | None |
| [certifiable.h](certifiable.h) | Declares certifiable types or operations. | None | None |
| [certifiable_mosek.h](certifiable_mosek.h) | Declares certifiable mosek types or operations. | None | None |
| [constrained.h](constrained.h) | Declares constrained types or operations. | None | None |
| [cuda_linear.h](cuda_linear.h) | Declares cuda linear types or operations. | None | None |
| [cuda_nonlinear.h](cuda_nonlinear.h) | Declares cuda nonlinear types or operations. | None | None |
| [cuda_sfm.h](cuda_sfm.h) | Declares cuda sfm types or operations. | None | None |
| [custom.h](custom.h) | Declares custom types or operations. | None | None |
| [discrete.h](discrete.h) | Declares discrete types or operations. | None | None |
| [geometry.h](geometry.h) | Declares geometry types or operations. | [arg_policies.h](arg_policies.h) | None |
| [gtsam.h](gtsam.h) | Declares gtsam types or operations. | [arg_policies.h](arg_policies.h) | None |
| [hybrid.h](hybrid.h) | Declares hybrid types or operations. | None | None |
| [inference.h](inference.h) | Declares inference types or operations. | `pybind11` headers | None |
| [linear.h](linear.h) | Declares linear types or operations. | None | None |
| [navigation.h](navigation.h) | Declares navigation types or operations. | [arg_policies.h](arg_policies.h) | None |
| [nonlinear.h](nonlinear.h) | Declares nonlinear types or operations. | None | None |
| [sam.h](sam.h) | Declares sam types or operations. | None | None |
| [sfm.h](sfm.h) | Declares sfm types or operations. | None | None |
| [slam.h](slam.h) | Declares slam types or operations. | [arg_policies.h](arg_policies.h) | None |
| [symbolic.h](symbolic.h) | Declares symbolic types or operations. | None | None |
| [values.h](values.h) | Declares values types or operations. | None | None |

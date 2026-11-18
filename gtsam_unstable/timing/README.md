# Unstable Timing Benchmarks

## Sparse Hybrid AllDiff Multiplication

`timeHybridAllDiff` separates the two performance improvements involved in
multiplying a `TableFactor` by `AllDiff`:

- `decision_tree` reproduces the original conversion through a
  `DecisionTreeFactor`;
- `copied_table` uses sparse `AllDiff` conversion but reproduces the former
  generic dispatch, including its copy of the input table;
- `direct_table` uses the current virtual `toTableFactor()` dispatch and
  borrows the input table by reference.

The benchmark checks that all three products are numerically identical before
timing them. It reports full-scope and partial-scope multiplication separately,
including both the speedup over decision-tree conversion and the incremental
speedup from removing the input-table copy.

Build and run it from the build directory:

```bash
make -j6 timeHybridAllDiff
./gtsam_unstable/timing/timeHybridAllDiff \
  --minimum-objects 3 --maximum-objects 7 --warmup 1 --repeats 5
```

Use `--output hybrid_all_diff.json` to retain the medians in Benchmark Action
JSON format.

## File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [process_shonan_timing_results.py](process_shonan_timing_results.py) | Process timing results from timeShonanAveraging. | Python standard library; `matplotlib`; `numpy`; `xlrd` | None |
| [timeDSFvariants.cpp](timeDSFvariants.cpp) | Time different implementations of DSF. | [DSFMap.h](../../gtsam/base/DSFMap.h); [DSFVector.h](../../gtsam/base/DSFVector.h); [timing.h](../../gtsam/base/timing.h); [DSF.h](../base/DSF.h); C++ standard/system library | None |
| [timeDSFvariants.xlsx](timeDSFvariants.xlsx) | Retains the time DSFvariants example or reference data. | None | None |
| [timeDSFvariants2.xlsx](timeDSFvariants2.xlsx) | Retains the time DSFvariants2 example or reference data. | None | None |
| [timeHybridAllDiff.cpp](timeHybridAllDiff.cpp) | Benchmark sparse AllDiff multiplication and table dispatch. | [gtsam/discrete/AllDiff.h](../../gtsam/discrete/AllDiff.h); [DecisionTreeFactor.h](../../gtsam/discrete/DecisionTreeFactor.h); [TableFactor.h](../../gtsam/discrete/TableFactor.h); [gtsam/inference/Symbol.h](../../gtsam/inference/Symbol.h); C++ standard/system library; `Eigen` headers; `internal` headers | [timing/README.md](../../timing/README.md) |
| [timeInertialNavFactor_GlobalVelocity.cpp](timeInertialNavFactor_GlobalVelocity.cpp) | Unit test for the InertialNavFactor_GlobalVelocity. | [Pose3.h](../../gtsam/geometry/Pose3.h); [Key.h](../../gtsam/inference/Key.h); [GaussianFactorGraph.h](../../gtsam/linear/GaussianFactorGraph.h); [ImuBias.h](../../gtsam/navigation/ImuBias.h); 2 other source includes; C++ standard/system library; `gtsam` headers | [stats.html](../../doc/stats.html); [gtsam_unstable/timing/CMakeLists.txt](CMakeLists.txt) |
| [timeShonanAveraging.cpp](timeShonanAveraging.cpp) | Timing script for Shonan Averaging algorithm. | [TestHarness.h](../../CppUnitLite/TestHarness.h); [gtsam/base/Matrix.h](../../gtsam/base/Matrix.h); [Vector.h](../../gtsam/base/Vector.h); [timing.h](../../gtsam/base/timing.h); 3 other source includes; C++ standard/system library | None |

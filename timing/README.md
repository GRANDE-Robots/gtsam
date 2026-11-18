# Timing Benchmarks

This directory contains timing executables and helper scripts for GTSAM.

## Shared timing conventions

Modern benchmarks share the private support library in `timing/internal`.
`Arguments` provides consistent typed command-line parsing, timing helpers use
`std::chrono::steady_clock`, and `TimingSummary` records the statistical
definitions already used by the individual programs. In particular, callers
must select either the averaged-middle or upper-middle median policy so that a
migration does not silently change historical results.

Warmups execute before the measured repetitions, and harness work such as
argument parsing, sample aggregation, formatting, and file creation remains
outside the timed callable. Output files are checked when opened and missing
parent directories are created. Benchmark Action JSON uses the shared
`BenchmarkMetric` writer to keep names, units, numeric precision, and escaping
consistent.

These helpers are private to the timing targets and do not add public GTSAM
API. Legacy `gttic_` microbenchmarks continue to use `gtsam/base/timing` and are
not candidates for migration to this harness.

## Hybrid Inference Benchmark

`timeHybridInference` constructs a small 2D data-association problem with a
sparse one-to-one association constraint using only core GTSAM APIs. It times
the four tutorial-level hybrid inference operations independently: sequential
Bayes-net creation, Bayes-net optimization, multifrontal Bayes-tree creation,
and Bayes-tree optimization. Creation performs sum-product elimination, while
optimization obtains the max-product assignment and its continuous solution.
The executable verifies that the sequential and multifrontal solutions agree
before collecting timings.

Build and run it from the build directory:

```bash
make -j6 timeHybridInference
./timing/timeHybridInference --objects 3 --warmup 1 --repeats 10 \
  --iterations 10 --output hybrid_inference.json
```

The AllDiff-specific table-dispatch comparison lives in
`gtsam_unstable/timing/timeHybridAllDiff.cpp`.

## BetweenFactor Jacobian Benchmark

`timeBetweenFactor` measures `BetweenFactor<Rot3>::evaluateError` with both
Jacobians requested at a nonzero residual. It also reports maximum absolute
differences from numerical Jacobians outside the timed region. This migrates
the experiment from PR 88 into a standalone, reproducible timing target.
The current factor and an exact copy of the legacy Jacobian path are timed in
alternating order within each repetition, reducing CPU-frequency drift in the
comparison.

Build and run it from the build directory:

```bash
make -j6 timeBetweenFactor
./timing/timeBetweenFactor --warmup 5 --repeats 20 \
  --iterations 100000 --output between_factor.json
```

With `GTSAM_SLOW_BUT_CORRECT_BETWEENFACTOR=ON`, the output directly compares
the corrected Local-Jacobian path with the legacy approximation. The optional
output uses the shared Benchmark Action JSON format.

### End-to-end pose-graph optimization

`timeBetweenFactorPoseGraph` assesses whether the more expensive Jacobians
change nonlinear convergence enough to offset their per-evaluation cost. It
loads `w10000.graph`, anchors pose zero, computes one shared FAST-Sync
initialization, and then runs Levenberg-Marquardt to its standard termination
condition on two otherwise identical graphs. FAST-Sync is outside the timed
refinements. The current factors and benchmark-only copies of the legacy
`BetweenFactor` and `PriorFactor` Jacobian paths are run in alternating order.

```bash
make -j6 timeBetweenFactorPoseGraph
./timing/timeBetweenFactorPoseGraph --warmup 1 --repeats 5 \
  --dataset w10000.graph --output between_factor_pose_graph.json
```

Pass `--raw-initial` only to reproduce the difficult uninitialized convergence
diagnostic.

BAL benchmarks additionally share `BalBenchmarkConfig` and the builders in
`timing/internal/SfmBalBenchmark`. The configuration carries ordering and
projection-noise choices explicitly; timing headers no longer define mutable
globals or inject the `std` and `gtsam` namespaces. Dataset selection, initial
values, point- and camera-batch graph variants, orderings, and LM defaults live
in that component. The end-to-end full-system and reduced-camera PCG comparison
is isolated in `SfmPcgBenchmark` so `timeSFMBAL.cpp` remains focused on selecting
and reporting benchmark modes.

## Public SFM Solver Matrix

The public CPU matrix is implemented by `timeSfmPartialElimination.cpp`. The
CUDA matrix uses the public `gtsam::cuda::SfmLevenbergMarquardtOptimizer` path
in `sfm_ba/timeCudaSFMBAL.cpp`; it does not use the former
`SfmFullNormalProblem` timing path or a CPU fallback.

### Recorded environment

The August 21, 2026 measurements used Ubuntu 24.04.4 LTS with Linux
7.0.0-28-generic on an Intel Core i7-14700F: one socket, 20 physical cores, 28
logical CPUs, one NUMA node, and 31 GiB RAM. The NVIDIA GeForce RTX 5060 Ti had
compute capability 12.0 and 16,311 MiB VRAM with driver 580.173.02.

The Release build used GNU C++ 13.3.0, CMake 4.2.3, CUDA toolkit 13.0.88,
cuDSS 0.8.0, CHOLMOD 5.3.1, and SuiteSparse_config 7.10.1. CMake detected the
Ubuntu TBB 2021.11.0 package. Because the CHOLMOD conda directory precedes the
system directory in the generated runpath, the executables loaded ABI-compatible
TBB 2021.13.0 at runtime. The exact configuration was:

```bash
cmake -S . -B build-cuda \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CUDA_COMPILER=/usr/local/cuda-13.0/bin/nvcc \
  -DCMAKE_CUDA_ARCHITECTURES=native \
  '-DCMAKE_CXX_FLAGS_RELEASE=-O3 -DNDEBUG' \
  '-DCMAKE_CUDA_FLAGS_RELEASE=-O3 -DNDEBUG' \
  -DGTSAM_ENABLE_CUDA=ON -DGTSAM_ENABLE_CUDSS=ON \
  -DCUDSS_ROOT=/home/dellaert/.local/opt/cudss-0.8.0-cuda13 \
  -DGTSAM_WITH_TBB=ON \
  -DTBB_DIR=/usr/lib/x86_64-linux-gnu/cmake/TBB \
  -DCHOLMOD_DIR=/home/dellaert/miniconda3/envs/gtsfm-v1/lib/cmake/CHOLMOD \
  -DSuiteSparse_config_DIR=/home/dellaert/miniconda3/envs/gtsfm-v1/lib/cmake/SuiteSparse_config \
  -DGTSAM_BUILD_TIMING_ALWAYS=ON -DGTSAM_BUILD_TESTS=ON \
  -DGTSAM_BUILD_DOCS=ON -DGTSAM_BUILD_PYTHON=OFF
cmake --build build-cuda --target \
  timeSfmPartialElimination timeCudaSFMBAL -j6
```

### CPU procedure and results

Each cell was measured in three separate invocations under a hard five-minute
process limit. The datasets were `dubrovnik-16-22106-pre.txt`,
`dubrovnik-88-64298-pre.txt`, and `dubrovnik-135-90642-pre.txt`.

```bash
timeout 300s build-cuda/timing/timeSfmPartialElimination \
  --repetitions 1 --max-seconds 300 \
  --configuration 'CONFIGURATION' examples/Data/DATASET
```

The exact configuration names use a `Full/` or `Schur/` prefix followed by
`MultifrontalSolver`, `MultifrontalCholesky`, `MultifrontalQR`,
`SequentialCholesky`, `SequentialQR`, `PCG`, `SubgraphSolver`, or `CHOLMOD`.
The program creates one natural-points/METIS-cameras ordering per dataset and
reuses it. Data loading, ordering, and optimizer construction are excluded.

Values are medians in seconds, sorted by completed BAL-135 time. A dash means
the run reached the five-minute cap.

| Configuration | BAL-16 | BAL-88 | BAL-135 |
| --- | ---: | ---: | ---: |
| Schur/MultifrontalSolver | 0.258 | 1.003 | 1.419 |
| Full/MultifrontalSolver | 0.252 | 1.001 | 1.423 |
| Schur/MultifrontalCholesky | 0.422 | 1.378 | 2.009 |
| Schur/CHOLMOD | 0.454 | 1.429 | 2.035 |
| Schur/SequentialCholesky | 0.423 | 1.394 | 2.048 |
| Schur/PCG | 0.426 | 1.515 | 2.054 |
| Full/MultifrontalCholesky | 0.531 | 1.866 | 2.968 |
| Schur/MultifrontalQR | 0.430 | 2.266 | 3.227 |
| Full/SequentialCholesky | 0.843 | 3.456 | 4.412 |
| Full/PCG | 0.658 | 3.826 | 4.646 |
| Full/CHOLMOD | 1.293 | 5.418 | 6.293 |
| Schur/SequentialQR | 0.441 | 4.309 | 12.446 |
| Full/SequentialQR | 3.813 | 121.922 | - |
| Full/MultifrontalQR | 4.984 | 152.545 | - |
| Full/SubgraphSolver | unsupported | unsupported | unsupported |
| Schur/SubgraphSolver | unsupported | unsupported | unsupported |

Both SubgraphSolver modes fail before the first LM iteration because the
spanning-tree builder only uses unary and binary factors, while these graphs
contain higher-arity factors. Full multifrontal and sequential QR both reached
the BAL-135 cap.

### Hybrid multifrontal parent-gather acceptance

The August 24, 2026 focused rerun measured the hybrid parent-gather candidate
on the same i7-14700F host and toolchain. Three detached worktrees used
identical CPU-only Release builds with TBB enabled:

| Role | Measured commit | Rebased PR commit |
| --- | --- | --- |
| Original parent-gather baseline | `dd79e05e9` | not part of the PR |
| Linear-cleanup reference plus timing harness | `f02e1bcb8` | `fe9a1352c` |
| Hybrid parent-gather candidate | `bbd2864f9` | `b95413654` |

`git range-diff` reports the cleanup and candidate patches as identical before
and after the rebase.

All processes were pinned to logical CPUs 0-20. The regular-factor benchmark
also set `--threads 21` explicitly; the SFM benchmark used the solver's normal
three-quarter-hardware default, which is 21 threads on this 28-CPU host. The
build command for each worktree was:

```bash
cmake -S SOURCE -B BUILD -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  '-DCMAKE_CXX_FLAGS_RELEASE=-O3 -DNDEBUG' \
  -DGTSAM_WITH_TBB=ON -DGTSAM_ENABLE_CUDA=OFF \
  -DGTSAM_BUILD_TIMING_ALWAYS=ON -DGTSAM_BUILD_TESTS=OFF \
  -DGTSAM_BUILD_EXAMPLES_ALWAYS=OFF -DGTSAM_BUILD_UNSTABLE=OFF \
  -DGTSAM_BUILD_PYTHON=OFF
cmake --build BUILD -j6 --target \
  timeMultifrontalSolver timeSfmPartialElimination
```

The regular graph command measures two eliminate-and-solve iterations after
one untimed warmup:

```bash
taskset -c 0-20 BUILD/timing/timeMultifrontalSolver \
  --bal-dataset DATASET --samples SAMPLES --iterations 2 --threads 21
```

BAL-16 and BAL-88 are three-sample diagnostics. BAL-135 is the formal gate:
seven separate one-sample baseline/candidate invocations, alternating which
binary ran first. Negative changes are improvements.

| Dataset | `dd79e05e9` s | `f02e1bcb8` s | `bbd2864f9` s | Candidate vs. original | Result |
| --- | ---: | ---: | ---: | ---: | --- |
| BAL-16 | 0.168448 | 0.168262 | 0.058755 | -65.1% | diagnostic pass |
| BAL-88 | 2.608010 | 2.580410 | 0.942307 | -63.9% | diagnostic pass |
| BAL-135 | 4.955640 | - | 2.199900 | **-55.6%** | **passes the 5% gate** |

The point-batched public SFM path used one optimizer repetition per BAL-135
invocation and cycled the baseline, cleanup, and candidate run order. BAL-16
and BAL-88 used three repetitions per diagnostic invocation:

```bash
taskset -c 0-20 BUILD/timing/timeSfmPartialElimination \
  --repetitions REPETITIONS --max-seconds 300 \
  --configuration 'Full/MultifrontalSolver' examples/Data/DATASET
# Repeat with Schur/MultifrontalSolver.
```

The no-regression limit is at most 3% slower than both references. All six
candidate medians pass; negative percentages are faster.

| Dataset | Mode | `dd79e05e9` s | `f02e1bcb8` s | `bbd2864f9` s | Vs. original | Vs. cleanup |
| --- | --- | ---: | ---: | ---: | ---: | ---: |
| BAL-16 | Full | 0.231144 | 0.230305 | 0.228180 | -1.3% | -0.9% |
| BAL-16 | Schur | 0.230632 | 0.228250 | 0.228183 | -1.1% | -0.03% |
| BAL-88 | Full | 0.889642 | 0.880253 | 0.868962 | -2.3% | -1.3% |
| BAL-88 | Schur | 0.893126 | 0.877075 | 0.873318 | -2.2% | -0.4% |
| BAL-135 | Full | 1.432247 | 1.429569 | 1.436844 | +0.3% | +0.5% |
| BAL-135 | Schur | 1.421049 | 1.418110 | 1.426606 | +0.4% | +0.6% |

Full and Schur produced identical results in every build: final objectives of
18,033.914832, 291,581.106404, and 377,782.056028 with respectively 5/5, 4/4,
and 2/2 LM/inner iterations on BAL-16, BAL-88, and BAL-135.

Peak full-process RSS for the regular BAL-135 command fell from 4,065,540 KiB
to 3,957,944 KiB, a reduction of 105.1 MiB (2.65%). The process peak includes
the loaded graph and factorization state, so it understates the scratch-memory
reduction itself.

These focused results supersede only the two `MultifrontalSolver` rows when
evaluating the hybrid gather change. The complete solver matrix above remains
the August 21 record for comparisons with the other solver families.

### CUDA procedure and results

The CUDA runs used point-batched graphs and Schur elimination. Each command was
run three times under the same hard cap. Dataset loading and optimizer
construction are excluded, and CUDA is synchronized immediately before and
after the timed `optimize()` call.

```bash
build-cuda/timing/sfm_ba/timeCudaSFMBAL --list-configurations
timeout 300s build-cuda/timing/sfm_ba/timeCudaSFMBAL \
  --cuda-lm-graph --cuda-lm-graph-kind point-batch \
  --configuration CONFIGURATION --output-format json \
  examples/Data/DATASET
```

`CONFIGURATION` was `schur-dense`, `schur-cudss-auto`,
`schur-cudss-gtsam`, or `schur-pcg`. Values are medians in seconds.

| Configuration | BAL-16 | BAL-88 | BAL-135 |
| --- | ---: | ---: | ---: |
| Schur/dense Cholesky | 0.055 | 0.218 | 0.290 |
| Schur/cuDSS, automatic ordering | 0.093 | 0.790 | 1.104 |
| Schur/cuDSS, GTSAM ordering | 0.093 | 0.786 | 1.107 |
| Schur/PCG | 0.164 | 1.127 | 1.282 |

CUDA Full is reserved but not implemented. Selecting it produces
`CUDA SFM Full elimination mode is not implemented; select Schur.`

### Correctness observations

All completed repetitions had stable objectives and iteration counts. Full and
Schur `MULTIFRONTAL_SOLVER` agreed at 18,033.914832, 291,581.106404, and
377,782.056028. Direct Full CPU solvers and direct CUDA backends converged near
18,034.103054, 291,611.296974, and 378,041.329924. Explicit-Schur CPU direct
solvers converged near 18,122.993769, 293,146.832936, and 378,183.228886. The
largest objective spread across completed CPU configurations was 0.61%.

These are end-to-end optimizer timings, not fixed reduced-system
microbenchmarks. Numerical differences can alter LM trajectories and iteration
counts, so final objectives and iteration counts should accompany elapsed-time
comparisons.

`timeSFMBALsmart` compares camera-only, structureless bundle adjustment using
smart factors. Its default run reports Hessian smart factors with multifrontal
Cholesky, Hessian smart factors with parallel block-Jacobi PCG, and implicit
Schur smart factors with the same PCG solver. The implicit-Schur case exercises
the common preindexed `FlatGaussianFactor` kernels also used by compact batch
factors. Use `--cholesky-only` or
`--pcg-only` to select a subset, or isolate one iterative representation with
`--hessian-pcg-only` or `--implicit-schur-pcg-only`. Use
`--benchmark-action-json FILE` for machine-readable timing output.

```bash
make -j6 timeSFMBALsmart
./timing/timeSFMBALsmart examples/Data/dubrovnik-16-22106-pre.txt
```

When CHOLMOD is available, the compact explicit-point sparse Schur backend can
be run independently:

```bash
./timing/timeSFMBAL --point-batch-schur-cholmod-only \
  /path/to/dubrovnik-88-64298-pre.txt
```

The backend assembles packed 9x9 camera blocks, reuses symbolic analysis while
recomputing the numeric factorization for each LM system, and reports assembly,
factor-and-solve, and point back-substitution times separately. CHOLMOD is an
optional timing dependency; all normal targets continue to build without it,
and selecting this mode in such a build reports a clear runtime error.

## RangeFactor Plaza2 Benchmark

This benchmark isolates the current range-only Plaza2 incremental SLAM workload
used by `RangeFactor<Pose2, Point2>`. It exists to support before/after
performance comparisons when changing the `RangeFactor` implementation.

### Build

From the build directory:

```bash
make -j6 timeRangeFactorPlaza2
```

### Run the benchmark executable

Run from `build/`:

```bash
./timing/timeRangeFactorPlaza2 --warmup 1 --repeats 5 \
  --output ../timing/results/range_factor_plaza2.csv
```

This prints aggregate timing statistics and writes one CSV row per measured run.

### Run the helper script

Run from the repository root with the `py312` conda environment:

```bash
conda run -n py312 python timing/benchmark_range_factor_plaza2.py \
  --build-dir build \
  --warmup 1 \
  --repeats 5 \
  --output timing/results/range_factor_plaza2.csv
```

The helper script runs the benchmark executable, preserves the CSV, and prints a
short summary that can be copied into a PR description.

## Arbitrary-Arity Fixed Jacobian Benchmark

`timeFixedJacobianFactor` compares a four-key `JacobianFactor` with
`FixedJacobianFactor<2,1,2,1,2>`. It measures nonlinear linearization, delta
error, Hessian-diagonal accumulation, and whole and ranged Hessian assembly.
The executable alternates mode order and verifies equal linear factors and
Hessians before timing.

From the build directory:

```bash
make -j6 timeFixedJacobianFactor
./timing/timeFixedJacobianFactor --trials 9 \
  --linearize-iterations 100000 --kernel-iterations 200000
```

## Binary Factor Pose-Graph Benchmark

This benchmark compares the automatic fixed-size binary linearization of
`BetweenFactor<Pose2>` with an explicitly qualified generic
`NoiseModelFactor::linearize()` control. Both modes use the same graph, initial
values, COLAMD ordering, and fixed number of Levenberg-Marquardt iterations.
Trial order alternates to reduce systematic timing drift, and the executable
checks that both modes produce equivalent final errors and poses.

From the build directory:

```bash
make -j6 timeBinaryFactorPoseGraph
./timing/timeBinaryFactorPoseGraph \
  --dataset w10000.graph \
  --warmup 1 \
  --repeats 7 \
  --linearize-repeats 3 \
  --iterations 10 \
  --output ../timing/results/binary_factor_pose_graph.csv
```

The console summary reports generic and binary medians plus the median paired
percentage change. The optional CSV contains one row per mode and measured
trial for more detailed analysis.

## Ternary Factor Benchmarks

`timeTernarySfmBAL` compares variable-calibration BAL in three forms: a split
Pose3/Point3/Cal3Bundler graph forced through generic linearization, the same
graph using `FixedJacobianFactor<2,6,3,3>`, and the existing packed-camera
graph using `FixedJacobianFactor<2,9,3>`. The generic and ternary runs have
identical nonlinear factors, values, ordering, and iteration counts.

`timeTernaryImuFactor` builds a deterministic NavState/bias chain with one
second of preintegrated stationary IMU data per interval and weak anchors every
100 intervals to keep the long Cholesky solve well-conditioned. It compares
`ImuFactor2` forced through generic linearization against automatic
`FixedJacobianFactor<9,9,9,6>` linearization. Before timing, it requires the
keys, all three whitened Jacobian blocks, RHS, and noise model of every factor
to be bitwise identical. Both executables alternate trial order, verify
concrete linear-factor types, and reject numerically different optimization
results. BAL uses fixed-iteration Levenberg-Marquardt, while the IMU chain uses
fixed-step Gauss-Newton to avoid adaptive damping retries in the timed
comparison.

From the build directory:

```bash
make -j6 timeTernarySfmBAL timeTernaryImuFactor
./timing/timeTernarySfmBAL --dataset /path/to/dubrovnik-88-64298-pre.txt \
  --warmup 1 --repeats 5 --linearize-repeats 3 --iterations 5 \
  --output ../timing/results/ternary_sfm_bal.csv
./timing/timeTernaryImuFactor --steps 1000 \
  --warmup 1 --repeats 5 --linearize-repeats 3 --iterations 1 \
  --output ../timing/results/ternary_imu_factor.csv
```

Each console summary reports median linearization and fixed-iteration solver
times.
The optional CSV files retain every measured trial for independent analysis.

## Bayes-Tree Covariance Results

The Bayes-tree covariance paper uses generated benchmark output rather than
checked-in CSV files. The files under `timing/results/` can be regenerated from
the commands below and do not need to be committed.

### Build

From the build directory:

```bash
make -j6 timeBayesTreeCovariance
make -j6 timeISAM2Covariance
make -j6 exportBayesTreeCovarianceVisuals
```

### Generate benchmark CSVs

Run from `build/`:

```bash
./timing/timeBayesTreeCovariance \
  --datasets w100.graph,w10000.graph,w20000.txt \
  --repeats 10 \
  --output-dir ../timing/results/bayes_tree_covariance
```

This writes:

- `timing/results/bayes_tree_covariance/raw.csv`
- `timing/results/bayes_tree_covariance/per_query.csv`
- `timing/results/bayes_tree_covariance/summary.csv`

The generated CSVs now include the small-query families used to benchmark the
legacy common cases:

- `single_pose` for `Q = 1`
- `pair_pose` for `Q = 2`

These are timed with the same benchmark executable and appear alongside the
larger `local_window`, `wide_separated`, `overlap_window`, and
`selected_cross` workloads.

The local query families are now sampled across the full valid trajectory range
rather than from only the earliest windows. This makes the `w10000` versus
`w20000` comparison reflect trajectory-wide local supports rather than a prefix
of the trajectory.

The fixed linearization point for these batch covariance timings is now obtained
from a sequential `ISAM2` solve rather than from a one-shot batch optimizer.
This avoids the poor large-loop initializations that can occur when the dataset
provides only odometric seed poses.

### Generate incremental `ISAM2` covariance CSV

Run from `build/`:

```bash
./timing/timeISAM2Covariance \
  --dataset w20000.txt \
  --query-repeats 5 \
  --output ../timing/results/bayes_tree_covariance/isam2_w20000.csv \
  --snapshot-dir ../timing/results/bayes_tree_covariance/isam2_support_snapshots
```

This writes:

- `timing/results/bayes_tree_covariance/isam2_w20000.csv`
- `timing/results/bayes_tree_covariance/isam2_support_snapshots/snapshots.csv`
- `timing/results/bayes_tree_covariance/isam2_support_snapshots/*.dot`

The incremental CSV contains one row per update step, recording both the
`ISAM2.update(...)` time and the repeated query time for the pairwise joint
covariance on `{x0, xt}`.
The snapshot directory stores compressed-support Graphviz views for five
representative incremental steps.

### Export `w100` visual data

Run from `build/`:

```bash
./timing/exportBayesTreeCovarianceVisuals \
  --dataset w100.graph \
  --output-dir ../timing/results/bayes_tree_covariance/visuals
```

This writes:

- the `w100` pose/query/covariance CSVs used for the geometric query figures
- `w10000_cliques.csv`
- `w20000_cliques.csv`

The latter two files store the final optimized trajectories with one clique-size value
per pose, so the report can compare the elimination geometry of the two larger datasets
on a shared color scale.

### Generate figures

Run from the repository root:

```bash
python3 timing/plot_bayes_tree_covariance.py \
  --input timing/results/bayes_tree_covariance/summary.csv \
  --per-query-input timing/results/bayes_tree_covariance/per_query.csv \
  --incremental-input timing/results/bayes_tree_covariance/isam2_w20000.csv \
  --incremental-snapshot-dir timing/results/bayes_tree_covariance/isam2_support_snapshots \
  --output-dir ../BayesTreeCovariance/figures/generated \
  --copy-csv-dir ../BayesTreeCovariance/data \
  --visual-data-dir timing/results/bayes_tree_covariance/visuals
```

This generates:

- `results-smallq.pdf`
- `results-ablation.pdf`
- `results-ordering.pdf`
- `results-structure.pdf`
- `results-local-diagnostics.pdf`
- `results-clique-sizes.pdf`
- `results-cross.pdf`
- `results-isam2-support.pdf`
- `results-isam2-w20000.pdf`
- `results-w100-queries.pdf`
- `results-w100-covariance.pdf`

## Notes

- The benchmark timings measure covariance-query work after obtaining a final
  estimate with sequential `ISAM2` and then linearizing once at that estimate.
- Each distinct query is run once as an untimed warmup and then `--repeats`
  times as measured repetitions.
- `raw.csv` stores one row per measured repetition.
- `per_query.csv` stores one row per distinct query, aggregating repeated
  timings by per-query means.
- `summary.csv` stores one row per query family bucket, aggregating the
  per-query means and structural statistics by medians across the sampled
  queries.
- The batch CSVs now also record support-width diagnostics:
  - `max_frontal_dim`
  - `max_separator_dim`
- `isam2_w20000.csv` stores one row per incremental update step for the
  sequential `ISAM2` experiment on `w20000`.
- The `results-smallq.pdf` figure summarizes the `Q = 1` and `Q = 2` query
  families; the larger performance figures focus on `Q > 2`, where Steiner
  localization changes the asymptotic behavior.
- The benchmark compares four variants:
  - `legacy_dense`
  - `steiner_dense`
  - `legacy_solve`
  - `steiner_solve`
- If the generated results become stale, it is safe to delete
  `timing/results/bayes_tree_covariance/` and regenerate it.

## File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [DummyFactor.h](DummyFactor.h) | Just to help in timing overhead. | [RegularImplicitSchurFactor.h](../gtsam/slam/RegularImplicitSchurFactor.h) | [timeSchurFactors.cpp](timeSchurFactors.cpp) |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [benchmark_range_factor_plaza2.py](benchmark_range_factor_plaza2.py) | Run the Plaza2 RangeFactor benchmark and print a PR-friendly summary. | Python standard library | [timing/README.md](README.md) |
| [cuda_sparse/](cuda_sparse/README.md) | Indexes this maintained subfolder. | None | Developers |
| [exportBayesTreeCovarianceVisuals.cpp](exportBayesTreeCovarianceVisuals.cpp) | Export representative pose-graph query and covariance visuals. | [Pose2.h](../gtsam/geometry/Pose2.h); [gtsam/inference/Ordering.h](../gtsam/inference/Ordering.h); [GaussianBayesTree.h](../gtsam/linear/GaussianBayesTree.h); [ISAM2.h](../gtsam/nonlinear/ISAM2.h); 6 other source includes; C++ standard/system library | None |
| [inspect_mosek_sdp.py](inspect_mosek_sdp.py) | Inspect MOSEK exports from the certifiable examples without re-solving. | Python standard library; `mosek`; `numpy` | None |
| [internal/](internal/README.md) | Indexes this maintained subfolder. | None | Developers |
| [plot_bayes_tree_covariance.py](plot_bayes_tree_covariance.py) | Plots Bayes-tree covariance benchmark results. | Python standard library; `matplotlib`; `numpy` | [timing/README.md](README.md) |
| [pypose_ba/](pypose_ba/README.md) | Indexes this maintained subfolder. | None | Developers |
| [sfm_ba/](sfm_ba/README.md) | Indexes this maintained subfolder. | None | Developers |
| [tests/](tests/README.md) | Indexes this maintained subfolder. | None | Developers |
| [timeActiveSetSolverComparison.cpp](timeActiveSetSolverComparison.cpp) | Compare sparse and dense active-set QP subproblem solves. | [ActiveSetSolver.h](../gtsam/constrained/ActiveSetSolver.h); [TimingUtils.h](internal/TimingUtils.h); C++ standard/system library | [QpProblemExample.ipynb](../python/gtsam/examples/constrained/QpProblemExample.ipynb) |
| [timeAdaptAutoDiff.cpp](timeAdaptAutoDiff.cpp) | time CalibratedCamera derivatives. | [Cal3Bundler.h](../gtsam/geometry/Cal3Bundler.h); [PinholeCamera.h](../gtsam/geometry/PinholeCamera.h); [Point3.h](../gtsam/geometry/Point3.h); [AdaptAutoDiff.h](../gtsam/nonlinear/AdaptAutoDiff.h); 4 other source includes | [timing/CMakeLists.txt](CMakeLists.txt) |
| [timeAugmentedLagrangianPolicies.cpp](timeAugmentedLagrangianPolicies.cpp) | Compare Aggressive and BCL augmented-Lagrangian update policies. | [AugmentedLagrangianOptimizer.h](../gtsam/constrained/AugmentedLagrangianOptimizer.h); [gtsam/inference/Symbol.h](../gtsam/inference/Symbol.h); [GaussianFactorGraph.h](../gtsam/linear/GaussianFactorGraph.h); [gtsam/nonlinear/expressions.h](../gtsam/nonlinear/expressions.h); 1 other source includes; C++ standard/system library | None |
| [timeBatch.cpp](timeBatch.cpp) | Overall timing tests for batch solving. | [timing.h](../gtsam/base/timing.h); [LevenbergMarquardtOptimizer.h](../gtsam/nonlinear/LevenbergMarquardtOptimizer.h); [Marginals.h](../gtsam/nonlinear/Marginals.h); [dataset.h](../gtsam/slam/dataset.h) | None |
| [timeBayesTreeCovariance.cpp](timeBayesTreeCovariance.cpp) | Benchmark Bayes-tree covariance recovery variants. | [gtsam/inference/Ordering.h](../gtsam/inference/Ordering.h); [GaussianBayesNet.h](../gtsam/linear/GaussianBayesNet.h); [GaussianBayesTree.h](../gtsam/linear/GaussianBayesTree.h); [GaussianFactorGraph.h](../gtsam/linear/GaussianFactorGraph.h); 6 other source includes; C++ standard/system library; `gtsam` headers | None |
| [timeBetweenFactor.cpp](timeBetweenFactor.cpp) | Benchmark Rot3 BetweenFactor error and Jacobian evaluation. | [gtsam/base/Matrix.h](../gtsam/base/Matrix.h); [Vector.h](../gtsam/base/Vector.h); [numericalDerivative.h](../gtsam/base/numericalDerivative.h); [Rot3.h](../gtsam/geometry/Rot3.h); 3 other source includes; C++ standard/system library; `gtsam` headers | None |
| [timeBetweenFactorPoseGraph.cpp](timeBetweenFactorPoseGraph.cpp) | Benchmark corrected factor Jacobians in full pose-graph optimization. | [gtsam/base/Matrix.h](../gtsam/base/Matrix.h); [Vector.h](../gtsam/base/Vector.h); [Pose2.h](../gtsam/geometry/Pose2.h); [NoiseModel.h](../gtsam/linear/NoiseModel.h); 8 other source includes; C++ standard/system library; `gtsam` headers | None |
| [timeBinaryFactorPoseGraph.cpp](timeBinaryFactorPoseGraph.cpp) | Compare fixed-size binary and generic pose-graph linearization. | [FixedJacobianFactor.h](../gtsam/linear/FixedJacobianFactor.h); [GaussianFactorGraph.h](../gtsam/linear/GaussianFactorGraph.h); [LevenbergMarquardtOptimizer.h](../gtsam/nonlinear/LevenbergMarquardtOptimizer.h); [NonlinearFactorGraph.h](../gtsam/nonlinear/NonlinearFactorGraph.h); 4 other source includes; C++ standard/system library | None |
| [timeCalibratedCamera.cpp](timeCalibratedCamera.cpp) | time CalibratedCamera derivatives. | [CalibratedCamera.h](../gtsam/geometry/CalibratedCamera.h); [Point2.h](../gtsam/geometry/Point2.h); C++ standard/system library | [stats.html](../doc/stats.html) |
| [timeCameraExpression.cpp](timeCameraExpression.cpp) | time CalibratedCamera derivatives. | [Cal3_S2.h](../gtsam/geometry/Cal3_S2.h); [Pose3.h](../gtsam/geometry/Pose3.h); [ExpressionFactor.h](../gtsam/nonlinear/ExpressionFactor.h); [GeneralSFMFactor.h](../gtsam/slam/GeneralSFMFactor.h); 3 other source includes | [timeAdaptAutoDiff.cpp](timeAdaptAutoDiff.cpp) |
| [timeCholesky.cpp](timeCholesky.cpp) | time Cholesky factorization. | [cholesky.h](../gtsam/base/cholesky.h); C++ standard/system library; `time.h` | None |
| [timeFactorOverhead.cpp](timeFactorOverhead.cpp) | Compares times of solving large single-factor graphs with their multi-factor equivalents. | [timing.h](../gtsam/base/timing.h); [GaussianBayesNet.h](../gtsam/linear/GaussianBayesNet.h); [GaussianFactorGraph.h](../gtsam/linear/GaussianFactorGraph.h); [NoiseModel.h](../gtsam/linear/NoiseModel.h); 1 other source includes; C++ standard/system library | None |
| [timeFixedJacobianFactor.cpp](timeFixedJacobianFactor.cpp) | Compare generic and fixed-size quaternary Jacobian factors. | [Testable.h](../gtsam/base/Testable.h); [FixedJacobianFactor.h](../gtsam/linear/FixedJacobianFactor.h); [NoiseModelFactorN.h](../gtsam/nonlinear/NoiseModelFactorN.h); [TimingUtils.h](internal/TimingUtils.h); C++ standard/system library | None |
| [timeFrobeniusFactor.cpp](timeFrobeniusFactor.cpp) | Time FrobeniusBetweenFactor::evaluateError with derivatives for various Lie groups. | [timing.h](../gtsam/base/timing.h); [Gal3.h](../gtsam/geometry/Gal3.h); [Pose2.h](../gtsam/geometry/Pose2.h); [Pose3.h](../gtsam/geometry/Pose3.h); 7 other source includes; C++ standard/system library | None |
| [timeGaussianFactor.cpp](timeGaussianFactor.cpp) | time JacobianFactor.eliminate. | [gtsam/base/Matrix.h](../gtsam/base/Matrix.h); [gtsam/inference/Ordering.h](../gtsam/inference/Ordering.h); [GaussianConditional.h](../gtsam/linear/GaussianConditional.h); [JacobianFactor.h](../gtsam/linear/JacobianFactor.h); 1 other source includes; C++ standard/system library; `time.h` | [stats.html](../doc/stats.html) |
| [timeGaussianFactorGraph.cpp](timeGaussianFactorGraph.cpp) | Time elimination with simple Kalman Smoothing example. | [TestHarness.h](../CppUnitLite/TestHarness.h); [smallExample.h](../tests/smallExample.h); `time.h` | None |
| [timeHybridInference.cpp](timeHybridInference.cpp) | Benchmark sequential and multifrontal hybrid inference. | [gtsam/base/Matrix.h](../gtsam/base/Matrix.h); [TableFactor.h](../gtsam/discrete/TableFactor.h); [HybridBayesNet.h](../gtsam/hybrid/HybridBayesNet.h); [HybridBayesTree.h](../gtsam/hybrid/HybridBayesTree.h); 6 other source includes; C++ standard/system library; `Eigen` headers | None |
| [timeISAM2Covariance.cpp](timeISAM2Covariance.cpp) | Incremental timing study for ISAM2 joint covariance queries. | [Pose2.h](../gtsam/geometry/Pose2.h); [ISAM2.h](../gtsam/nonlinear/ISAM2.h); [NonlinearFactorGraph.h](../gtsam/nonlinear/NonlinearFactorGraph.h); [Values.h](../gtsam/nonlinear/Values.h); 3 other source includes; C++ standard/system library | None |
| [timeImuIntegration.cpp](timeImuIntegration.cpp) | Benchmark one-sample IMU preintegration for every PIM backend. | [CombinedImuFactor.h](../gtsam/navigation/CombinedImuFactor.h); [GalileanImuFactor.h](../gtsam/navigation/GalileanImuFactor.h); [ImuFactor.h](../gtsam/navigation/ImuFactor.h); [LieGroupPreintegration.h](../gtsam/navigation/LieGroupPreintegration.h); 3 other source includes; C++ standard/system library | None |
| [timeIncremental.cpp](timeIncremental.cpp) | Overall timing tests for incremental solving. | [timing.h](../gtsam/base/timing.h); [Pose2.h](../gtsam/geometry/Pose2.h); [gtsam/inference/Symbol.h](../gtsam/inference/Symbol.h); [ISAM2.h](../gtsam/nonlinear/ISAM2.h); 4 other source includes; C++ standard/system library; `boost` headers | [timing/CMakeLists.txt](CMakeLists.txt) |
| [timeLago.cpp](timeLago.cpp) | Time the LAGO initialization method. | [timing.h](../gtsam/base/timing.h); [Pose2.h](../gtsam/geometry/Pose2.h); [Sampler.h](../gtsam/linear/Sampler.h); [GaussNewtonOptimizer.h](../gtsam/nonlinear/GaussNewtonOptimizer.h); 2 other source includes; C++ standard/system library | None |
| [timeLinearize.h](timeLinearize.h) | time linearize. | [GaussianFactorGraph.h](../gtsam/linear/GaussianFactorGraph.h); [NonlinearFactorGraph.h](../gtsam/nonlinear/NonlinearFactorGraph.h); C++ standard/system library; `time.h` | [timeAdaptAutoDiff.cpp](timeAdaptAutoDiff.cpp); [timeCameraExpression.cpp](timeCameraExpression.cpp); [timeOneCameraExpression.cpp](timeOneCameraExpression.cpp) |
| [timeMatrix.cpp](timeMatrix.cpp) | Performs timing and profiling for Matrix operations. | [gtsam/base/Matrix.h](../gtsam/base/Matrix.h); [timing.h](../gtsam/base/timing.h); C++ standard/system library | None |
| [timeMatrixOps.cpp](timeMatrixOps.cpp) | Tests to help determine which way of accomplishing something with Eigen is faster. | [gtsam/base/Matrix.h](../gtsam/base/Matrix.h); [timing.h](../gtsam/base/timing.h); C++ standard/system library | None |
| [timeMultifrontalSolver.cpp](timeMultifrontalSolver.cpp) | Compare MultifrontalSolver against standard elimination. | [GaussianBayesTree.h](../gtsam/linear/GaussianBayesTree.h); [GaussianFactorGraph.h](../gtsam/linear/GaussianFactorGraph.h); [MultifrontalSolver.h](../gtsam/linear/MultifrontalSolver.h); [smallExample.h](../tests/smallExample.h); 2 other source includes; C++ standard/system library | None |
| [timeNonlinearMultifrontalSolver.cpp](timeNonlinearMultifrontalSolver.cpp) | Time NonlinearMultifrontalSolver on BAL 88-camera dataset. | [gtsam/constrained/NonlinearEquality.h](../gtsam/constrained/NonlinearEquality.h); [NonlinearMultifrontalSolver.h](../gtsam/nonlinear/NonlinearMultifrontalSolver.h); [TimingUtils.h](internal/TimingUtils.h); [timeSFMBAL.h](timeSFMBAL.h); C++ standard/system library | None |
| [timeNonlinearOptimizerCache.cpp](timeNonlinearOptimizerCache.cpp) | Compare validated cache reuse, unchecked reuse, and fresh elimination. | [GaussianBayesTree.h](../gtsam/linear/GaussianBayesTree.h); [GaussianFactorGraph.h](../gtsam/linear/GaussianFactorGraph.h); [GaussNewtonOptimizer.h](../gtsam/nonlinear/GaussNewtonOptimizer.h); [BetweenFactor.h](../gtsam/slam/BetweenFactor.h); 1 other source includes; C++ standard/system library | None |
| [timeOneCameraExpression.cpp](timeOneCameraExpression.cpp) | time CalibratedCamera derivatives. | [ExpressionFactor.h](../gtsam/nonlinear/ExpressionFactor.h); [gtsam/slam/expressions.h](../gtsam/slam/expressions.h); [timeLinearize.h](timeLinearize.h) | None |
| [timePCGSolver.cpp](timePCGSolver.cpp) | Compare legacy, contiguous, and Eigen PCG performance. | [BatchJacobianFactor.h](../gtsam/linear/BatchJacobianFactor.h); [PCGSolver.h](../gtsam/linear/PCGSolver.h); [Preconditioner.h](../gtsam/linear/Preconditioner.h); [SparseEigen.h](../gtsam/linear/SparseEigen.h); 2 other source includes; C++ standard/system library; `Eigen` headers | None |
| [timePinholeCamera.cpp](timePinholeCamera.cpp) | time PinholeCamera derivatives. | [Cal3Bundler.h](../gtsam/geometry/Cal3Bundler.h); [PinholeCamera.h](../gtsam/geometry/PinholeCamera.h); C++ standard/system library; `time.h` | [stats.html](../doc/stats.html) |
| [timePose2.cpp](timePose2.cpp) | Time Pose2 geometry. | [MatrixConstants.h](../gtsam/base/MatrixConstants.h); [timing.h](../gtsam/base/timing.h); [Pose2.h](../gtsam/geometry/Pose2.h); C++ standard/system library | [stats.html](../doc/stats.html) |
| [timePose3.cpp](timePose3.cpp) | time Pose3 functions. | [timing.h](../gtsam/base/timing.h); [Pose3.h](../gtsam/geometry/Pose3.h); C++ standard/system library | [stats.html](../doc/stats.html) |
| [timeRangeFactorPlaza2.cpp](timeRangeFactorPlaza2.cpp) | Benchmark the range-only Plaza2 incremental SLAM workload. | [Vector.h](../gtsam/base/Vector.h); [Point2.h](../gtsam/geometry/Point2.h); [Pose2.h](../gtsam/geometry/Pose2.h); [gtsam/inference/Symbol.h](../gtsam/inference/Symbol.h); 9 other source includes; C++ standard/system library | None |
| [timeRot2.cpp](timeRot2.cpp) | Time Rot2 geometry. | [MatrixConstants.h](../gtsam/base/MatrixConstants.h); [OptionalJacobian.h](../gtsam/base/OptionalJacobian.h); [timing.h](../gtsam/base/timing.h); [Pose2.h](../gtsam/geometry/Pose2.h); C++ standard/system library | None |
| [timeRot3.cpp](timeRot3.cpp) | time Rot3 functions. | [Rot3.h](../gtsam/geometry/Rot3.h); C++ standard/system library; `time.h` | None |
| [timeSFMBAL.cpp](timeSFMBAL.cpp) | time SFM with BAL file, conventional GeneralSFMFactor. | [gtsam/inference/Symbol.h](../gtsam/inference/Symbol.h); [BatchJacobianFactor.h](../gtsam/linear/BatchJacobianFactor.h); [GaussianBayesTree.h](../gtsam/linear/GaussianBayesTree.h); [JacobianFactor.h](../gtsam/linear/JacobianFactor.h); 8 other source includes; C++ standard/system library | [timing/README.md](README.md); [timing/pypose_ba/README.md](pypose_ba/README.md) |
| [timeSFMBAL.h](timeSFMBAL.h) | Compatibility include for private BAL timing infrastructure. | [SfmBalBenchmark.h](internal/SfmBalBenchmark.h) | [timeCudaSparseLM.cpp](cuda_sparse/timeCudaSparseLM.cpp); [timeCudaSFMBAL.cpp](sfm_ba/timeCudaSFMBAL.cpp); [timeMultifrontalSolver.cpp](timeMultifrontalSolver.cpp); 5 other source references |
| [timeSFMBALautodiff.cpp](timeSFMBALautodiff.cpp) | time SFM with BAL file, Ceres autodiff version. | [Point3.h](../gtsam/geometry/Point3.h); [AdaptAutoDiff.h](../gtsam/nonlinear/AdaptAutoDiff.h); [ExpressionFactor.h](../gtsam/nonlinear/ExpressionFactor.h); [SnavelyProjection.h](../tests/SnavelyProjection.h); 1 other source includes; C++ standard/system library; `stddef.h` | [timing/CMakeLists.txt](CMakeLists.txt) |
| [timeSFMBALcamTnav.cpp](timeSFMBALcamTnav.cpp) | time SFM with BAL file, expressions with camTnav pose. | [Cal3Bundler.h](../gtsam/geometry/Cal3Bundler.h); [Point3.h](../gtsam/geometry/Point3.h); [ExpressionFactor.h](../gtsam/nonlinear/ExpressionFactor.h); [gtsam/slam/expressions.h](../gtsam/slam/expressions.h); 1 other source includes | None |
| [timeSFMBALnavTcam.cpp](timeSFMBALnavTcam.cpp) | time SFM with BAL file, expressions with navTcam pose. | [Cal3Bundler.h](../gtsam/geometry/Cal3Bundler.h); [Point3.h](../gtsam/geometry/Point3.h); [ExpressionFactor.h](../gtsam/nonlinear/ExpressionFactor.h); [gtsam/slam/expressions.h](../gtsam/slam/expressions.h); 1 other source includes | None |
| [timeSFMBALsmart.cpp](timeSFMBALsmart.cpp) | Compare direct and PCG solvers for structureless BAL smart factors. | [LevenbergMarquardtOptimizer.h](../gtsam/nonlinear/LevenbergMarquardtOptimizer.h); [SmartFactorParams.h](../gtsam/slam/SmartFactorParams.h); [SfmBalBenchmark.h](internal/SfmBalBenchmark.h); [SfmPcgBenchmark.h](internal/SfmPcgBenchmark.h); 1 other source includes; C++ standard/system library | None |
| [timeSFMExpressions.cpp](timeSFMExpressions.cpp) | time CalibratedCamera derivatives, realistic scenario. | [GaussianFactorGraph.h](../gtsam/linear/GaussianFactorGraph.h); [ExpressionFactor.h](../gtsam/nonlinear/ExpressionFactor.h); [NonlinearFactorGraph.h](../gtsam/nonlinear/NonlinearFactorGraph.h); [gtsam/slam/expressions.h](../gtsam/slam/expressions.h); C++ standard/system library; `time.h` | None |
| [timeSchurFactors.cpp](timeSchurFactors.cpp) | Time various Schur-complement Jacobian factors. | [timing.h](../gtsam/base/timing.h); [Cal3Bundler.h](../gtsam/geometry/Cal3Bundler.h); [PinholePose.h](../gtsam/geometry/PinholePose.h); [JacobianFactorQ.h](../gtsam/slam/JacobianFactorQ.h); 3 other source includes; C++ standard/system library | [RegularImplicitSchurFactor.h](../gtsam/slam/RegularImplicitSchurFactor.h) |
| [timeSfmPartialElimination.cpp](timeSfmPartialElimination.cpp) | Compare the public CPU SFM elimination-mode and solver matrix. | [PCGSolver.h](../gtsam/linear/PCGSolver.h); [Preconditioner.h](../gtsam/linear/Preconditioner.h); [SubgraphSolver.h](../gtsam/linear/SubgraphSolver.h); [gtsam/sfm/SfmLevenbergMarquardt.h](../gtsam/sfm/SfmLevenbergMarquardt.h); 2 other source includes; C++ standard/system library | [timing/README.md](README.md) |
| [timeShonanFactor.cpp](timeShonanFactor.cpp) | time ShonanFactor with BAL file. | [timing.h](../gtsam/base/timing.h); [gtsam/constrained/NonlinearEquality.h](../gtsam/constrained/NonlinearEquality.h); [Pose3.h](../gtsam/geometry/Pose3.h); [NoiseModel.h](../gtsam/linear/NoiseModel.h); 8 other source includes; C++ standard/system library | None |
| [timeShonanInitialization.cpp](timeShonanInitialization.cpp) | Compare Shonan with the general QCQP/BM staircase. | [DSFMap.h](../gtsam/base/DSFMap.h); [RiemannianStaircaseOptimizer.h](../gtsam/certifiable/RiemannianStaircaseOptimizer.h); [QcqpProblem.h](../gtsam/constrained/QcqpProblem.h); [Pose3.h](../gtsam/geometry/Pose3.h); 12 other source includes; C++ standard/system library | None |
| [timeStereoCamera.cpp](timeStereoCamera.cpp) | time StereoCamera derivatives. | [StereoCamera.h](../gtsam/geometry/StereoCamera.h); C++ standard/system library; `time.h` | [stats.html](../doc/stats.html) |
| [timeTernaryImuFactor.cpp](timeTernaryImuFactor.cpp) | Compare generic and fixed-size ternary ImuFactor2 linearization. | [gtsam/inference/Symbol.h](../gtsam/inference/Symbol.h); [FixedJacobianFactor.h](../gtsam/linear/FixedJacobianFactor.h); [ImuFactor.h](../gtsam/navigation/ImuFactor.h); [GaussNewtonOptimizer.h](../gtsam/nonlinear/GaussNewtonOptimizer.h); 3 other source includes; C++ standard/system library | None |
| [timeTernarySfmBAL.cpp](timeTernarySfmBAL.cpp) | Compare generic and fixed-size ternary BAL linearization. | [gtsam/inference/Symbol.h](../gtsam/inference/Symbol.h); [FixedJacobianFactor.h](../gtsam/linear/FixedJacobianFactor.h); [LevenbergMarquardtOptimizer.h](../gtsam/nonlinear/LevenbergMarquardtOptimizer.h); [gtsam/nonlinear/PriorFactor.h](../gtsam/nonlinear/PriorFactor.h); 2 other source includes; C++ standard/system library | None |
| [timeTest.cpp](timeTest.cpp) | Measures Test benchmark behavior. | [timing.h](../gtsam/base/timing.h) | None |
| [timeVirtual.cpp](timeVirtual.cpp) | Measures Virtual benchmark behavior. | [timing.h](../gtsam/base/timing.h); C++ standard/system library | [timeVirtual2.cpp](timeVirtual2.cpp) |
| [timeVirtual2.cpp](timeVirtual2.cpp) | Measures Virtual2 benchmark behavior. | [timing.h](../gtsam/base/timing.h); C++ standard/system library | None |
| [timeiSAM2Chain.cpp](timeiSAM2Chain.cpp) | Times each iteration of a long chain in iSAM2, to measure asymptotic performance. | [timing.h](../gtsam/base/timing.h); [Pose2.h](../gtsam/geometry/Pose2.h); [gtsam/inference/Symbol.h](../gtsam/inference/Symbol.h); [ISAM2.h](../gtsam/nonlinear/ISAM2.h); 3 other source includes; C++ standard/system library; `boost` headers | None |

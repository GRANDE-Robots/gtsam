# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [testSfmBalBenchmark.cpp](testSfmBalBenchmark.cpp) | Tests for shared BAL smart-factor and PCG timing support. | [TestHarness.h](../../CppUnitLite/TestHarness.h); [gtsam/inference/Symbol.h](../../gtsam/inference/Symbol.h); [LevenbergMarquardtParams.h](../../gtsam/nonlinear/LevenbergMarquardtParams.h); [gtsam/sam/RangeFactor.h](../../gtsam/sam/RangeFactor.h); 1 other source includes; C++ standard/system library; `internal` headers | None |
| [testTimingUtils.cpp](testTimingUtils.cpp) | Tests for the private timing support library. | [TestHarness.h](../../CppUnitLite/TestHarness.h); C++ standard/system library; `internal` headers | None |

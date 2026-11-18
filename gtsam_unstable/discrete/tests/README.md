# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [testCSP.cpp](testCSP.cpp) | develop code for CSP solver. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [gtsam/discrete/Domain.h](../../../gtsam/discrete/Domain.h); [CSP.h](../CSP.h); C++ standard/system library | None |
| [testDiscreteConstraintCompatibility.cpp](testDiscreteConstraintCompatibility.cpp) | Test the deprecated GTSAM 4.3 discrete constraint include paths. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [gtsam_unstable/discrete/AllDiff.h](../AllDiff.h); [gtsam_unstable/discrete/BinaryAllDiff.h](../BinaryAllDiff.h); [gtsam_unstable/discrete/Constraint.h](../Constraint.h); 2 other source includes | [gtsam_unstable/discrete/tests/CMakeLists.txt](CMakeLists.txt) |
| [testLoopyBelief.cpp](testLoopyBelief.cpp) | Checks Loopy Belief behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [DecisionTreeFactor.h](../../../gtsam/discrete/DecisionTreeFactor.h); [DiscreteConditional.h](../../../gtsam/discrete/DiscreteConditional.h); [DiscreteFactorGraph.h](../../../gtsam/discrete/DiscreteFactorGraph.h); 1 other source includes; C++ standard/system library | [stats.html](../../../doc/stats.html) |
| [testScheduler.cpp](testScheduler.cpp) | Checks Scheduler behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [Testable.h](../../../gtsam/base/Testable.h); [timing.h](../../../gtsam/base/timing.h); [gtsam_unstable/discrete/Scheduler.h](../Scheduler.h) | [gtsam_unstable/discrete/tests/CMakeLists.txt](CMakeLists.txt) |
| [testSudoku.cpp](testSudoku.cpp) | develop code for Sudoku CSP solver. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [gtsam/inference/Symbol.h](../../../gtsam/inference/Symbol.h); [CSP.h](../CSP.h); C++ standard/system library; `stdarg.h` | None |

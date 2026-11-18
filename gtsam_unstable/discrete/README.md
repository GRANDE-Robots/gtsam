# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [AllDiff.h](AllDiff.h) | Declares All Diff types or operations. | [gtsam/discrete/AllDiff.h](../../gtsam/discrete/AllDiff.h); `gtsam` headers | [testDiscreteConstraintCompatibility.cpp](tests/testDiscreteConstraintCompatibility.cpp) |
| [BinaryAllDiff.h](BinaryAllDiff.h) | Declares Binary All Diff types or operations. | [gtsam/discrete/BinaryAllDiff.h](../../gtsam/discrete/BinaryAllDiff.h); `gtsam` headers | [testDiscreteConstraintCompatibility.cpp](tests/testDiscreteConstraintCompatibility.cpp) |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [CSP.cpp](CSP.cpp) | Constraint Satisfaction Problem class. | [Testable.h](../../gtsam/base/Testable.h); [DiscreteBayesNet.h](../../gtsam/discrete/DiscreteBayesNet.h); [gtsam/discrete/Domain.h](../../gtsam/discrete/Domain.h); [CSP.h](CSP.h) | None |
| [CSP.h](CSP.h) | Constraint Satisfaction Problem class. | [gtsam/discrete/AllDiff.h](../../gtsam/discrete/AllDiff.h); [DiscreteFactorGraph.h](../../gtsam/discrete/DiscreteFactorGraph.h); [gtsam/discrete/SingleValue.h](../../gtsam/discrete/SingleValue.h); `gtsam_unstable` headers | [CSP.cpp](CSP.cpp); [gtsam_unstable/discrete/Scheduler.h](Scheduler.h); [testCSP.cpp](tests/testCSP.cpp); 1 other source references |
| [Constraint.h](Constraint.h) | Declares Constraint types or operations. | [gtsam/discrete/Constraint.h](../../gtsam/discrete/Constraint.h); `gtsam` headers | [testDiscreteConstraintCompatibility.cpp](tests/testDiscreteConstraintCompatibility.cpp) |
| [Domain.h](Domain.h) | Declares Domain types or operations. | [gtsam/discrete/Domain.h](../../gtsam/discrete/Domain.h); `gtsam` headers | [testDiscreteConstraintCompatibility.cpp](tests/testDiscreteConstraintCompatibility.cpp) |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [Scheduler.cpp](Scheduler.cpp) | an example how inference can be used for scheduling qualifiers. | [debug.h](../../gtsam/base/debug.h); [timing.h](../../gtsam/base/timing.h); [DiscreteFactorGraph.h](../../gtsam/discrete/DiscreteFactorGraph.h); [gtsam_unstable/discrete/Scheduler.h](Scheduler.h); C++ standard/system library; `boost` headers | [gtsam_unstable/CMakeLists.txt](../CMakeLists.txt) |
| [Scheduler.h](Scheduler.h) | an example how inference can be used for scheduling qualifiers. | [DiscreteBayesNet.h](../../gtsam/discrete/DiscreteBayesNet.h); [CSP.h](CSP.h) | [Scheduler.cpp](Scheduler.cpp); [schedulingExample.cpp](examples/schedulingExample.cpp); [schedulingQuals12.cpp](examples/schedulingQuals12.cpp); 2 other source references |
| [SingleValue.h](SingleValue.h) | Declares Single Value types or operations. | [gtsam/discrete/SingleValue.h](../../gtsam/discrete/SingleValue.h); `gtsam` headers | [testDiscreteConstraintCompatibility.cpp](tests/testDiscreteConstraintCompatibility.cpp) |
| [examples/](examples/README.md) | Indexes this maintained subfolder. | None | Developers |
| [tests/](tests/README.md) | Indexes this maintained subfolder. | None | Developers |

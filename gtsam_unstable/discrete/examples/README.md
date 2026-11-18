# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [Doodle.csv](Doodle.csv) | Retains the Doodle example or reference data. | None | [schedulingExample.cpp](schedulingExample.cpp) |
| [Doodle.xls](Doodle.xls) | Retains the Doodle example or reference data. | None | None |
| [Doodle2012.csv](Doodle2012.csv) | Retains the Doodle2012 example or reference data. | None | [schedulingQuals12.cpp](schedulingQuals12.cpp) |
| [Doodle2012.xls](Doodle2012.xls) | Retains the Doodle2012 example or reference data. | None | None |
| [Doodle2013.csv](Doodle2013.csv) | Retains the Doodle2013 example or reference data. | None | [schedulingQuals13.cpp](schedulingQuals13.cpp) |
| [Doodle2013.xls](Doodle2013.xls) | Retains the Doodle2013 example or reference data. | None | None |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [intrusive.xlsx](intrusive.xlsx) | Retains the intrusive example or reference data. | None | None |
| [schedulingExample.cpp](schedulingExample.cpp) | hard scheduling example. | [debug.h](../../../gtsam/base/debug.h); [timing.h](../../../gtsam/base/timing.h); [gtsam_unstable/discrete/Scheduler.h](../Scheduler.h); C++ standard/system library | [gtsam_unstable/discrete/examples/CMakeLists.txt](CMakeLists.txt); [schedulingQuals12.cpp](schedulingQuals12.cpp); [schedulingQuals13.cpp](schedulingQuals13.cpp) |
| [schedulingQuals12.cpp](schedulingQuals12.cpp) | hard scheduling example. | [debug.h](../../../gtsam/base/debug.h); [timing.h](../../../gtsam/base/timing.h); [gtsam_unstable/discrete/Scheduler.h](../Scheduler.h); C++ standard/system library | [gtsam_unstable/discrete/examples/CMakeLists.txt](CMakeLists.txt) |
| [schedulingQuals13.cpp](schedulingQuals13.cpp) | hard scheduling example. | [debug.h](../../../gtsam/base/debug.h); [timing.h](../../../gtsam/base/timing.h); [gtsam_unstable/discrete/Scheduler.h](../Scheduler.h); C++ standard/system library | [stats.html](../../../doc/stats.html); [gtsam_unstable/discrete/examples/CMakeLists.txt](CMakeLists.txt) |
| [small.csv](small.csv) | Retains the small example or reference data. | None | [testScheduler.cpp](../tests/testScheduler.cpp) |

# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [ValuesCrossLibrary.cpp](ValuesCrossLibrary.cpp) | Implements Values Cross Library operations. | [GenericValue.h](../../gtsam/base/GenericValue.h); [ValuesCrossLibrary.h](ValuesCrossLibrary.h); C++ standard/system library | [tests/CMakeLists.txt](../CMakeLists.txt) |
| [ValuesCrossLibrary.h](ValuesCrossLibrary.h) | Declares Values Cross Library types or operations. | [Manifold.h](../../gtsam/base/Manifold.h); [Value.h](../../gtsam/base/Value.h); C++ standard/system library | [ValuesCrossLibrary.cpp](ValuesCrossLibrary.cpp); [testValuesCrossLibrary.cpp](testValuesCrossLibrary.cpp) |
| [testValuesCrossLibrary.cpp](testValuesCrossLibrary.cpp) | Checks Values Cross Library behavior. | [TestHarness.h](../../CppUnitLite/TestHarness.h); [Values.h](../../gtsam/nonlinear/Values.h); [ValuesCrossLibrary.h](ValuesCrossLibrary.h); C++ standard/system library | [tests/CMakeLists.txt](../CMakeLists.txt) |

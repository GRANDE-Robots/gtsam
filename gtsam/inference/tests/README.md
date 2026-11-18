# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [testEdgeKey.cpp](testEdgeKey.cpp) | Checks Edge Key behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [EdgeKey.h](../EdgeKey.h); C++ standard/system library | None |
| [testKey.cpp](testKey.cpp) | Checks Key behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [Testable.h](../../base/Testable.h); [TestableAssertions.h](../../base/TestableAssertions.h); [Key.h](../Key.h); 1 other source includes; C++ standard/system library | None |
| [testKruskal.cpp](testKruskal.cpp) | Unit tests for Kruskal's minimum spanning tree algorithm. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [MatrixConstants.h](../../base/MatrixConstants.h); [TestableAssertions.h](../../base/TestableAssertions.h); [Rot3.h](../../geometry/Rot3.h); 5 other source includes; C++ standard/system library | None |
| [testLabeledSymbol.cpp](testLabeledSymbol.cpp) | Checks Labeled Symbol behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [Testable.h](../../base/Testable.h); [TestableAssertions.h](../../base/TestableAssertions.h); [LabeledSymbol.h](../LabeledSymbol.h) | None |
| [testOrdering.cpp](testOrdering.cpp) | Checks Ordering behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [TestableAssertions.h](../../base/TestableAssertions.h); [MetisIndex.h](../MetisIndex.h); [gtsam/inference/Ordering.h](../Ordering.h); 2 other source includes | None |
| [testSymbol.cpp](testSymbol.cpp) | Checks Symbol behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [gtsam/inference/Symbol.h](../Symbol.h); C++ standard/system library | None |
| [testVariableSlots.cpp](testVariableSlots.cpp) | Checks Variable Slots behavior. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [TestableAssertions.h](../../base/TestableAssertions.h); [VariableSlots.h](../VariableSlots.h); [SymbolicFactorGraph.h](../../symbolic/SymbolicFactorGraph.h) | None |

# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [parallelTraversalTasks.h](parallelTraversalTasks.h) | Declares parallel Traversal Tasks types or operations. | [global_includes.h](../../global_includes.h); C++ standard/system library; `tbb` headers | [treeTraversal-inst.h](../treeTraversal-inst.h) |
| [statistics.h](statistics.h) | Tools for gathering statistics about a forest to aid tuning parallel traversal. | [FastMap.h](../FastMap.h); [global_includes.h](../../global_includes.h); C++ standard/system library | [treeTraversal-inst.h](../treeTraversal-inst.h) |

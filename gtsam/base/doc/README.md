# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [Group.md](Group.md) | Documents Guide to Creating a `Group`. | None | [GTSAM-Concepts.md](../../../doc/GTSAM-Concepts.md); [base.md](../base.md); [VectorSpace.md](VectorSpace.md) |
| [LieGroup.md](LieGroup.md) | Documents Creating a `LieGroup`. | [Lie.h](../Lie.h); [TestableAssertions.h](../TestableAssertions.h); `gtsam` headers | [GTSAM-Concepts.md](../../../doc/GTSAM-Concepts.md); [base.md](../base.md); [MatrixLieGroup.md](MatrixLieGroup.md); 1 other source references |
| [Manifold.md](Manifold.md) | Documents Creating a `Manifold` Class. | [Manifold.h](../Manifold.h); [TestableAssertions.h](../TestableAssertions.h); `gtsam` headers | [GTSAM-Concepts.md](../../../doc/GTSAM-Concepts.md); [base.md](../base.md); [LieGroup.md](LieGroup.md); 1 other source references |
| [MatrixLieGroup.md](MatrixLieGroup.md) | Documents Creating a `MatrixLieGroup`. | [MatrixLieGroup.h](../MatrixLieGroup.h); [TestableAssertions.h](../TestableAssertions.h); `gtsam` headers | [GTSAM-Concepts.md](../../../doc/GTSAM-Concepts.md); [base.md](../base.md) |
| [ProductLieGroup.md](ProductLieGroup.md) | Documents `ProductLieGroup`: Direct Products. | [ProductLieGroup.h](../ProductLieGroup.h) | [base.md](../base.md); [AsVectorSpace.ipynb](../../geometry/doc/AsVectorSpace.ipynb) |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [SemidirectLieGroup.md](SemidirectLieGroup.md) | Documents `SemidirectLieGroup`: Action-Coupled Products. | [SemidirectLieGroup.h](../SemidirectLieGroup.h) | [base.md](../base.md); [ProductLieGroup.md](ProductLieGroup.md); [TangentLieGroup.md](TangentLieGroup.md) |
| [TangentLieGroup.md](TangentLieGroup.md) | Documents `TangentLieGroup`: A Lie Group Acting on Its Algebra. | [TangentLieGroup.h](../TangentLieGroup.h) | [base.md](../base.md); [ProductLieGroup.md](ProductLieGroup.md); [SemidirectLieGroup.md](SemidirectLieGroup.md) |
| [VectorSpace.md](VectorSpace.md) | Documents Creating a `VectorSpace`. | None | [GTSAM-Concepts.md](../../../doc/GTSAM-Concepts.md); [base.md](../base.md) |

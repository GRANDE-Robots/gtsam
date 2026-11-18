# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [testBasisFactors.cpp](testBasisFactors.cpp) | unit tests for factors in BasisFactors.h. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [Testable.h](../../base/Testable.h); [TestableAssertions.h](../../base/TestableAssertions.h); [Vector.h](../../base/Vector.h); 8 other source includes | None |
| [testChebyshev.cpp](testChebyshev.cpp) | Unit tests for Chebyshev Basis Decompositions. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [Testable.h](../../base/Testable.h); [numericalDerivative.h](../../base/numericalDerivative.h); [Chebyshev.h](../Chebyshev.h); 4 other source includes | None |
| [testChebyshev2.cpp](testChebyshev2.cpp) | Unit tests for Chebyshev Basis Decompositions via pseudo-spectral. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [Testable.h](../../base/Testable.h); [numericalDerivative.h](../../base/numericalDerivative.h); [Chebyshev2.h](../Chebyshev2.h); 4 other source includes; C++ standard/system library | None |
| [testCumulativeSplineTrajectory.cpp](testCumulativeSplineTrajectory.cpp) | Unit tests for continuous cardinal spline trajectories. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [Testable.h](../../base/Testable.h); [CardinalSplineBasis.h](../CardinalSplineBasis.h); [CumulativeSplineTrajectory.h](../CumulativeSplineTrajectory.h); 4 other source includes | None |
| [testFourier.cpp](testFourier.cpp) | Unit tests for Fourier Basis Decompositions with Expressions. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [Testable.h](../../base/Testable.h); [numericalDerivative.h](../../base/numericalDerivative.h); [FitBasis.h](../FitBasis.h); 2 other source includes | None |
| [testIrwinHall.cpp](testIrwinHall.cpp) | Validate Irwin-Hall PDF coefficients and continuity. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [IrwinHall.h](../IrwinHall.h); C++ standard/system library | None |
| [testIrwinHallCDF.cpp](testIrwinHallCDF.cpp) | Validate Irwin-Hall CDF coefficients and continuity. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [IrwinHall.h](../IrwinHall.h); C++ standard/system library | None |
| [testPiecewisePolynomial.cpp](testPiecewisePolynomial.cpp) | Validate analytic Jacobians of piecewise polynomial kernels. | [TestHarness.h](../../../CppUnitLite/TestHarness.h); [IrwinHall.h](../IrwinHall.h); C++ standard/system library | None |

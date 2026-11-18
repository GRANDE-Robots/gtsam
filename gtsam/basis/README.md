# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [Basis.cpp](Basis.cpp) | Compute an interpolating basis. | [Basis.h](Basis.h) | None |
| [Basis.h](Basis.h) | Compute an interpolating basis. | [gtsam/base/Matrix.h](../base/Matrix.h); [OptionalJacobian.h](../base/OptionalJacobian.h); C++ standard/system library | [Basis.cpp](Basis.cpp); [BasisFactors.h](BasisFactors.h); [CardinalSplineBasis.h](CardinalSplineBasis.h); 7 other source references |
| [BasisFactors.h](BasisFactors.h) | Factor definitions for various Basis functors. | [Basis.h](Basis.h); [FunctorizedFactor.h](../nonlinear/FunctorizedFactor.h) | [CardinalSplineBasis.h](CardinalSplineBasis.h); [FitBasis.h](FitBasis.h); [basis.i](basis.i); 8 other source references |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [CardinalSplineBasis.h](CardinalSplineBasis.h) | Cubic cardinal splines integrated with the GTSAM Basis framework. | [Basis.h](Basis.h); [IrwinHall.h](IrwinHall.h); C++ standard/system library | [basis.i](basis.i); [CardinalSplineBasis.ipynb](doc/CardinalSplineBasis.ipynb); [testCumulativeSplineTrajectory.cpp](tests/testCumulativeSplineTrajectory.cpp); 1 other source references |
| [Chebyshev.cpp](Chebyshev.cpp) | Chebyshev basis decompositions. | [Chebyshev.h](Chebyshev.h) | None |
| [Chebyshev.h](Chebyshev.h) | Chebyshev basis decompositions. | [Manifold.h](../base/Manifold.h); [Basis.h](Basis.h) | [Chebyshev.cpp](Chebyshev.cpp); [Chebyshev2.h](Chebyshev2.h); [basis.i](basis.i); 3 other source references |
| [Chebyshev2.cpp](Chebyshev2.cpp) | Chebyshev parameterizations on Chebyshev points of second kind. | [Chebyshev2.h](Chebyshev2.h); C++ standard/system library; `Eigen` headers | None |
| [Chebyshev2.h](Chebyshev2.h) | Pseudo-spectral parameterization for Chebyshev polynomials of the. | [Manifold.h](../base/Manifold.h); [Basis.h](Basis.h) | [Chebyshev2.cpp](Chebyshev2.cpp); [basis.i](basis.i); [Chebyshev2.ipynb](doc/Chebyshev2.ipynb); 2 other source references |
| [CumulativeSplineTrajectory.h](CumulativeSplineTrajectory.h) | Expression-based cumulative splines on Lie groups. | [IrwinHall.h](IrwinHall.h); [KernelBase.h](KernelBase.h); [Values.h](../nonlinear/Values.h); [gtsam/slam/expressions.h](../slam/expressions.h); C++ standard/system library | [ClockRecoveryContinuousTrajectory.cpp](../../examples/ClockRecoveryContinuousTrajectory.cpp); [basis.i](basis.i); [CumulativeSplineTrajectory.ipynb](doc/CumulativeSplineTrajectory.ipynb); 2 other source references |
| [FitBasis.h](FitBasis.h) | Fit a Basis using least-squares. | [Basis.h](Basis.h); [BasisFactors.h](BasisFactors.h); [GaussianFactorGraph.h](../linear/GaussianFactorGraph.h); [NoiseModel.h](../linear/NoiseModel.h); 2 other source includes | [basis.i](basis.i); [FitBasis.ipynb](doc/FitBasis.ipynb); [testChebyshev.cpp](tests/testChebyshev.cpp); 2 other source references |
| [Fourier.h](Fourier.h) | Fourier decomposition, see e.g. | [Basis.h](Basis.h) | [basis.i](basis.i); [FourierBasis.ipynb](doc/FourierBasis.ipynb); [testFourier.cpp](tests/testFourier.cpp) |
| [IrwinHall.cpp](IrwinHall.cpp) | Irwin-Hall probability density kernels. | [IrwinHall.h](IrwinHall.h) | None |
| [IrwinHall.h](IrwinHall.h) | Piecewise polynomial Irwin-Hall PDF and CDF kernels. | [PiecewisePolynomial.h](PiecewisePolynomial.h); `gtsam` headers | [ClockRecoveryContinuousTrajectory.cpp](../../examples/ClockRecoveryContinuousTrajectory.cpp); [CardinalSplineBasis.h](CardinalSplineBasis.h); [CumulativeSplineTrajectory.h](CumulativeSplineTrajectory.h); 9 other source references |
| [IrwinHallCDF.cpp](IrwinHallCDF.cpp) | Irwin-Hall cumulative distribution kernels. | [IrwinHall.h](IrwinHall.h) | None |
| [KernelBase.h](KernelBase.h) | Continuous kernels for convolution-based trajectory models. | [OptionalJacobian.h](../base/OptionalJacobian.h); C++ standard/system library | [CumulativeSplineTrajectory.h](CumulativeSplineTrajectory.h); [PiecewisePolynomial.h](PiecewisePolynomial.h); [basis.md](basis.md); 1 other source references |
| [PiecewisePolynomial.h](PiecewisePolynomial.h) | Fixed-order piecewise polynomial kernels with analytic derivatives. | [KernelBase.h](KernelBase.h); C++ standard/system library | [IrwinHall.h](IrwinHall.h); [basis.md](basis.md); [CumulativeSplineTrajectory.ipynb](doc/CumulativeSplineTrajectory.ipynb) |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [basis.i](basis.i) | Declares basis wrapper interfaces or binding templates. | [BasisFactors.h](BasisFactors.h); [CardinalSplineBasis.h](CardinalSplineBasis.h); [Chebyshev.h](Chebyshev.h); [Chebyshev2.h](Chebyshev2.h); 5 other source includes | [matlab/CMakeLists.txt](../../matlab/CMakeLists.txt); [python/CMakeLists.txt](../../python/CMakeLists.txt) |
| [basis.md](basis.md) | Documents Basis. | None | [myst.yml](../../myst.yml) |
| [doc/](doc/README.md) | Indexes this maintained subfolder. | None | Developers |
| [tests/](tests/README.md) | Indexes this maintained subfolder. | None | Developers |

# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [AHRSFactor.ipynb](AHRSFactor.ipynb) | Explains or demonstrates AHRSFactor. | Jupyter/Python | [navigation.md](../navigation.md) |
| [AttitudeFactor.ipynb](AttitudeFactor.ipynb) | Explains or demonstrates AttitudeFactor. | Jupyter/Python | [gtsam/navigation/README.md](../README.md); [navigation.md](../navigation.md) |
| [BarometricFactor.ipynb](BarometricFactor.ipynb) | Explains or demonstrates BarometricFactor. | Jupyter/Python | [navigation.md](../navigation.md) |
| [CombinedImuFactor.ipynb](CombinedImuFactor.ipynb) | Explains or demonstrates CombinedImuFactor. | Jupyter/Python | [ImuFactorWithGravity.ipynb](ImuFactorWithGravity.ipynb); [navigation.md](../navigation.md) |
| [Combined_vs_ImuFactor.ipynb](Combined_vs_ImuFactor.ipynb) | Explains or demonstrates `ImuFactor` vs. `CombinedImuFactor`. | Jupyter/Python | None |
| [ConstantVelocityFactor.ipynb](ConstantVelocityFactor.ipynb) | Explains or demonstrates ConstantVelocityFactor. | Jupyter/Python | None |
| [DopplerFactor.ipynb](DopplerFactor.ipynb) | Explains or demonstrates GNSS Doppler Factors. | Jupyter/Python | [navigation.md](../navigation.md); [DopplerVelocityExample.ipynb](../../../python/gtsam/examples/navigation/DopplerVelocityExample.ipynb) |
| [EKF-variants.md](EKF-variants.md) | Documents EKF Variants. | None | [EquivariantFilter.ipynb](EquivariantFilter.ipynb); [InvariantEKF.ipynb](InvariantEKF.ipynb) |
| [EquivariantFilter.ipynb](EquivariantFilter.ipynb) | Explains or demonstrates EquivariantFilter User Guide. | Jupyter/Python | [EquivariantFilter.h](../EquivariantFilter.h); [EKF-variants.md](EKF-variants.md); [navigation.md](../navigation.md) |
| [GPSFactor.ipynb](GPSFactor.ipynb) | Explains or demonstrates GPSFactor Family. | Jupyter/Python | [navigation.md](../navigation.md) |
| [Gal3ImuEKF.ipynb](Gal3ImuEKF.ipynb) | Explains or demonstrates Gal3ImuEKF. | Jupyter/Python | [GalileanImuFactor.ipynb](GalileanImuFactor.ipynb) |
| [GalileanImuFactor.ipynb](GalileanImuFactor.ipynb) | Explains or demonstrates Galilean IMU preintegration with a left-invariant error. | Jupyter/Python | [GalileanPreintegration.h](../GalileanPreintegration.h); [navigation.md](../navigation.md) |
| [GalileanImuFactorNEES.ipynb](GalileanImuFactorNEES.ipynb) | Explains or demonstrates Galilean IMU preintegration: Logmap NEES and bias correction. | Jupyter/Python | [GalileanImuFactor.ipynb](GalileanImuFactor.ipynb); [Logmap_IMU_NEES.md](Logmap_IMU_NEES.md); [galilean_imu_factor_nees.py](galilean_imu_factor_nees.py); 1 other source references |
| [IMUIntegrationCovariance.md](IMUIntegrationCovariance.md) | Documents IMU integration covariance. | None | [gtsam/navigation/README.md](../README.md) |
| [ImuFactor.ipynb](ImuFactor.ipynb) | Explains or demonstrates ImuFactor. | Jupyter/Python | [GalileanImuFactor.ipynb](GalileanImuFactor.ipynb); [ImuFactorWithGravity.ipynb](ImuFactorWithGravity.ipynb); [navigation.md](../navigation.md) |
| [ImuFactorWithGravity.ipynb](ImuFactorWithGravity.ipynb) | Explains or demonstrates ImuFactorWithGravity Family. | Jupyter/Python | [CombinedImuFactor.ipynb](CombinedImuFactor.ipynb); [ImuFactor.ipynb](ImuFactor.ipynb); [VectorNormFactor.ipynb](../../nonlinear/doc/VectorNormFactor.ipynb) |
| [InvariantEKF.ipynb](InvariantEKF.ipynb) | Explains or demonstrates InvariantEKF User Guide. | Jupyter/Python | [ExtendedPose3.ipynb](../../geometry/doc/ExtendedPose3.ipynb); [EquivariantFilter.ipynb](EquivariantFilter.ipynb); [navigation.md](../navigation.md) |
| [LeggedEstimator.ipynb](LeggedEstimator.ipynb) | Explains or demonstrates Staircase Legged State Estimation. | Jupyter/Python | [LeggedEstimatorReplayExample.cpp](../../../examples/LeggedEstimatorReplayExample.cpp) |
| [Logmap_IMU_NEES.md](Logmap_IMU_NEES.md) | Documents Logmap IMU Preintegration Results. | None | [navigation.md](../navigation.md) |
| [MagFactor.ipynb](MagFactor.ipynb) | Explains or demonstrates MagFactor Family. | Jupyter/Python | [ImuFactorWithGravity.ipynb](ImuFactorWithGravity.ipynb); [navigation.md](../navigation.md); [VectorNormFactor.ipynb](../../nonlinear/doc/VectorNormFactor.ipynb) |
| [MagPoseFactor.ipynb](MagPoseFactor.ipynb) | Explains or demonstrates MagPoseFactor. | Jupyter/Python | [navigation.md](../navigation.md) |
| [NavState.ipynb](NavState.ipynb) | Explains or demonstrates NavState. | Jupyter/Python | [ExtendedPose3.ipynb](../../geometry/doc/ExtendedPose3.ipynb); [GalileanImuFactor.ipynb](GalileanImuFactor.ipynb); [navigation.md](../navigation.md) |
| [NavStateImuEKF.ipynb](NavStateImuEKF.ipynb) | Explains or demonstrates NavStateImuEKF. | Jupyter/Python | [EKF-variants.md](EKF-variants.md) |
| [PreintegratedCombinedMeasurements.ipynb](PreintegratedCombinedMeasurements.ipynb) | Explains or demonstrates PreintegratedCombinedMeasurements. | Jupyter/Python | None |
| [PreintegratedImuMeasurements.ipynb](PreintegratedImuMeasurements.ipynb) | Explains or demonstrates PreintegratedImuMeasurements. | Jupyter/Python | None |
| [PreintegratedRotation.ipynb](PreintegratedRotation.ipynb) | Explains or demonstrates PreintegratedRotation. | Jupyter/Python | [navigation.md](../navigation.md) |
| [PreintegrationCombinedParams.ipynb](PreintegrationCombinedParams.ipynb) | Explains or demonstrates PreintegrationCombinedParams. | Jupyter/Python | None |
| [PreintegrationParams.ipynb](PreintegrationParams.ipynb) | Explains or demonstrates PreintegrationParams. | Jupyter/Python | [navigation.md](../navigation.md) |
| [PseudorangeFactor.ipynb](PseudorangeFactor.ipynb) | Explains or demonstrates Pseudorange Factor. | Jupyter/Python | [navigation.md](../navigation.md); [DifferentialPseudorangeExample.ipynb](../../../python/gtsam/examples/navigation/DifferentialPseudorangeExample.ipynb); [SinglePointPositioningExample.ipynb](../../../python/gtsam/examples/navigation/SinglePointPositioningExample.ipynb) |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [Scenario.ipynb](Scenario.ipynb) | Explains or demonstrates Scenario Class Hierarchy. | Jupyter/Python | [navigation.md](../navigation.md) |
| [ScenarioRunner.ipynb](ScenarioRunner.ipynb) | Explains or demonstrates ScenarioRunner. | Jupyter/Python | [navigation.md](../navigation.md) |
| [galilean_imu_factor_nees.py](galilean_imu_factor_nees.py) | Numerical helpers for the Galilean IMU factor NEES notebook. | Python standard library; `gtsam`; `numpy`; `plotly`; 1 other declared imports/includes | [GalileanImuFactorNEES.ipynb](GalileanImuFactorNEES.ipynb); [Logmap_IMU_NEES.md](Logmap_IMU_NEES.md) |

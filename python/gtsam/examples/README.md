# Python Examples

Notebook examples are grouped by the GTSAM module they demonstrate:

| Folder | Topics |
|--------|--------|
| [geometry](geometry/) | Rotations |
| [basis](basis/) | Basis functions and spline trajectories |
| [linear](linear/) | Gaussian factor graphs and linear-quadratic control |
| [discrete](discrete/) | Discrete inference and hidden Markov models |
| [hybrid](hybrid/) | Hybrid inference |
| [nonlinear](nonlinear/) | Custom factors, optimization, filtering, and smoothing |
| [constrained](constrained/) | Linear, quadratic, and quadratically constrained programs |
| [certifiable](certifiable/) | Certifiable estimation and semidefinite relaxations |
| [navigation](navigation/) | IMU, GNSS, and continuous-time state estimation |
| [sfm](sfm/) | Cameras, structure from motion, and visual odometry |
| [slam](slam/) | Localization, pose graphs, and landmark SLAM |

Standalone Python scripts and shared helper modules live in this directory.
Import shared helpers through `gtsam.examples` so notebooks can run from their
module folders. Add new notebooks to the appropriate folder; the corresponding
MyST subsection discovers them automatically.

## Porting Progress

| C++ Example Name                                      | Ported |
|-------------------------------------------------------|--------|
| [CameraResectioning](sfm/CameraResectioning.ipynb) | :heavy_check_mark: |
| CombinedImuFactorsExample                             | :heavy_check_mark: |
| [CreateSFMExampleData](sfm/CreateSFMExampleData.ipynb) | :heavy_check_mark: |
| [DiscreteBayesNetExample](discrete/DiscreteBayesNetExample.ipynb) | :heavy_check_mark: |
| DiscreteBayesNet_FG                                   | none of the required discrete functionality is exposed through Python |
| [easyPoint2KalmanFilter](nonlinear/easyPoint2KalmanFilter.ipynb) | ExtendedKalmanFilter not yet exposed through Python |
| [elaboratePoint2KalmanFilter](nonlinear/elaboratePoint2KalmanFilter.ipynb) | GaussianSequentialSolver not yet exposed through Python |
| [FisheyeExample](sfm/FisheyeExample.ipynb) | :heavy_check_mark: |
| [FixedLagSmootherExample](nonlinear/FixedLagSmootherExample.ipynb) | :heavy_check_mark: |
| [HMMExample](discrete/HMMExample.ipynb) | :heavy_check_mark: |
| ImuFactorsExample2                                    | :heavy_check_mark: |
| ImuFactorsExample                                     |        |
| IMUKittiExampleGPS                                    | :heavy_check_mark: |
| InverseKinematicsExampleExpressions.cpp               |        |
| ISAM2Example_SmartFactor                              |        |
| ISAM2_SmartFactorStereo_IMU                           |        |
| LocalizationExample                                   | :heavy_check_mark: |
| METISOrderingExample                                  |        |
| [OdometryExample](slam/OdometryExample.ipynb) | :heavy_check_mark: |
| [PlanarSLAMExample](slam/PlanarSLAMExample.ipynb) | :heavy_check_mark: |
| [Pose2SLAMExample](slam/Pose2SLAMExample.ipynb) | :heavy_check_mark: |
| Pose2SLAMExampleExpressions                           | ExpressionFactorGraph not yet exposed through Python |
| Pose2SLAMExample_g2o                                  | :heavy_check_mark: |
| Pose2SLAMExample_graph                                | :heavy_check_mark: |
| Pose2SLAMExample_graphviz                             | :heavy_check_mark: |
| Pose2SLAMExample_lago                                 | lago not yet exposed through Python |
| [Pose2SLAMStressTest](slam/Pose2SLAMStressTest.ipynb) | :heavy_check_mark: |
| [Pose2SLAMwSPCG](slam/Pose2SLAMwSPCG.ipynb) | :heavy_check_mark: |
| Pose3Localization                                     |        |
| Pose3SLAMExample_changeKeys                           |        |
| Pose3SLAMExampleExpressions_BearingRangeWithTransform |        |
| Pose3SLAMExample_g2o                                  | :heavy_check_mark: |
| Pose3SLAMExample_initializePose3Chordal               | :heavy_check_mark: |
| Pose3SLAMExample_initializePose3Gradient              |        |
| [RangeISAMExample_plaza2](slam/RangeISAMExample_plaza2.ipynb) | :heavy_check_mark: |
| [SelfCalibrationExample](sfm/SelfCalibrationExample.ipynb) | :heavy_check_mark: |
| SFMdata                                               | :heavy_check_mark: |     
| SFMExample_bal_COLAMD_METIS                           |        |
| SFMExample_bal                                        | :heavy_check_mark: |
| [SFMExample](sfm/SFMExample.ipynb) | :heavy_check_mark: |
| SFMExampleExpressions_bal                             |        |
| SFMExampleExpressions                                 |        |
| SFMExample_SmartFactor                                |        |
| SFMExample_SmartFactorPCG                             |        |
| ShonanAveragingCLI                                    | :heavy_check_mark: |
| [SimpleRotation](geometry/SimpleRotation.ipynb) | :heavy_check_mark: |
| SolverComparer                                        |        |
| [StereoVOExample](sfm/StereoVOExample.ipynb) | :heavy_check_mark: |
| [StereoVOExample_large](sfm/StereoVOExample_large.ipynb) | :heavy_check_mark: |
| TimeTBB                                               |        |
| UGM_chain                                             | discrete functionality not yet exposed |
| UGM_small                                             | discrete functionality not yet exposed |
| VisualISAM2Example                                    | :heavy_check_mark: |
| [VisualISAMExample](sfm/VisualISAMExample.ipynb) | :heavy_check_mark: |

Extra Examples (with no C++ equivalent)
- [Fast CPU bundle adjustment with Full and Schur](sfm/SfmLevenbergMarquardtOptimizerExample.ipynb)
- [CardinalSplineBasisExample](basis/CardinalSplineBasisExample.ipynb)
- [CumulativeSplineTrajectoryExample](basis/CumulativeSplineTrajectoryExample.ipynb)
- [FitBasisExample](basis/FitBasisExample.ipynb)
- [PseudoSpectralChebyshevExample](basis/PseudoSpectralChebyshevExample.ipynb)
- [DogLegOptimizerExample](nonlinear/DogLegOptimizerExample.ipynb)
- [GPSFactorExample](navigation/GPSFactorExample.ipynb)
- PlanarManipulatorExample
- PreintegrationExample
- SFMData

Additional Notebook Examples

- [BearingRange3DExample](slam/BearingRange3DExample.ipynb)
- [DiscreteBayesTree](discrete/DiscreteBayesTree.ipynb)
- [DiscreteMotionModel](discrete/DiscreteMotionModel.ipynb)
- [DiscreteSwitching](discrete/DiscreteSwitching.ipynb)
- [EKF_SLAM](slam/EKF_SLAM.ipynb)
- [EqF](navigation/EqF.ipynb)
- [Gal3ImuASVExample](navigation/Gal3ImuASVExample.ipynb)
- [Gal3ImuExample](navigation/Gal3ImuExample.ipynb)
- [Gal3ImuNEESReset](navigation/Gal3ImuNEESReset.ipynb)
- [LQRExample](linear/LQRExample.ipynb)
- [NavStateImuASVExample](navigation/NavStateImuASVExample.ipynb)
- [NavStateImuExample](navigation/NavStateImuExample.ipynb)
- [NonlinearEqualityExample](nonlinear/NonlinearEqualityExample.ipynb)
- [RangeSLAMExample_plaza2](slam/RangeSLAMExample_plaza2.ipynb)
- [SL4SLAMExample](slam/SL4SLAMExample.ipynb)
- [SinglePointPositioningExample](navigation/SinglePointPositioningExample.ipynb)
- [iLQRExample](nonlinear/iLQRExample.ipynb)

## File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [.gitignore](.gitignore) | Excludes generated and local products from Git staging. | None | None |
| [AbcEquivariantFilterExample.py](AbcEquivariantFilterExample.py) | Python translation of examples/AbcEquivariantFilterExample.cpp. | Python standard library; `gtsam`; `numpy` | None |
| [CombinedImuFactorExample.py](CombinedImuFactorExample.py) | A script validating and demonstrating inference with the CombinedImuFactor. | Python standard library; `PreintegrationExample`; `gtsam`; `matplotlib`; 2 other declared imports/includes | None |
| [EqF.py](EqF.py) | Implements the attitude-bias-calibration equivariant filter example. | Python standard library; `gtsam`; `numpy` | None |
| [EssentialViewGraphExample.py](EssentialViewGraphExample.py) | Provides the Essential View Graph Example Python module. | `gtsam`; `numpy` | None |
| [GaussianProcessWnoaInterpolationSE3Helpers.py](GaussianProcessWnoaInterpolationSE3Helpers.py) | Provides the Gaussian Process Wnoa Interpolation SE3 Helpers Python module. | Python standard library; `PIL`; `gtsam`; `numpy`; 1 other declared imports/includes | None |
| [IMUKittiExampleGPS.py](IMUKittiExampleGPS.py) | Example of application of ISAM2 for GPS-aided navigation on the KITTI VISION BENCHMARK SUITE. | Python standard library; `gtsam`; `numpy` | None |
| [ImuFactorExample.py](ImuFactorExample.py) | A script validating and demonstrating the ImuFactor inference. | Python standard library; `PreintegrationExample`; `gtsam`; `matplotlib`; 2 other declared imports/includes | None |
| [ImuFactorISAM2Example.py](ImuFactorISAM2Example.py) | ImuFactor example with iSAM2. | Python standard library; `gtsam`; `matplotlib`; `mpl_toolkits`; 1 other declared imports/includes | None |
| [ImuFactorWithGravityExample.py](ImuFactorWithGravityExample.py) | A script demonstrating gravity estimation with the ImuFactorWithGravity family: a stationary IMU in a navigation frame whose true gravity is tilted away from the direction assumed by the preintegration parameters. | `gtsam`; `numpy` | None |
| [LandmarkLocalizationDataset.py](LandmarkLocalizationDataset.py) | Synthetic data for the known-landmark localization examples. | Python standard library; `gtsam`; `numpy` | None |
| [LeggedEstimatorExample.py](LeggedEstimatorExample.py) | Helper utilities for the staircase legged-estimation example. | Python standard library; `PIL`; `gtsam`; `numpy`; 1 other declared imports/includes | None |
| [PlanarManipulatorExample.py](PlanarManipulatorExample.py) | Kinematics of three-link manipulator with GTSAM poses and product of exponential maps. | Python standard library; `gtsam`; `matplotlib`; `mpl_toolkits`; 1 other declared imports/includes | None |
| [Pose2ISAM2Example.py](Pose2ISAM2Example.py) | Pose SLAM example using iSAM2 in the 2D plane. | Python standard library; `gtsam`; `matplotlib`; `numpy` | None |
| [Pose2SLAMExample_g2o.py](Pose2SLAMExample_g2o.py) | A 2D Pose SLAM example that reads input from g2o, converts it to a factor graph and does the optimization. | Python standard library; `gtsam`; `matplotlib` | None |
| [Pose2SLAMExample_lago.py](Pose2SLAMExample_lago.py) | A 2D Pose SLAM example that reads input from g2o, and solve the Pose2 problem using LAGO (Linear Approximation for Graph Optimization). | Python standard library; `gtsam`; `numpy` | None |
| [Pose3ISAM2Example.py](Pose3ISAM2Example.py) | Pose SLAM example using iSAM2 in 3D space. | Python standard library; `gtsam`; `matplotlib`; `numpy` | None |
| [Pose3SLAMExample_g2o.py](Pose3SLAMExample_g2o.py) | A 3D Pose SLAM example that reads input from g2o, and initializes the. | Python standard library; `gtsam`; `matplotlib`; `mpl_toolkits`; 1 other declared imports/includes | None |
| [Pose3SLAMExample_initializePose3Chordal.py](Pose3SLAMExample_initializePose3Chordal.py) | Initialize PoseSLAM with Chordal init. | Python standard library; `gtsam`; `numpy` | None |
| [PreintegrationExample.py](PreintegrationExample.py) | A script validating the Preintegration of IMU measurements. | Python standard library; `gtsam`; `matplotlib`; `mpl_toolkits`; 1 other declared imports/includes | None |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [SFMExample_SphericalCamera.py](SFMExample_SphericalCamera.py) | A structure-from-motion example using SphericalCamera. | `gtsam`; `matplotlib`; `numpy` | None |
| [SFMExample_bal.py](SFMExample_bal.py) | Solve a structure-from-motion problem from a "Bundle Adjustment in the Large" file. | Python standard library; `gtsam`; `matplotlib` | None |
| [SFMdata.py](SFMdata.py) | A structure-from-motion example with landmarks - The landmarks form a 10 meter cube - The robot rotates around the landmarks, always facing towards the cube. | Python standard library; `gtsam`; `numpy` | None |
| [ShonanAveragingCLI.py](ShonanAveragingCLI.py) | Shonan Rotation Averaging CLI reads a pose graph, extracts the rotation constraints, and runs the Shonan algorithm. | Python standard library; `gtsam`; `matplotlib`; `numpy` | None |
| [TranslationAveragingExample.py](TranslationAveragingExample.py) | This example shows how 1dsfm uses outlier rejection (MFAS) and optimization (translation recovery) together for estimating global translations from relative translation directions and global rotations. | Python standard library; `gtsam`; `numpy` | None |
| [ViewGraphComparison.py](ViewGraphComparison.py) | Compare several methods for optimizing the view-graph. | Python standard library; `gtsam`; `matplotlib`; `numpy` | None |
| [ViewGraphExample.py](ViewGraphExample.py) | Provides the View Graph Example Python module. | `gtsam`; `numpy` | None |
| [VisualISAM2Example.py](VisualISAM2Example.py) | An example of running visual SLAM using iSAM2. | Python standard library; `gtsam`; `matplotlib`; `mpl_toolkits`; 1 other declared imports/includes | None |
| [__init__.py](__init__.py) | Defines the Python package's import surface. | None | None |
| [basis/](basis/README.md) | Indexes this maintained subfolder. | None | Developers |
| [certifiable/](certifiable/README.md) | Indexes this maintained subfolder. | None | Developers |
| [constrained/](constrained/README.md) | Indexes this maintained subfolder. | None | Developers |
| [discrete/](discrete/README.md) | Indexes this maintained subfolder. | None | Developers |
| [geometry/](geometry/README.md) | Indexes this maintained subfolder. | None | Developers |
| [gnss_frontend.py](gnss_frontend.py) | GNSS front-end helpers for the RTK / PPP-RTK GTSAM examples. | Python standard library; `cssrlib`; `gtsam`; `numpy` | [DopplerVelocityExample.ipynb](navigation/DopplerVelocityExample.ipynb); [RtkAndPppExample.ipynb](navigation/RtkAndPppExample.ipynb) |
| [gnss_utils.py](gnss_utils.py) | Utility functions for processing and manipulating GNSS data. | Python standard library; `IPython`; `numpy`; `pyrtklib` | [gnss_frontend.py](gnss_frontend.py) |
| [gtsam_plotly.py](gtsam_plotly.py) | Provides the gtsam plotly Python module. | Python standard library; `graphviz`; `gtsam`; `numpy`; 2 other declared imports/includes | None |
| [hybrid/](hybrid/README.md) | Indexes this maintained subfolder. | None | Developers |
| [images/](images/README.md) | Indexes this maintained subfolder. | None | Developers |
| [linear/](linear/README.md) | Indexes this maintained subfolder. | None | Developers |
| [navigation/](navigation/README.md) | Indexes this maintained subfolder. | None | Developers |
| [nonlinear/](nonlinear/README.md) | Indexes this maintained subfolder. | None | Developers |
| [sfm/](sfm/README.md) | Indexes this maintained subfolder. | None | Developers |
| [simulation.py](simulation.py) | Provides the simulation Python module. | `gtsam`; `numpy` | None |
| [slam/](slam/README.md) | Indexes this maintained subfolder. | None | Developers |

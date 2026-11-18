# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [dfg_utils.py](dfg_utils.py) | Provides the dfg utils Python module. | `gtsam`; `numpy` | None |
| [test_AHRSFactor.py](test_AHRSFactor.py) | Checks AHRSFactor behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_AttitudeFactor.py](test_AttitudeFactor.py) | Checks Attitude Factor behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Cal3Fisheye.py](test_Cal3Fisheye.py) | Checks Cal3 Fisheye behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Cal3Unified.py](test_Cal3Unified.py) | Checks Cal3 Unified behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Chebyshev2.py](test_Chebyshev2.py) | Checks Chebyshev2 behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_CudaGnc.py](test_CudaGnc.py) | Checks Cuda Gnc behavior. | Python standard library; `gtsam`; `numpy` | [python/CMakeLists.txt](../../CMakeLists.txt) |
| [test_CudaSfm.py](test_CudaSfm.py) | Checks Cuda Sfm behavior. | Python standard library; `gtsam`; `numpy` | [python/CMakeLists.txt](../../CMakeLists.txt) |
| [test_CudaSparseLevenbergMarquardt.py](test_CudaSparseLevenbergMarquardt.py) | Checks Cuda Sparse Levenberg Marquardt behavior. | Python standard library; `gtsam`; `numpy` | [python/CMakeLists.txt](../../CMakeLists.txt) |
| [test_CumulativeSplineTrajectory.py](test_CumulativeSplineTrajectory.py) | Checks Cumulative Spline Trajectory behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_DCSAM.py](test_DCSAM.py) | Checks DCSAM behavior. | Python standard library; `gtsam` | None |
| [test_DSFMap.py](test_DSFMap.py) | Checks DSFMap behavior. | Python standard library; `gtsam` | None |
| [test_DecisionTreeFactor.py](test_DecisionTreeFactor.py) | Checks Decision Tree Factor behavior. | Python standard library; `gtsam` | None |
| [test_DiscreteBayesNet.py](test_DiscreteBayesNet.py) | Checks Discrete Bayes Net behavior. | Python standard library; `gtsam` | None |
| [test_DiscreteBayesTree.dot](test_DiscreteBayesTree.dot) | Retains the test Discrete Bayes Tree source or configuration file. | None | [test_DiscreteBayesTree.py](test_DiscreteBayesTree.py) |
| [test_DiscreteBayesTree.py](test_DiscreteBayesTree.py) | Checks Discrete Bayes Tree behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_DiscreteConditional.py](test_DiscreteConditional.py) | Checks Discrete Conditional behavior. | Python standard library; `gtsam` | None |
| [test_DiscreteDistribution.py](test_DiscreteDistribution.py) | Checks Discrete Distribution behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_DiscreteFactorGraph.py](test_DiscreteFactorGraph.py) | Checks Discrete Factor Graph behavior. | Python standard library; `dfg_utils`; `gtsam`; `numpy` | None |
| [test_DiscreteSearch.py](test_DiscreteSearch.py) | Checks Discrete Search behavior. | Python standard library; `dfg_utils`; `gtsam` | None |
| [test_DopplerFactor.py](test_DopplerFactor.py) | Checks Doppler Factor behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_DsfTrackGenerator.py](test_DsfTrackGenerator.py) | Checks Dsf Track Generator behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_EssentialMatrixConstraint.py](test_EssentialMatrixConstraint.py) | Checks Essential Matrix Constraint behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_ExtendedPose3.py](test_ExtendedPose3.py) | Checks Extended Pose3 behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Factors.py](test_Factors.py) | Checks Factors behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_FixedLagSmootherAccessors.py](test_FixedLagSmootherAccessors.py) | Checks Fixed Lag Smoother Accessors behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_FixedLagSmootherExample.py](test_FixedLagSmootherExample.py) | Checks Fixed Lag Smoother Example behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_FrobeniusFactor.py](test_FrobeniusFactor.py) | Checks Frobenius Factor behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_FundamentalMatrix.py](test_FundamentalMatrix.py) | Checks Fundamental Matrix behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Gal3.py](test_Gal3.py) | Checks Gal3 behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_GalileanImuFactor.py](test_GalileanImuFactor.py) | Checks Galilean Imu Factor behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_GaussianBayesNet.py](test_GaussianBayesNet.py) | Checks Gaussian Bayes Net behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_GaussianBayesTree.py](test_GaussianBayesTree.py) | Checks Gaussian Bayes Tree behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_GaussianFactorGraph.py](test_GaussianFactorGraph.py) | Checks Gaussian Factor Graph behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_GraphvizFormatting.py](test_GraphvizFormatting.py) | Checks Graphviz Formatting behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_HybridBayesNet.py](test_HybridBayesNet.py) | Checks Hybrid Bayes Net behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_HybridFactorGraph.py](test_HybridFactorGraph.py) | Checks Hybrid Factor Graph behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_HybridNonlinearFactorGraph.py](test_HybridNonlinearFactorGraph.py) | Checks Hybrid Nonlinear Factor Graph behavior. | Python standard library; `gtsam` | None |
| [test_HybridValues.py](test_HybridValues.py) | Checks Hybrid Values behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_ISAM2.py](test_ISAM2.py) | Checks ISAM2 behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_ISAM2FillIn.py](test_ISAM2FillIn.py) | Checks ISAM2 Fill In behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_ISAM2ResultKeys.py](test_ISAM2ResultKeys.py) | Checks ISAM2 Result Keys behavior. | Python standard library; `gtsam` | None |
| [test_ImuFactorWithGravity.py](test_ImuFactorWithGravity.py) | Checks Imu Factor With Gravity behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_JacobianFactor.py](test_JacobianFactor.py) | Checks Jacobian Factor behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_KalmanFilter.py](test_KalmanFilter.py) | Checks Kalman Filter behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_KarcherMeanFactor.py](test_KarcherMeanFactor.py) | Checks Karcher Mean Factor behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_KeyWidth.py](test_KeyWidth.py) | Checks Key Width behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_KnownLandmarkFactor.py](test_KnownLandmarkFactor.py) | Checks Known Landmark Factor behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_LandmarkLocalizationDataset.py](test_LandmarkLocalizationDataset.py) | Checks Landmark Localization Dataset behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_LeggedEstimator.py](test_LeggedEstimator.py) | Checks Legged Estimator behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_LocalizationExample.py](test_LocalizationExample.py) | Checks Localization Example behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Marginals.py](test_Marginals.py) | Checks Marginals behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_NavState.py](test_NavState.py) | Checks Nav State behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_NavigationFactorNoiseModel.py](test_NavigationFactorNoiseModel.py) | Checks Navigation Factor Noise Model behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_NoiseModelIntrospection.py](test_NoiseModelIntrospection.py) | Checks Noise Model Introspection behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_NonlinearOptimizer.py](test_NonlinearOptimizer.py) | Checks Nonlinear Optimizer behavior. | Python standard library; `gtsam` | None |
| [test_OdometryExample.py](test_OdometryExample.py) | Checks Odometry Example behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_OptionalJacobianArgument.py](test_OptionalJacobianArgument.py) | Checks Optional Jacobian Argument behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_PinholeCamera.py](test_PinholeCamera.py) | Checks Pinhole Camera behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_PlanarSLAMExample.py](test_PlanarSLAMExample.py) | Checks Planar SLAMExample behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Point2.py](test_Point2.py) | Checks Point2 behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Point3.py](test_Point3.py) | Checks Point3 behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Pose2.py](test_Pose2.py) | Checks Pose2 behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Pose2SLAMExample.py](test_Pose2SLAMExample.py) | Checks Pose2 SLAMExample behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Pose3.py](test_Pose3.py) | Checks Pose3 behavior. | Python standard library; `gtsam`; `numpy` | [wrap/README.md](../../../wrap/README.md) |
| [test_Pose3SLAMExample.py](test_Pose3SLAMExample.py) | Checks Pose3 SLAMExample behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_PreintegratedImuMeasurements.py](test_PreintegratedImuMeasurements.py) | Checks Preintegrated Imu Measurements behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_PreintegratedRotation.py](test_PreintegratedRotation.py) | Checks Preintegrated Rotation behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_PriorFactor.py](test_PriorFactor.py) | Checks Prior Factor behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_PseudorangeFactor.py](test_PseudorangeFactor.py) | Checks Pseudorange Factor behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_PybindOutputParameters.py](test_PybindOutputParameters.py) | Checks Pybind Output Parameters behavior. | `gtsam`; `numpy` | None |
| [test_QuadraticRangeFactor.py](test_QuadraticRangeFactor.py) | Checks Quadratic Range Factor behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_RelativeTranslationFactor.py](test_RelativeTranslationFactor.py) | Checks Relative Translation Factor behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Robust.py](test_Robust.py) | Checks Robust behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Rot3.py](test_Rot3.py) | Checks Rot3 behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_SFMExample.py](test_SFMExample.py) | Checks SFMExample behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_SO4.py](test_SO4.py) | Checks SO4 behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_SOn.py](test_SOn.py) | Checks SOn behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Scenario.py](test_Scenario.py) | Checks Scenario behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_ScenarioRunner.py](test_ScenarioRunner.py) | Checks Scenario Runner behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Se23.py](test_Se23.py) | Checks Se23 behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Serialization.py](test_Serialization.py) | Checks Serialization behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_SfmData.py](test_SfmData.py) | Checks Sfm Data behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_SfmLevenbergMarquardt.py](test_SfmLevenbergMarquardt.py) | Checks Sfm Levenberg Marquardt behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_ShonanAveraging.py](test_ShonanAveraging.py) | Checks Shonan Averaging behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Sim2.py](test_Sim2.py) | Checks Sim2 behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Sim3.py](test_Sim3.py) | Checks Sim3 behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_SimpleCamera.py](test_SimpleCamera.py) | Checks Simple Camera behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_SmartProjectionFactor.py](test_SmartProjectionFactor.py) | Checks Smart Projection Factor behavior. | Python standard library; `gtsam` | None |
| [test_SphericalCamera.py](test_SphericalCamera.py) | Checks Spherical Camera behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_StereoVOExample.py](test_StereoVOExample.py) | Checks Stereo VOExample behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_TargetedEstimate.py](test_TargetedEstimate.py) | Checks Targeted Estimate behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_TrajectoryAlignerSim3.py](test_TrajectoryAlignerSim3.py) | Checks Trajectory Aligner Sim3 behavior. | Python standard library; `gtsam` | None |
| [test_TranslationRecovery.py](test_TranslationRecovery.py) | Checks Translation Recovery behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Triangulation.py](test_Triangulation.py) | Checks Triangulation behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Utilities.py](test_Utilities.py) | Checks Utilities behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_Values.py](test_Values.py) | Checks Values behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_VisualISAMExample.py](test_VisualISAMExample.py) | Checks Visual ISAMExample behavior. | Python standard library; `gtsam` | None |
| [test_WahbaFactor.py](test_WahbaFactor.py) | Checks Wahba Factor behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_WnoaFactors.py](test_WnoaFactors.py) | Checks Wnoa Factors behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_WrapperTypeRegistrations.py](test_WrapperTypeRegistrations.py) | Checks Wrapper Type Registrations behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_backwards_compatibility.py](test_backwards_compatibility.py) | Checks backwards compatibility behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_basis.py](test_basis.py) | Checks basis behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_certifiable.py](test_certifiable.py) | Checks certifiable behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_constrained.py](test_constrained.py) | Checks constrained behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_custom_factor.py](test_custom_factor.py) | Checks custom factor behavior. | Python standard library; `gtsam`; `numpy` | [CustomFactor.ipynb](../../../gtsam/nonlinear/doc/CustomFactor.ipynb) |
| [test_dataset.py](test_dataset.py) | Checks dataset behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_fast_sync.py](test_fast_sync.py) | Checks fast sync behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_initialize_pose3.py](test_initialize_pose3.py) | Checks initialize pose3 behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_lago.py](test_lago.py) | Checks lago behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_logging_optimizer.py](test_logging_optimizer.py) | Checks logging optimizer behavior. | Python standard library; `cStringIO`; `comet_ml`; `gtsam`; 1 other declared imports/includes | None |
| [test_matrix_shape_checks.py](test_matrix_shape_checks.py) | Checks matrix shape checks behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_numerical_derivative.py](test_numerical_derivative.py) | Checks numerical derivative behavior. | Python standard library; `gtsam`; `numpy` | None |
| [test_pickle.py](test_pickle.py) | Checks pickle behavior. | Python standard library; `gtsam` | None |
| [test_sam.py](test_sam.py) | Checks sam behavior. | Python standard library; `gtsam` | None |

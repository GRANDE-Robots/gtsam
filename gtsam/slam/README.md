# SLAM Factors

## GenericProjectionFactor (defined in ProjectionFactor.h)

Non-linear factor that minimizes the re-projection error with respect to a 2D measurement. 
The calibration is assumed known and passed in the constructor.
The main building block for visual SLAM.

Templated on
- `POSE`, default `Pose3`
- `LANDMARK`, default `Point3`
- `CALIBRATION`, default `Cal3_S2`

## SmartFactors

These are "structure-less" factors, i.e., rather than introducing a new variable for an observed 3D point or landmark, a single factor is created that provides a multi-view constraint on several poses and/or cameras.
While one typically adds multiple GenericProjectionFactors (one for each observation of a landmark), a SmartFactor collects all measurements for a landmark, i.e., the factor graph contains 1 smart factor per landmark.

### SmartFactorBase

This is the base class for smart factors, templated on a `CAMERA` type.
It has no internal point, but it saves the measurements, keeps a noise model, and an optional sensor pose.

### SmartProjectionFactor

Also templated on `CAMERA`. Triangulates a 3D point and keeps an estimate of it around.
This factor operates with monocular cameras, and is used to optimize the camera pose
*and* calibration for each camera, and requires variables of type `CAMERA` in values.

If the calibration is fixed use `SmartProjectionPoseFactor` instead!


### SmartProjectionPoseFactor

Derives from `SmartProjectionFactor` but is templated on a `CALIBRATION` type, setting `CAMERA = PinholePose<CALIBRATION>`.
This factor assumes that the camera calibration is fixed and the same for all cameras involved in this factor.
The factor only constrains poses.

If the calibration should be optimized, as well, use `SmartProjectionFactor` instead!

### SmartProjectionRigFactor

Same as `SmartProjectionPoseFactor`, except:
- it is templated on `CAMERA`, i.e., it allows cameras beyond pinhole;
- it allows measurements from multiple cameras, each camera with fixed but potentially different intrinsics and extrinsics;
- it allows multiple observations from the same pose/key, again, to model a multi-camera system.

## Linearized Smart Factors

The factors below are less likely to be relevant to the user, but result from using the non-linear smart factors above.


### RegularImplicitSchurFactor

A specialization of a GaussianFactor to structure-less SFM, which is very fast in a conjugate gradient (CG) solver. 
It is produced by calling `createRegularImplicitSchurFactor` in `SmartFactorBase` or `SmartProjectionFactor`. 

### JacobianFactorQ

A RegularJacobianFactor that uses some badly documented reduction on the Jacobians.

### JacobianFactorQR

A RegularJacobianFactor that eliminates a point using sequential elimination.

### JacobianFactorSVD

A RegularJacobianFactor that uses the "Nullspace Trick" by Mourikis et al. See the documentation in the file, which *is* well documented.

## File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [AntiFactor.h](AntiFactor.h) | Declares Anti Factor types or operations. | [gtsam/nonlinear/AntiFactor.h](../nonlinear/AntiFactor.h); `gtsam` headers | [testHeaderMoveCompatibility.cpp](../../tests/testHeaderMoveCompatibility.cpp) |
| [BearingFactor.h](BearingFactor.h) | Declares Bearing Factor types or operations. | [gtsam/sam/BearingFactor.h](../sam/BearingFactor.h) | None |
| [BearingRangeFactor.h](BearingRangeFactor.h) | Declares Bearing Range Factor types or operations. | [gtsam/sam/BearingRangeFactor.h](../sam/BearingRangeFactor.h) | None |
| [BetweenFactor.h](BetweenFactor.h) | Declares Between Factor types or operations. | [Lie.h](../base/Lie.h); [Testable.h](../base/Testable.h); [FixedJacobianFactor.h](../linear/FixedJacobianFactor.h); [NoiseModelFactorN.h](../nonlinear/NoiseModelFactorN.h); 1 other source includes; C++ standard/system library | [cmake/example_cmake_find_gtsam/main.cpp](../../cmake/example_cmake_find_gtsam/main.cpp); [CertifiableLocalizationUtils.h](../../examples/CertifiableLocalizationUtils.h); [CertifiablePoseGraphOptimization.cpp](../../examples/CertifiablePoseGraphOptimization.cpp); 120 other source references |
| [BoundingConstraint.h](BoundingConstraint.h) | Declares Bounding Constraint types or operations. | [gtsam/constrained/BoundingConstraint.h](../constrained/BoundingConstraint.h); `gtsam` headers | [testHeaderMoveCompatibility.cpp](../../tests/testHeaderMoveCompatibility.cpp) |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [EssentialMatrixConstraint.h](EssentialMatrixConstraint.h) | Declares Essential Matrix Constraint types or operations. | [gtsam/sfm/EssentialMatrixConstraint.h](../sfm/EssentialMatrixConstraint.h); `gtsam` headers | [testHeaderMoveCompatibility.cpp](../../tests/testHeaderMoveCompatibility.cpp) |
| [EssentialMatrixFactor.h](EssentialMatrixFactor.h) | Declares Essential Matrix Factor types or operations. | [gtsam/sfm/EssentialMatrixFactor.h](../sfm/EssentialMatrixFactor.h); `gtsam` headers | [testHeaderMoveCompatibility.cpp](../../tests/testHeaderMoveCompatibility.cpp) |
| [FastSync-inl.h](FastSync-inl.h) | Template implementation for fixed-size FAST-Sync. | [gtsam/inference/Ordering.h](../inference/Ordering.h); [GaussianBayesNet.h](../linear/GaussianBayesNet.h); [GaussianFactorGraph.h](../linear/GaussianFactorGraph.h); [JacobianFactor.h](../linear/JacobianFactor.h); 2 other source includes; C++ standard/system library | [FastSync.h](FastSync.h) |
| [FastSync.h](FastSync.h) | Fast initialization for synchronization over matrix Lie groups. | [FastMap.h](../base/FastMap.h); [MatrixLieGroup.h](../base/MatrixLieGroup.h); [Pose2.h](../geometry/Pose2.h); [Pose3.h](../geometry/Pose3.h); 12 other source includes; C++ standard/system library; `Eigen` headers; `gtsam` headers | [CertifiableLandmarkSLAM.cpp](../../examples/CertifiableLandmarkSLAM.cpp); [CertifiablePoseGraphOptimization.cpp](../../examples/CertifiablePoseGraphOptimization.cpp); [CertifiableRangeAidedSLAM.cpp](../../examples/CertifiableRangeAidedSLAM.cpp); 8 other source references |
| [FrobeniusFactor.cpp](FrobeniusFactor.cpp) | Various factors that minimize some Frobenius norm. | [FrobeniusFactor.h](FrobeniusFactor.h) | [ShonanFactor.cpp](../sfm/ShonanFactor.cpp) |
| [FrobeniusFactor.h](FrobeniusFactor.h) | Various factors that minimize some Frobenius norm. | [QcqpProblem.h](../constrained/QcqpProblem.h); [QpCost.h](../constrained/QpCost.h); [Pose2.h](../geometry/Pose2.h); [Pose3.h](../geometry/Pose3.h); 5 other source includes; C++ standard/system library | [CertifiableLandmarkSLAM.cpp](../../examples/CertifiableLandmarkSLAM.cpp); [CertifiableLocalizationUtils.h](../../examples/CertifiableLocalizationUtils.h); [CertifiableMosek.h](../../examples/CertifiableMosek.h); 19 other source references |
| [GeneralSFMFactor.h](GeneralSFMFactor.h) | a general SFM factor with an unknown calibration. | [Manifold.h](../base/Manifold.h); [gtsam/base/Matrix.h](../base/Matrix.h); [SymmetricBlockMatrix.h](../base/SymmetricBlockMatrix.h); [Testable.h](../base/Testable.h); 13 other source includes; C++ standard/system library; `boost` headers | [stats.html](../../doc/stats.html); [SFMExample_bal.cpp](../../examples/SFMExample_bal.cpp); [SFMExample_bal_COLAMD_METIS.cpp](../../examples/SFMExample_bal_COLAMD_METIS.cpp); 18 other source references |
| [InitializePose.h](InitializePose.h) | common code between lago. (2D) and InitializePose3. (3D). | [gtsam/inference/Symbol.h](../inference/Symbol.h); [GaussNewtonOptimizer.h](../nonlinear/GaussNewtonOptimizer.h); [NonlinearFactorGraph.h](../nonlinear/NonlinearFactorGraph.h); [gtsam/nonlinear/PriorFactor.h](../nonlinear/PriorFactor.h); 1 other source includes | [ShonanAveragingCLI.cpp](../../examples/ShonanAveragingCLI.cpp); [InitializePose3.cpp](InitializePose3.cpp); [lago.cpp](lago.cpp); 2 other source references |
| [InitializePose3.cpp](InitializePose3.cpp) | Implements Initialize Pose3 operations. | [MatrixConstants.h](../base/MatrixConstants.h); [VectorConstants.h](../base/VectorConstants.h); [timing.h](../base/timing.h); [Pose2.h](../geometry/Pose2.h); 7 other source includes; C++ standard/system library | None |
| [InitializePose3.h](InitializePose3.h) | Initialize Pose3 in a factor graph. | [Rot3.h](../geometry/Rot3.h); [GaussianFactorGraph.h](../linear/GaussianFactorGraph.h); [VectorValues.h](../linear/VectorValues.h); [NonlinearFactorGraph.h](../nonlinear/NonlinearFactorGraph.h); C++ standard/system library | [Pose3SLAMExample_initializePose3Chordal.cpp](../../examples/Pose3SLAMExample_initializePose3Chordal.cpp); [Pose3SLAMExample_initializePose3Gradient.cpp](../../examples/Pose3SLAMExample_initializePose3Gradient.cpp); [InitializePose3.cpp](InitializePose3.cpp); 3 other source references |
| [JacobianFactorQ.h](JacobianFactorQ.h) | Declares Jacobian Factor Q types or operations. | [RegularJacobianFactor.h](../linear/RegularJacobianFactor.h) | [SmartFactorBase.h](SmartFactorBase.h); [JacobianFactorQ.ipynb](doc/JacobianFactorQ.ipynb); [SmartFactors.md](doc/SmartFactors.md); 8 other source references |
| [JacobianFactorQR.h](JacobianFactorQR.h) | Jacobianfactor that combines and eliminates points. | [gtsam/inference/Symbol.h](../inference/Symbol.h); [GaussianFactorGraph.h](../linear/GaussianFactorGraph.h); [RegularJacobianFactor.h](../linear/RegularJacobianFactor.h) | [testRegularImplicitSchurFactor.cpp](tests/testRegularImplicitSchurFactor.cpp); [timeSchurFactors.cpp](../../timing/timeSchurFactors.cpp) |
| [JacobianFactorSVD.h](JacobianFactorSVD.h) | Construct a new JacobianFactorSVD object, createing a reduced-rank. | [RegularJacobianFactor.h](../linear/RegularJacobianFactor.h) | [SmartFactorBase.h](SmartFactorBase.h); [SmartFactors.md](doc/SmartFactors.md) |
| [KarcherMeanFactor-inl.h](KarcherMeanFactor-inl.h) | Declares Karcher Mean Factor inl types or operations. | [GaussNewtonOptimizer.h](../nonlinear/GaussNewtonOptimizer.h); [NonlinearFactorGraph.h](../nonlinear/NonlinearFactorGraph.h); [KarcherMeanFactor.h](KarcherMeanFactor.h); C++ standard/system library | [Similarity2.cpp](../geometry/Similarity2.cpp); [Similarity3.cpp](../geometry/Similarity3.cpp); [ShonanAveraging.cpp](../sfm/ShonanAveraging.cpp); 3 other source references |
| [KarcherMeanFactor.h](KarcherMeanFactor.h) | Declares Karcher Mean Factor types or operations. | [gtsam/base/Matrix.h](../base/Matrix.h); [JacobianFactor.h](../linear/JacobianFactor.h); C++ standard/system library | [KarcherMeanFactor-inl.h](KarcherMeanFactor-inl.h); [KarcherMeanFactor.ipynb](doc/KarcherMeanFactor.ipynb); [testKarcherMeanFactor.cpp](tests/testKarcherMeanFactor.cpp); 1 other source references |
| [KnownLandmarkFactor.h](KnownLandmarkFactor.h) | Factors for observing a known landmark under an unknown transform. | [QcqpProblem.h](../constrained/QcqpProblem.h); [QpCost.h](../constrained/QpCost.h); [Pose2.h](../geometry/Pose2.h); [Pose3.h](../geometry/Pose3.h); 1 other source includes; C++ standard/system library | [CertifiableLocalizationUtils.h](../../examples/CertifiableLocalizationUtils.h); [slam.i](slam.i); [testKnownLandmarkFactor.cpp](tests/testKnownLandmarkFactor.cpp) |
| [OrientedPlane3Factor.cpp](OrientedPlane3Factor.cpp) | Implements Oriented Plane3 Factor operations. | [VectorConstants.h](../base/VectorConstants.h); [OrientedPlane3Factor.h](OrientedPlane3Factor.h) | [OrientedPlane3Factor.h](OrientedPlane3Factor.h) |
| [OrientedPlane3Factor.h](OrientedPlane3Factor.h) | OrientedPlane3 Factor class. | [OrientedPlane3.h](../geometry/OrientedPlane3.h); [NoiseModelFactorN.h](../nonlinear/NoiseModelFactorN.h); [NonlinearFactor.h](../nonlinear/NonlinearFactor.h) | [OrientedPlane3Factor.cpp](OrientedPlane3Factor.cpp); [slam.i](slam.i); [testOrientedPlane3Factor.cpp](tests/testOrientedPlane3Factor.cpp) |
| [PlanarProjectionFactor.h](PlanarProjectionFactor.h) | for planar smoothing. | [Lie.h](../base/Lie.h); [Testable.h](../base/Testable.h); [Cal3DS2.h](../geometry/Cal3DS2.h); [PinholeCamera.h](../geometry/PinholeCamera.h); 6 other source includes | [slam.i](slam.i); [testPlanarProjectionFactor.cpp](tests/testPlanarProjectionFactor.cpp) |
| [PoseRotationPrior.h](PoseRotationPrior.h) | Implements a prior on the rotation component of a pose. | [Manifold.h](../base/Manifold.h); [gtsam/geometry/concepts.h](../geometry/concepts.h); [NoiseModelFactorN.h](../nonlinear/NoiseModelFactorN.h); [NonlinearFactor.h](../nonlinear/NonlinearFactor.h) | [slam.i](slam.i); [testPoseRotationPrior.cpp](tests/testPoseRotationPrior.cpp) |
| [PoseTranslationPrior.h](PoseTranslationPrior.h) | Implements a prior on the translation component of a pose. | [Manifold.h](../base/Manifold.h); [gtsam/geometry/concepts.h](../geometry/concepts.h); [NoiseModelFactorN.h](../nonlinear/NoiseModelFactorN.h); [NonlinearFactor.h](../nonlinear/NonlinearFactor.h) | [slam.i](slam.i); [testPoseTranslationPrior.cpp](tests/testPoseTranslationPrior.cpp); [testSmartProjectionPoseFactor.cpp](tests/testSmartProjectionPoseFactor.cpp); 4 other source references |
| [PriorFactor.h](PriorFactor.h) | Declares Prior Factor types or operations. | [gtsam/nonlinear/PriorFactor.h](../nonlinear/PriorFactor.h) | [FisheyeExample.cpp](../../examples/FisheyeExample.cpp); [IMUKittiExampleGPS.cpp](../../examples/IMUKittiExampleGPS.cpp); [testLine3.cpp](../geometry/tests/testLine3.cpp); 8 other source references |
| [ProjectionFactor.h](ProjectionFactor.h) | Reprojection of a LANDMARK to a 2D point. | [Cal3_S2.h](../geometry/Cal3_S2.h); [PinholeCamera.h](../geometry/PinholeCamera.h); [Point3.h](../geometry/Point3.h); [Pose3.h](../geometry/Pose3.h); 3 other source includes; C++ standard/system library | [FisheyeExample.cpp](../../examples/FisheyeExample.cpp); [SFMExample.cpp](../../examples/SFMExample.cpp); [VisualISAM2Example.cpp](../../examples/VisualISAM2Example.cpp); 21 other source references |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [RangeFactor.h](RangeFactor.h) | Declares Range Factor types or operations. | [gtsam/sam/RangeFactor.h](../sam/RangeFactor.h) | None |
| [ReferenceFrameFactor.h](ReferenceFrameFactor.h) | A constraint for combining graphs by common landmarks and a transform node. | [NonlinearFactor.h](../nonlinear/NonlinearFactor.h) | [testCudaSparseLevenbergMarquardt.cpp](../nonlinear/tests/testCudaSparseLevenbergMarquardt.cpp); [slam.i](slam.i); [testReferenceFrameFactor.cpp](tests/testReferenceFrameFactor.cpp) |
| [RegularImplicitSchurFactor.h](RegularImplicitSchurFactor.h) | A subclass of GaussianFactor specialized to structureless SFM. | [CameraSet.h](../geometry/CameraSet.h); [FlatGaussianFactor.h](../linear/FlatGaussianFactor.h); [JacobianFactor.h](../linear/JacobianFactor.h); [VectorValues.h](../linear/VectorValues.h); C++ standard/system library | [SmartFactorBase.h](SmartFactorBase.h); [SmartFactors.md](doc/SmartFactors.md); [testRegularImplicitSchurFactor.cpp](tests/testRegularImplicitSchurFactor.cpp); 4 other source references |
| [RelativeTranslationFactor.h](RelativeTranslationFactor.h) | Quadratic translation factor: the translation part of a relative. | [gtsam/base/Matrix.h](../base/Matrix.h); [QcqpProblem.h](../constrained/QcqpProblem.h); [QpCost.h](../constrained/QpCost.h); [Rot2.h](../geometry/Rot2.h); 3 other source includes; C++ standard/system library | [CertifiableLandmarkSLAM.cpp](../../examples/CertifiableLandmarkSLAM.cpp); [CertifiablePoseGraphOptimization.cpp](../../examples/CertifiablePoseGraphOptimization.cpp); [CertifiableRangeAidedSLAM.cpp](../../examples/CertifiableRangeAidedSLAM.cpp); 3 other source references |
| [RotateFactor.h](RotateFactor.h) | RotateFactor class. | [Rot3.h](../geometry/Rot3.h); [NoiseModelFactorN.h](../nonlinear/NoiseModelFactorN.h); [NonlinearFactor.h](../nonlinear/NonlinearFactor.h) | [slam.i](slam.i); [testRotateFactor.cpp](tests/testRotateFactor.cpp) |
| [SmartFactorBase.h](SmartFactorBase.h) | Base class to create smart factors on poses or cameras. | [CameraSet.h](../geometry/CameraSet.h); [RegularHessianFactor.h](../linear/RegularHessianFactor.h); [NonlinearFactor.h](../nonlinear/NonlinearFactor.h); [JacobianFactorQ.h](JacobianFactorQ.h); 2 other source includes; C++ standard/system library; `boost` headers | [SmartProjectionFactorBase.h](SmartProjectionFactorBase.h); [SmartFactorBase.ipynb](doc/SmartFactorBase.ipynb); [SmartFactors.md](doc/SmartFactors.md); 5 other source references |
| [SmartFactorParams.h](SmartFactorParams.h) | Collect common parameters for SmartProjection and SmartStereoProjection factors. | [triangulation.h](../geometry/triangulation.h) | [SmartProjectionFactorBase.h](SmartProjectionFactorBase.h); [SmartFactorParams.ipynb](doc/SmartFactorParams.ipynb); [SmartFactors.md](doc/SmartFactors.md); 3 other source references |
| [SmartProjectionFactor.h](SmartProjectionFactor.h) | Smart factor on cameras (pose + calibration). | [SmartProjectionFactorBase.h](SmartProjectionFactorBase.h) | [SFMExample_SmartFactor_bal.cpp](../../examples/SFMExample_SmartFactor_bal.cpp); [SmartProjectionRigFactor.h](SmartProjectionRigFactor.h); [slam.i](slam.i); 6 other source references |
| [SmartProjectionFactorBase.h](SmartProjectionFactorBase.h) | Base class for smart projection factors. | [triangulation.h](../geometry/triangulation.h); [SmartFactorBase.h](SmartFactorBase.h); [SmartFactorParams.h](SmartFactorParams.h); C++ standard/system library | [SmartProjectionFactor.h](SmartProjectionFactor.h); [SmartProjectionPoseFactor.h](SmartProjectionPoseFactor.h) |
| [SmartProjectionPoseFactor.h](SmartProjectionPoseFactor.h) | Smart factor on poses, assuming camera calibration is fixed. | [SmartProjectionFactorBase.h](SmartProjectionFactorBase.h) | [ISAM2Example_SmartFactor.cpp](../../examples/ISAM2Example_SmartFactor.cpp); [SFMExample_SmartFactor.cpp](../../examples/SFMExample_SmartFactor.cpp); [SFMExample_SmartFactorPCG.cpp](../../examples/SFMExample_SmartFactorPCG.cpp); 6 other source references |
| [SmartProjectionRigFactor.h](SmartProjectionRigFactor.h) | Smart factor on poses, assuming camera calibration is fixed. | [SmartProjectionFactor.h](SmartProjectionFactor.h) | [SmartFactors.md](doc/SmartFactors.md); [slam.i](slam.i); [smartFactorScenarios.h](tests/smartFactorScenarios.h) |
| [StereoFactor.h](StereoFactor.h) | A non-linear factor for stereo measurements. | [MatrixConstants.h](../base/MatrixConstants.h); [StereoCamera.h](../geometry/StereoCamera.h); [FixedJacobianFactor.h](../linear/FixedJacobianFactor.h); [NoiseModelFactorN.h](../nonlinear/NoiseModelFactorN.h); 1 other source includes; C++ standard/system library | [stats.html](../../doc/stats.html); [Pose2SLAMStressTest.cpp](../../examples/Pose2SLAMStressTest.cpp); [StereoVOExample.cpp](../../examples/StereoVOExample.cpp); 10 other source references |
| [TriangulationFactor.h](TriangulationFactor.h) | Declares Triangulation Factor types or operations. | [CalibratedCamera.h](../geometry/CalibratedCamera.h); [NoiseModelFactorN.h](../nonlinear/NoiseModelFactorN.h); C++ standard/system library | [triangulation.h](../geometry/triangulation.h); [slam.i](slam.i) |
| [WahbaFactor.h](WahbaFactor.h) | Chordal Wahba factor with exact QCQP conversion. | [QcqpProblem.h](../constrained/QcqpProblem.h); [QpCost.h](../constrained/QpCost.h); [Rot3.h](../geometry/Rot3.h); [Unit3.h](../geometry/Unit3.h); 1 other source includes; C++ standard/system library | [slam.i](slam.i); [testWahbaFactor.cpp](tests/testWahbaFactor.cpp) |
| [dataset.cpp](dataset.cpp) | utility functions for loading datasets. | [GenericValue.h](../base/GenericValue.h); [Lie.h](../base/Lie.h); [gtsam/base/Matrix.h](../base/Matrix.h); [MatrixConstants.h](../base/MatrixConstants.h); 14 other source includes; C++ standard/system library; `Eigen` headers; `experimental` headers; `locale` | [stats.html](../../doc/stats.html); [ShonanAveraging.cpp](../sfm/ShonanAveraging.cpp); [testDataset.cpp](tests/testDataset.cpp); 1 other source references |
| [dataset.h](dataset.h) | utility functions for loading datasets. | [Testable.h](../base/Testable.h); [types.h](../base/types.h); [Pose2.h](../geometry/Pose2.h); [Pose3.h](../geometry/Pose3.h); 6 other source includes; C++ standard/system library | [AbcEquivariantFilterExample.cpp](../../examples/AbcEquivariantFilterExample.cpp); [CertifiableLocalizationUtils.h](../../examples/CertifiableLocalizationUtils.h); [CertifiablePoseGraphOptimization.cpp](../../examples/CertifiablePoseGraphOptimization.cpp); 71 other source references |
| [doc/](doc/README.md) | Indexes this maintained subfolder. | None | Developers |
| [expressions.h](expressions.h) | Common expressions for solving geometry/slam/sfm problems. | [Cal3Bundler.h](../geometry/Cal3Bundler.h); [Cal3_S2.h](../geometry/Cal3_S2.h); [Line3.h](../geometry/Line3.h); [OrientedPlane3.h](../geometry/OrientedPlane3.h); 3 other source includes | [ClockRecoveryContinuousTrajectory.cpp](../../examples/ClockRecoveryContinuousTrajectory.cpp); [InverseKinematicsExampleExpressions.cpp](../../examples/InverseKinematicsExampleExpressions.cpp); [Pose2SLAMExampleExpressions.cpp](../../examples/Pose2SLAMExampleExpressions.cpp); 20 other source references |
| [lago.cpp](lago.cpp) | Implements lago operations. | [MatrixConstants.h](../base/MatrixConstants.h); [VectorConstants.h](../base/VectorConstants.h); [timing.h](../base/timing.h); [Pose2.h](../geometry/Pose2.h); 6 other source includes; C++ standard/system library | None |
| [lago.h](lago.h) | Initialize Pose2 in a factor graph using LAGO. | [GaussianFactorGraph.h](../linear/GaussianFactorGraph.h); [VectorValues.h](../linear/VectorValues.h); [NonlinearFactorGraph.h](../nonlinear/NonlinearFactorGraph.h) | [Pose2SLAMExample_lago.cpp](../../examples/Pose2SLAMExample_lago.cpp); [lago.cpp](lago.cpp); [slam.i](slam.i); 2 other source references |
| [slam.i](slam.i) | Declares slam wrapper interfaces or binding templates. | [ExtendedPose3.h](../geometry/ExtendedPose3.h); [Gal3.h](../geometry/Gal3.h); [SL4.h](../geometry/SL4.h); [SO4.h](../geometry/SO4.h); 30 other source includes | [matlab/CMakeLists.txt](../../matlab/CMakeLists.txt); [python/CMakeLists.txt](../../python/CMakeLists.txt) |
| [slam.md](slam.md) | Documents SLAM. | None | [myst.yml](../../myst.yml) |
| [tests/](tests/README.md) | Indexes this maintained subfolder. | None | Developers |

# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [.gitignore](.gitignore) | Excludes generated and local products from Git staging. | None | None |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [CUDA_LINEAR_SOLVERS.md](CUDA_LINEAR_SOLVERS.md) | Documents CUDA linear solvers. | [SparseLevenbergMarquardt.h](../gtsam/nonlinear/cuda/SparseLevenbergMarquardt.h); `gtsam` headers | [INSTALL.md](../INSTALL.md); [README.md](../README.md); [HandleCuda.cmake](../cmake/HandleCuda.cmake); 3 other source references |
| [Code/](Code/README.md) | Indexes this maintained subfolder. | None | Developers |
| [CodingGuidelines.docx](CodingGuidelines.docx) | Retains the Coding Guidelines source or configuration file. | None | None |
| [CodingGuidelines.lyx](CodingGuidelines.lyx) | Retains the Coding Guidelines LyX document source. | LyX | None |
| [CovarianceRecovery.pdf](CovarianceRecovery.pdf) | Retains the Covariance Recovery illustration or document. | None | [Marginals.ipynb](../gtsam/nonlinear/doc/Marginals.ipynb) |
| [Doxyfile.in](Doxyfile.in) | Templates the generated Doxyfile configuration. | None | None |
| [Doxyfile.xml.in](Doxyfile.xml.in) | Templates the generated Doxyfile.xml configuration. | None | [doc/CMakeLists.txt](CMakeLists.txt) |
| [DoxygenLayout.xml](DoxygenLayout.xml) | Defines Doxygen Layout XML configuration. | None | [doc/Doxyfile.in](Doxyfile.in); [gtsam/3rdparty/Eigen/doc/Doxyfile.in](../gtsam/3rdparty/Eigen/doc/Doxyfile.in) |
| [GTSAM-Concepts.md](GTSAM-Concepts.md) | Documents GTSAM Concepts. | None | [README.md](../README.md); [Group.md](../gtsam/base/doc/Group.md); [Manifold.md](../gtsam/base/doc/Manifold.md); 2 other source references |
| [Hybrid.lyx](Hybrid.lyx) | Retains the Hybrid LyX document source. | LyX | None |
| [Hybrid.pdf](Hybrid.pdf) | Retains the Hybrid illustration or document. | None | None |
| [ImuFactor.lyx](ImuFactor.lyx) | Retains the Imu Factor LyX document source. | LyX | [TangentPreintegration.cpp](../gtsam/navigation/TangentPreintegration.cpp); [TangentPreintegration.h](../gtsam/navigation/TangentPreintegration.h) |
| [ImuFactor.pdf](ImuFactor.pdf) | Retains the Imu Factor illustration or document. | None | [README.md](../README.md); [ImuFactorWithGravity.ipynb](../gtsam/navigation/doc/ImuFactorWithGravity.ipynb) |
| [LieGroups.lyx](LieGroups.lyx) | Retains the Lie Groups LyX document source. | LyX | None |
| [LieGroups.pdf](LieGroups.pdf) | Retains the Lie Groups illustration or document. | None | [gtsam.lyx](gtsam.lyx); [Similarity3.cpp](../gtsam/geometry/Similarity3.cpp) |
| [Mathematica/](Mathematica/README.md) | Indexes this maintained subfolder. | None | Developers |
| [PreintegratedIMUJacobians.pdf](PreintegratedIMUJacobians.pdf) | Retains the Preintegrated IMUJacobians illustration or document. | None | [CombinedImuFactor.h](../gtsam/navigation/CombinedImuFactor.h); [ImuFactor.h](../gtsam/navigation/ImuFactor.h); [gtsam/navigation/README.md](../gtsam/navigation/README.md) |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [cholesky.lyx](cholesky.lyx) | Retains the cholesky LyX document source. | LyX | None |
| [common_macros.tex](common_macros.tex) | Defines common macros LaTeX content or macros. | LaTeX | [gtsam.lyx](gtsam.lyx) |
| [examples.md](examples.md) | Documents Examples. | None | [myst.yml](../myst.yml) |
| [expressions.md](expressions.md) | Documents Expressions. | None | [README.md](../README.md); [ExpressionFactor.ipynb](../gtsam/nonlinear/doc/ExpressionFactor.ipynb); [ExpressionFactorGraph.ipynb](../gtsam/nonlinear/doc/ExpressionFactorGraph.ipynb); 1 other source references |
| [generating/](generating/README.md) | Indexes this maintained subfolder. | None | Developers |
| [gt-favicon.svg](gt-favicon.svg) | Retains the gt favicon illustration or document. | None | [myst.yml](../myst.yml) |
| [gtsam-coordinate-frames.lyx](gtsam-coordinate-frames.lyx) | Retains the gtsam coordinate frames LyX document source. | LyX | None |
| [gtsam-coordinate-frames.pdf](gtsam-coordinate-frames.pdf) | Retains the gtsam coordinate frames illustration or document. | None | None |
| [gtsam-site.css](gtsam-site.css) | Defines documentation presentation styles. | None | [myst.yml](../myst.yml) |
| [gtsam.bib](gtsam.bib) | Retains bibliographic records for the documentation. | None | None |
| [gtsam.lyx](gtsam.lyx) | Retains the gtsam LyX document source. | LyX | None |
| [gtsam.pdf](gtsam.pdf) | Retains the gtsam illustration or document. | None | None |
| [images/](images/README.md) | Indexes this maintained subfolder. | None | Developers |
| [macros.lyx](macros.lyx) | Retains the macros LyX document source. | LyX | [ImuFactor.lyx](ImuFactor.lyx); [LieGroups.lyx](LieGroups.lyx) |
| [math.lyx](math.lyx) | Retains the math LyX document source. | LyX | [EssentialMatrix.cpp](../gtsam/geometry/EssentialMatrix.cpp); [Pose2.cpp](../gtsam/geometry/Pose2.cpp); [Rot2.cpp](../gtsam/geometry/Rot2.cpp); 3 other source references |
| [math.pdf](math.pdf) | Retains the math illustration or document. | None | [expressions.md](expressions.md); [gtsam.lyx](gtsam.lyx); [Lie.h](../gtsam/base/Lie.h); 1 other source references |
| [refs.bib](refs.bib) | Retains bibliographic records for the documentation. | None | None |
| [robust.pdf](robust.pdf) | Retains the robust illustration or document. | None | None |
| [stats.html](stats.html) | Retains the stats source or configuration file. | None | None |
| [trustregion.bib](trustregion.bib) | Retains bibliographic records for the documentation. | None | None |
| [trustregion.lyx](trustregion.lyx) | Retains the trustregion LyX document source. | LyX | [DoglegOptimizerImpl.cpp](../gtsam/nonlinear/DoglegOptimizerImpl.cpp) |
| [trustregion.pdf](trustregion.pdf) | Retains the trustregion illustration or document. | None | [DoglegOptimizerImpl.cpp](../gtsam/nonlinear/DoglegOptimizerImpl.cpp); [DoglegOptimizerImpl.h](../gtsam/nonlinear/DoglegOptimizerImpl.h) |
| [user_guide.md](user_guide.md) | Documents User Guide. | None | [myst.yml](../myst.yml) |
| [workflows.md](workflows.md) | Documents GTSAM GitHub Configuration. | None | [README.md](../README.md) |

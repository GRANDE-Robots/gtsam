# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [__init__.py](__init__.py) | Defines the Python package's import surface. | Python standard library; `gtsam` | None |
| [circlePose3.py](circlePose3.py) | Provides the circle Pose3 Python module. | `gtsam`; `numpy` | None |
| [generate_trajectory.py](generate_trajectory.py) | Generates a CSV file with ground-truth trajectory data for testing a DiscreteScenario in GTSAM. | Python standard library; `gtsam`; `numpy` | None |
| [logging_optimizer.py](logging_optimizer.py) | Optimization with logging via a hook. | Python standard library; `gtsam` | None |
| [numerical_derivative.py](numerical_derivative.py) | Numerical derivative functions. | Python standard library; `numpy` | [numericalDerivative.m](../../../matlab/%2Bgtsam/numericalDerivative.m) |
| [plot.py](plot.py) | Various plotting utlities. | Python standard library; `gtsam`; `matplotlib`; `mpl_toolkits`; 1 other declared imports/includes | [ellipses.ipynb](../notebooks/ellipses.ipynb) |
| [test_case.py](test_case.py) | TestCase class with GTSAM assert utils. | Python standard library; `numpy` | None |
| [visual_data_generator.py](visual_data_generator.py) | Provides the visual data generator Python module. | Python standard library; `gtsam`; `numpy` | None |
| [visual_isam.py](visual_isam.py) | Provides the visual isam Python module. | `gtsam` | None |

# File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [Containerfile](Containerfile) | Defines the container image build recipe. | None | None |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [bootstrap.sh](bootstrap.sh) | Runs the bootstrap shell workflow. | Shell and declared executables | [cibw_before_all.sh](../../.github/scripts/python_wheels/cibw_before_all.sh); [containers/gtsam-vnc/Containerfile](Containerfile) |
| [compose.yaml](compose.yaml) | Declares compose parameter or configuration values. | None | None |
| [hub_push.sh](hub_push.sh) | Runs the hub push shell workflow. | Shell and declared executables | None |

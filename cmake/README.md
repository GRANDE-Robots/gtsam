# GTSAMCMakeTools

This is the collection of GTSAM CMake tools that may be useful in external projects.  The way to use this collection is by first making a find_package call:

    find_package(GTSAMCMakeTools)

which will add a directory containing the GTSAM CMake tools to the CMAKE_MODULE_PATH variable.  After that, you may include the files you would like to use.  These files and the functions they define are explained below.

## GtsamBuildTypes

    include(GtsamBuildTypes)

Including this file immediately sets up the following build types and a drop-down list in cmake-gui:

*   `Debug`
*   `Release`
*   `RelWithDebInfo`
*   `Profiling`: All optimizations enabled and minimal debug symbols
*   `Timing`: Defines the symbol GTSAM_ENABLE_TIMING for using GTSAM timing instrumentation

It also configures several minor details, as follows:

*   The compile flag `-ftemplate-depth=1024` is set for newer versions of Clang to handle complex templates.
*   On Windows, executable and dll output paths are set to `${CMAKE_BINARY_DIR}/bin` and import library output to `${CMAKE_BINARY_DIR}/lib`.

It defines the following functions:

*   `gtsam_assign_source_folders( [files] )` Organizes files in the IDE into folders to reflect the actual directory structure of those files.  Folders will be determined relative to the current source folder when this function is called.
*   `gtsam_assign_all_source_folders()` Calls `gtsam_assign_source_folders` on all cpp, c, and h files recursively in the current source folder.

## GtsamTesting

    include(GtsamTesting)

Defines two useful functions for creating CTest unit tests.  Also immediately creates a `check` target that builds and runs all unit tests.

*   `gtsamAddTestsGlob(groupName globPatterns excludedFiles linkLibraries)` Add a group of unit tests.  A list of unit test .cpp files or glob patterns specifies the tests to create.  Tests are assigned into a group name so they can easily by run independently with a make target.  Running 'make check' builds and runs all tests.

    Usage example:
    
        gtsamAddTestsGlob(basic "test*.cpp" "testBroken.cpp" "gtsam;GeographicLib")

    Arguments:
    
        groupName:     A name that will allow this group of tests to be run independently, e.g.
                       'basic' causes a 'check.basic' target to be created to run this test
                       group.
        globPatterns:  The list of files or glob patterns from which to create unit tests, with
                       one test created for each cpp file.  e.g. "test*.cpp", or
                       "testA*.cpp;testB*.cpp;testOneThing.cpp".
        excludedFiles: A list of files or globs to exclude, e.g. "testC*.cpp;testBroken.cpp".
                       Pass an empty string "" if nothing needs to be excluded.
        linkLibraries: The list of libraries to link to in addition to CppUnitLite.
        
*   `gtsamAddExamplesGlob(globPatterns excludedFiles linkLibraries buildWithAll)` Add scripts that will serve as examples of how to use the library.  A list of files or glob patterns is specified, and one executable will be created for each matching .cpp file.  These executables will not be installed.  They are build with 'make all' if GTSAM_BUILD_EXAMPLES_ALWAYS is enabled.  They may also be built with 'make examples'.

    Usage example:

        gtsamAddExamplesGlob("*.cpp" "BrokenExample.cpp" "gtsam;GeographicLib" ON)

    Arguments:

        globPatterns:  The list of files or glob patterns from which to create unit tests, with
                       one test created for each cpp file.  e.g. "*.cpp", or
                       "A*.cpp;B*.cpp;MyExample.cpp".
        excludedFiles: A list of files or globs to exclude, e.g. "C*.cpp;BrokenExample.cpp".  Pass
                       an empty string "" if nothing needs to be excluded.
        linkLibraries: The list of libraries to link to.
        buildWithAll: Build examples with `make` and/or `make all`

## GtsamMakeConfigFile

    include(GtsamMakeConfigFile)
     
Defines a function for generating a config file so your project may be found with the CMake `find_package` function.  TODO: Write documentation.

## File Structure

| File | Relevance | Dependencies | Used by |
| --- | --- | --- | --- |
| [CMakeLists.txt](CMakeLists.txt) | Configures this folder's build, installation or validation targets. | CMake | None |
| [Config.cmake.in](Config.cmake.in) | Templates the generated Config.cmake configuration. | None | [cmake/CMakeLists.txt](CMakeLists.txt); [GtsamMakeConfigFile.cmake](GtsamMakeConfigFile.cmake); [HandleCuda.cmake](HandleCuda.cmake); 1 other source references |
| [FindGooglePerfTools.cmake](FindGooglePerfTools.cmake) | Defines Find Google Perf Tools CMake configuration. | CMake | None |
| [FindMKL.cmake](FindMKL.cmake) | Defines Find MKL CMake configuration. | CMake | None |
| [FindMOSEK.cmake](FindMOSEK.cmake) | Defines Find MOSEK CMake configuration. | CMake | None |
| [FindNumPy.cmake](FindNumPy.cmake) | Defines Find Num Py CMake configuration. | CMake | [cmake/CMakeLists.txt](CMakeLists.txt) |
| [GTSAMCMakeToolsConfig.cmake](GTSAMCMakeToolsConfig.cmake) | Defines GTSAMCMake Tools Config CMake configuration. | CMake | [cmake/CMakeLists.txt](CMakeLists.txt) |
| [GtsamBuildTypes.cmake](GtsamBuildTypes.cmake) | Defines Gtsam Build Types CMake configuration. | CMake | [cmake/CMakeLists.txt](CMakeLists.txt) |
| [GtsamMakeConfigFile.cmake](GtsamMakeConfigFile.cmake) | Defines Gtsam Make Config File CMake configuration. | CMake | [cmake/CMakeLists.txt](CMakeLists.txt) |
| [GtsamPrinting.cmake](GtsamPrinting.cmake) | Defines Gtsam Printing CMake configuration. | CMake | [cmake/CMakeLists.txt](CMakeLists.txt) |
| [GtsamTesting.cmake](GtsamTesting.cmake) | Defines Gtsam Testing CMake configuration. | CMake | [cmake/CMakeLists.txt](CMakeLists.txt); [GtsamTestingObsolete.cmake](obsolete/GtsamTestingObsolete.cmake) |
| [HandleAllocators.cmake](HandleAllocators.cmake) | Defines Handle Allocators CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt) |
| [HandleBoost.cmake](HandleBoost.cmake) | Defines Handle Boost CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt); [README.md](../README.md) |
| [HandleCCache.cmake](HandleCCache.cmake) | Defines Handle CCache CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt) |
| [HandleCPack.cmake](HandleCPack.cmake) | Defines Handle CPack CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt) |
| [HandleCephes.cmake](HandleCephes.cmake) | Defines Handle Cephes CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt) |
| [HandleCuda.cmake](HandleCuda.cmake) | Defines Handle Cuda CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt); [gtsam/base/cuda/Errors.h](../gtsam/base/cuda/Errors.h) |
| [HandleEigen.cmake](HandleEigen.cmake) | Defines Handle Eigen CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt) |
| [HandleFinalChecks.cmake](HandleFinalChecks.cmake) | Defines Handle Final Checks CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt) |
| [HandleGeneralOptions.cmake](HandleGeneralOptions.cmake) | Defines Handle General Options CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt) |
| [HandleGeographicLib.cmake](HandleGeographicLib.cmake) | Defines Handle Geographic Lib CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt) |
| [HandleGlobalBuildFlags.cmake](HandleGlobalBuildFlags.cmake) | Defines Handle Global Build Flags CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt) |
| [HandleMKL.cmake](HandleMKL.cmake) | Defines Handle MKL CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt) |
| [HandleMOSEK.cmake](HandleMOSEK.cmake) | Defines Handle MOSEK CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt) |
| [HandleMetis.cmake](HandleMetis.cmake) | Defines Handle Metis CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt); [gtsam/3rdparty/CMakeLists.txt](../gtsam/3rdparty/CMakeLists.txt) |
| [HandleOpenMP.cmake](HandleOpenMP.cmake) | Defines Handle Open MP CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt) |
| [HandlePerfTools.cmake](HandlePerfTools.cmake) | Defines Handle Perf Tools CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt) |
| [HandlePrintConfiguration.cmake](HandlePrintConfiguration.cmake) | Defines Handle Print Configuration CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt) |
| [HandlePython.cmake](HandlePython.cmake) | Defines Handle Python CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt) |
| [HandleSpectra.cmake](HandleSpectra.cmake) | Defines Handle Spectra CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt) |
| [HandleSuiteSparse.cmake](HandleSuiteSparse.cmake) | Defines Handle Suite Sparse CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt) |
| [HandleTBB.cmake](HandleTBB.cmake) | Defines Handle TBB CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt) |
| [HandleUninstall.cmake](HandleUninstall.cmake) | Defines Handle Uninstall CMake configuration. | CMake | [CMakeLists.txt](../CMakeLists.txt) |
| [README.html](README.html) | Retains the README source or configuration file. | None | [cmake/CMakeLists.txt](CMakeLists.txt) |
| [README.md](README.md) | Indexes this folder and its maintained subfolders. | None | Developers |
| [cmake_uninstall.cmake.in](cmake_uninstall.cmake.in) | Templates the generated cmake_uninstall.cmake configuration. | None | None |
| [dllexport.h.in](dllexport.h.in) | Templates the generated dllexport.h configuration. | None | [cmake/CMakeLists.txt](CMakeLists.txt); [gtsam/CMakeLists.txt](../gtsam/CMakeLists.txt); [gtsam_unstable/CMakeLists.txt](../gtsam_unstable/CMakeLists.txt) |
| [example_cmake_find_gtsam/](example_cmake_find_gtsam/README.md) | Indexes this maintained subfolder. | None | Developers |
| [obsolete/](obsolete/README.md) | Indexes this maintained subfolder. | None | Developers |

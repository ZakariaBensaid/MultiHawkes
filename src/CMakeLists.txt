cmake_minimum_required(VERSION 3.8)
project(hawkes LANGUAGES CXX)

# Use a modern C++ standard (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------------------------
# FIND Python and pybind11
# ------------------------------------------------------------------------------

## Example of my paths to the Python interpreter : 

#set(Python3_ROOT_DIR "C:/Users/zbensaid/AppData/Local/anaconda3/envs/pyZak") (without #)
#set(Python3_EXECUTABLE "C:/Users/zbensaid/AppData/Local/anaconda3/envs/pyZak/python.exe") (without #)
#set(pybind11_DIR "C:/vcpkg/packages/pybind11_x64-windows/share/pybind11") (without #)
 
## How to proceed :

# You can use the Anaconda environment (e.g., conda activate) or
# directly pass -DPython3_ROOT_DIR=... on the command line.
find_package(Python3 COMPONENTS Interpreter Development.Module REQUIRED)

# you can also look for a system-wide installation of pybind11, or
# optionally specify pybind11_DIR at configure time.
find_package(pybind11 CONFIG REQUIRED)

# ------------------------------------------------------------------------------
# BUILD the Extension Module
# ------------------------------------------------------------------------------
# We'll create a Python extension module named "hawkes" from hawkes.cpp
add_library(hawkes MODULE hawkes.cpp)

# Link Python and pybind11
target_link_libraries(hawkes PRIVATE
    Python3::Module
    pybind11::module
)

# Make sure CMake knows where to find the Python headers and pybind11 headers
target_include_directories(hawkes PRIVATE
    ${Python3_INCLUDE_DIRS}
    ${pybind11_INCLUDE_DIRS}
)

# On CMake >= 3.12, set the typical naming scheme for Python modules
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.12")
    set_target_properties(hawkes PROPERTIES
        PREFIX "${PYTHON_MODULE_PREFIX}"
        SUFFIX "${PYTHON_MODULE_EXTENSION}"
    )
endif()

# ------------------------------------------------------------------------------
# PRINT some helpful info for debugging
# ------------------------------------------------------------------------------
message(STATUS "Python3_FOUND: ${Python3_FOUND}")
message(STATUS "Python3_EXECUTABLE: ${Python3_EXECUTABLE}")
message(STATUS "Python3_INCLUDE_DIRS: ${Python3_INCLUDE_DIRS}")
message(STATUS "Python3_Development.Module_FOUND: ${Python3_Development_Module_FOUND}")
message(STATUS "pybind11_DIR: ${pybind11_DIR}")
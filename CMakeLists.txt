cmake_minimum_required(VERSION 3.12)
project(hawkes LANGUAGES CXX)

# Use a modern C++ standard (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------------------------
# FIND Python and pybind11
# ------------------------------------------------------------------------------

# You can use the Anaconda environment (e.g., conda activate) or
# directly pass -DPython3_ROOT_DIR=... on the command line.
find_package(Python3 COMPONENTS Interpreter Development.Module REQUIRED)

# you can also look for a system-wide installation of pybind11, or
# optionally specify pybind11_DIR at configure time.
find_package(pybind11 CONFIG REQUIRED)

# ------------------------------------------------------------------------------
# Include Directories
# ------------------------------------------------------------------------------

# Include directories for the core library
include_directories(${Python3_INCLUDE_DIRS})
include_directories(${pybind11_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)  

# ------------------------------------------------------------------------------
# BUILD the Extension Module
# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------
# Add Library for Core Functions
# ------------------------------------------------------------------------------

# Create a library from hawkes.cpp which contains simulate_hawkes
add_library(hawkes_core STATIC src/hawkes.cpp)
set_target_properties(hawkes_core PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(hawkes_core PUBLIC include)

# We'll create a Python extension module named "hawkes" from hawkes_module.cpp
add_library(hawkes MODULE module/hawkes_module.cpp)

# Link Python and pybind11
target_link_libraries(hawkes PRIVATE
    hawkes_core
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
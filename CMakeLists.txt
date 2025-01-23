cmake_minimum_required(VERSION 3.8)

project(hawkes)

# Set the path to your Conda Python
set(Python3_ROOT_DIR "C:/Users/zbensaid/AppData/Local/anaconda3/envs/pyZak")
set(Python3_EXECUTABLE "C:/Users/zbensaid/AppData/Local/anaconda3/envs/pyZak/python.exe")

# Include Pybind11
set(pybind11_DIR "C:/vcpkg/packages/pybind11_x64-windows/share/pybind11")

find_package(Python3 COMPONENTS Interpreter Development.Module REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

include_directories(${Python3_INCLUDE_DIRS})
include_directories(${pybind11_INCLUDE_DIR})

# Create a library instead of an executable
add_library(hawkes MODULE "hawkes.cpp")

target_include_directories(hawkes PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(hawkes PRIVATE Python3::Module pybind11::module)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_target_properties(hawkes PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}" SUFFIX "${PYTHON_MODULE_EXTENSION}")
endif()

# Debugging output
message(STATUS "Python3_FOUND: ${Python3_FOUND}")
message(STATUS "Python3_Interpreter_FOUND: ${Python3_Interpreter_FOUND}")
message(STATUS "Python3_EXECUTABLE: ${Python3_EXECUTABLE}")
message(STATUS "Python3_INCLUDE_DIRS: ${Python3_INCLUDE_DIRS}")
message(STATUS "Python3_Development.Module_FOUND: ${Python3_Development_Module_FOUND}")
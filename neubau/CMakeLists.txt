cmake_minimum_required(VERSION 2.6)

project(NEUBAU)  # makes this the source directory.

# ENABLE_TESTING() enables the use of CTest for unit tests.
# In particuar, we use it for the 'test' subdirectory only.
enable_testing()

# Includes the source directory as a include directory.
# By including the the source root as a path, this means that
# the #include directive can use the angled bracket notation
# to find header files. A subdirectory must be provided.
# e.g.
#
# #include <core/vector2d.h> // valid - CMake finds this include from ANYWHERE
# #include <vector2d.h>      // invalid - CMake fails to find the include at all
include_directories(${NEUBAU_SOURCE_DIR})


# Library directories is the binary with specified subdirectories.
link_directories(${NEUBAU_BINARY_DIR}/core
				${NEUBAU_BINARY_DIR}/control
				${NEUBAU_BINARY_DIR}/device
				${NEUBAU_BINARY_DIR}/electronic
				${NEUBAU_BINARY_DIR}/experimental/virtual)

add_subdirectory(control)
add_subdirectory(core)
add_subdirectory(device)
add_subdirectory(electronic)
add_subdirectory(experimental)
add_subdirectory(test)

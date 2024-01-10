cmake_minimum_required(VERSION 3.22)

# Top level CMake script for building RENE.
# Author: Igor Lesik 2024

project(RENE
    VERSION 0.1.0
    DESCRIPTION "Linear Algebra library"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Werror -march=native")

include_directories(./)

# Install inside the build directory.
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

include(kokkos_mdspan.cmake)

enable_testing()

add_subdirectory(test)

message(STATUS "C++ compiler:" ${CMAKE_CXX_COMPILER})

include(cmake/library.cmake)
include(cmake/test.cmake)

cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

project(physics_engine VERSION 0.1.1 LANGUAGES CXX)

set(MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MAIN_PROJECT ON)
endif()

option(BUILD_TESTING "Build tests" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

build_physics_engine()

if(BUILD_TESTING AND ${MAIN_PROJECT})
    build_test()
endif()

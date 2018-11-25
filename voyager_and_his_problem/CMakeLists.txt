cmake_minimum_required(VERSION 3.12)
project(voyager_and_his_problem)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(cmake-build-debug)

add_executable(voyager_and_his_problem
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/Makefile
        cmake-build-debug/untitled
        cmake-build-debug/untitled.cbp
        CMakeLists.txt
        functions.h
        main.cpp)

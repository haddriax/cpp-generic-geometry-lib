cmake_minimum_required(VERSION 3.26)
project(maths_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(maths_cpp main.cpp source/Vector.h source/Vector.cpp
        source/Matrix.h
        source/Matrix.cpp)

cmake_minimum_required(VERSION 3.3)
project(cpp_r_type)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        i2Vector.cpp
        i2Vector.hpp f2Vector.cpp f2Vector.hpp BaseVector.hpp t2Vector.cpp t2Vector.hpp)

add_executable(cpp_r_type ${SOURCE_FILES})
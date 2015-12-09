cmake_minimum_required(VERSION 3.3)
project(cpp_r_type)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(SFML 2 REQUIRED system window graphics network audio)
set(SOURCE_FILES test.cpp t2Vector.hpp QuadTree.cpp QuadTree.hpp Geometry.cpp Geometry.hpp Rectangle.cpp Rectangle.hpp World.cpp World.hpp)

add_executable(cpp_r-type ${SOURCE_FILES})
target_link_libraries(cpp_r-type ${SFML_LIBRARIES})
cmake_minimum_required(VERSION 3.3)
project(SFML)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}
-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGLEW")
set(SOURCE_FILES main.cpp InfoMenu.cpp InfoMenu.h)
add_executable(SFML ${SOURCE_FILES})
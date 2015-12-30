cmake_minimum_required(VERSION 3.3)
project(cpp_r_typecpy2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        Source/GameEngine/GameData.cpp
        Source/GameEngine/GameData.h
        Source/GameEngine/Geometry.cpp
        Source/GameEngine/Geometry.hpp
        Source/GameEngine/IGameplay.h
        Source/GameEngine/Level.cpp
        Source/GameEngine/Level.h
        Source/GameEngine/Object.cpp
        Source/GameEngine/Object.h
        Source/GameEngine/OnLevel.cpp
        Source/GameEngine/OnLevel.h
        Source/GameEngine/QuadTree.cpp
        Source/GameEngine/QuadTree.hpp
        Source/GameEngine/Rectangle.hpp
        Source/GameEngine/t2Vector.hpp
        Source/GameEngine/Timer.cpp
        Source/GameEngine/Timer.hpp
        Source/GameEngine/World.cpp
        Source/GameEngine/World.hpp
        Source/GameEngine/RTypeServer.cpp
        Source/GameEngine/RTypeServer.hpp
        Source/GameEngine/User.cpp
        Source/GameEngine/User.hpp
        Source/GameEngine/GameRoom.cpp
        Source/GameEngine/GameRoom.hpp
        Source/GameEngine/IMutex.hpp
        Source/GameEngine/MutexVault.cpp
        Source/GameEngine/MutexVault.hpp
        Source/GameEngine/ISocket.cpp
        Source/GameEngine/ISocket.h
        Source/GameEngine/LinuxSocket.cpp
        Source/GameEngine/LinuxSocket.h
        Source/GameEngine/LinuxMutex.hpp
        Source/test.cpp Source/GameEngine/Instruction.cpp Source/GameEngine/Instruction.h)

add_executable(cpp_r_typecpy2 ${SOURCE_FILES})
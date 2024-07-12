cmake_minimum_required(VERSION 3.26)
project(Q_Learning)

set(CMAKE_CXX_STANDARD 17)

add_executable(Q_Learning
        src/main.cpp
        src/testing.cpp
        src/testing.h
        src/game.cpp
        src/game.h
        src/training.cpp
        src/training.h
        src/agent.cpp
        src/agent.h)

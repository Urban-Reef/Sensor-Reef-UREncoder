cmake_minimum_required(VERSION 3.26)
project(UREncoder)

set(CMAKE_CXX_STANDARD 17)

add_executable(CustomEncoder main.cpp
        src/UREncoder.h
        src/UREncoder.cpp)

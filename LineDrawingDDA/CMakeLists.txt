cmake_minimum_required(VERSION 3.27)
project(LineDrawingDDA)

set(CMAKE_CXX_STANDARD 17)

add_executable(LineDrawingDDA main.cpp
        ../Graphics/LineDrawingBresenham/main.cpp)

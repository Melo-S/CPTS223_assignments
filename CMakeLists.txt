cmake_minimum_required(VERSION 3.16)
project(CPTS_223_MA4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
set(CMAKE_BUILD_TYPE Debug)

add_executable(MA4 main.cpp)
cmake_minimum_required(VERSION 3.16)
project(MA1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_BUILD_TYPE Debug)

add_executable(MA1 main.cpp  testQueue.cpp queue.h queue.cpp)
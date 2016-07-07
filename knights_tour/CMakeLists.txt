cmake_minimum_required(VERSION 3.2.2)
project(knights_tour)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp KnightsTour.cpp KnightsTour.h Test.cpp Test.h)
add_executable(knights_tour ${SOURCE_FILES})
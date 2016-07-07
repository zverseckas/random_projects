cmake_minimum_required(VERSION 3.3)
project(kinhgts_tour_warnsdorf)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp KnightsTour.cpp KnightsTour.h)
add_executable(kinhgts_tour_warnsdorf ${SOURCE_FILES})
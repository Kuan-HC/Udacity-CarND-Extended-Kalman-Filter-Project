project(ExtendedKF)

cmake_minimum_required(VERSION 3.5)

add_definitions(-std=c++11)

set(CMAKE_BUILD_TYPE Debug)

set(sources src/main.cpp src/tools.cpp src/FusionEKF.cpp src/kalman_filter.cpp src/tools.h src/FusionEKF.h src/kalman_filter.h)

add_executable(ExtendedKF ${sources})



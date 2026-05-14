cmake_minimum_required(VERSION 3.28)
project(lab1_linal)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes)

add_executable(lab1_linal
        includes/experiments.h
        includes/gaussian.h
        includes/matrix_util.h
        includes/timer.h
        includes/types.h
        src/experiments.cpp
        src/gaussian.cpp
        src/lu.cpp
        src/matrix_util.cpp
        src/timer.cpp
        main.cpp
        includes/lu.h)

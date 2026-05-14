cmake_minimum_required(VERSION 3.15)
project(lab1_linal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_executable(lab1_linal
        main.cpp
        src/matrix_util.cpp
        src/gaussian.cpp
        src/lu.cpp
        src/timer.cpp
        src/experiments.cpp
)

target_include_directories(lab1_linal PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)
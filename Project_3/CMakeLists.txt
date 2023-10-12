cmake_minimum_required(VERSION 3.24)
project(Project_3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static")

add_executable(Project_3 driver-proj3.cpp
        bst-student-proj3.h bst-prof-proj3.h)

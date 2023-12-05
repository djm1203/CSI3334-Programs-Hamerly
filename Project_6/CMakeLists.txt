cmake_minimum_required(VERSION 3.24)
project(Project_6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static")

add_executable(Project_6 driver-proj6.cpp graph-proj6.h
        graph-proj6.cpp
        arrayheap-prof-proj6.h
        arrayheap-student-proj6.h)

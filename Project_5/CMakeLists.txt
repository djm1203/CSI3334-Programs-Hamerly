cmake_minimum_required(VERSION 3.24)
project(Project_5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static")

add_executable(Project_5 driver-proj5.cpp arrayheap-prof-proj5.h arrayheap-student-proj5.h process-proj5.h process-proj5.cpp)

cmake_minimum_required(VERSION 3.26)
project(SET_3)

set(CMAKE_CXX_STANDARD 23)

add_executable(a1 a1.cpp
        src/sort_tester.cpp
)

add_executable(a23 a23.cpp
        src/array_generator.cpp
        src/sort_tester.cpp
        src/sorter.cpp)

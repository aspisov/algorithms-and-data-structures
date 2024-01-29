cmake_minimum_required(VERSION 3.26)
project(algorithms_and_data_structures)

set(CMAKE_CXX_STANDARD 23)

add_executable(algorithms_and_data_structures main.cpp
        s2/HashLPTable.cpp
        s2/HashLPTable.h
        s2/HashCuckooTable.cpp
        s2/HashCuckooTable.h)

cmake_minimum_required(VERSION 3.26)
project(Test)

set(CMAKE_CXX_STANDARD 17)

add_executable(Test main.cpp
        muchie.cpp
        muchie.h
        nod.cpp
        nod.h)

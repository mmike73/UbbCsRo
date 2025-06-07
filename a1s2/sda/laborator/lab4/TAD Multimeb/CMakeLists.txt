cmake_minimum_required(VERSION 3.26)
project(TAD_Multimeb)

set(CMAKE_CXX_STANDARD 20)

add_executable(TAD_Multimeb App.cpp
        Multime.h
        Multime.cpp
        IteratorMultime.cpp
        Teste/TestExtins.h
        Teste/TestExtins.cpp
        Teste/TestScurt.h
        Teste/TestScurt.cpp)

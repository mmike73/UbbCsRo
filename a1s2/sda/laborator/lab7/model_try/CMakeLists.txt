cmake_minimum_required(VERSION 3.26)
project(model)

set(CMAKE_CXX_STANDARD 17)

add_executable(model App.cpp
        Colectie.h
        IteratorColectie.h
        TestExtins.h
        TestScurt.h
        Colectie.cpp
        IteratorColectie.cpp
        TestExtins.cpp
        TestScurt.cpp)

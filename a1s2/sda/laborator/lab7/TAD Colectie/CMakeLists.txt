cmake_minimum_required(VERSION 3.26)
project(TAD_Colectie)

set(CMAKE_CXX_STANDARD 17)

add_executable(TAD_Colectie Colectie/App.cpp
        Colectie/App.cpp
        Colectie/Colectie.cpp
        Colectie/Colectie.h
        Colectie/IteratorColectie.h
        Colectie/IteratorColectie.cpp
        Teste/TestExtins.h
        Teste/TestExtins.cpp
        Teste/TestScurt.h
        Teste/TestScurt.cpp)

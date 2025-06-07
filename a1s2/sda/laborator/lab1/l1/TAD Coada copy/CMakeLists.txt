cmake_minimum_required(VERSION 3.26)
project(TAD_Coada)

set(CMAKE_CXX_STANDARD 14)

include_directories("Proiect C++")
include_directories(Teste)

add_executable(TAD_Coada
        "Proiect C++/App.cpp"
        "Proiect C++/Coada.cpp"
        "Proiect C++/Coada.h"
        Teste/TestExtins.cpp
        Teste/TestExtins.h
        Teste/TestScurt.cpp
        Teste/TestScurt.h)

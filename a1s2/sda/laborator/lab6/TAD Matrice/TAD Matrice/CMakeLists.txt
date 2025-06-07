cmake_minimum_required(VERSION 3.26)
project(TAD_Matrice)

set(CMAKE_CXX_STANDARD 20)

add_executable(TAD_Matrice "Proiect C++/App.cpp"
        "Proiect C++/Matrice.h"
        Teste/TestExtins.h
        Teste/TestScurt.h
        "Proiect C++/Matrice.cpp"
        Teste/TestScurt.cpp
        Teste/TestExtins.cpp)

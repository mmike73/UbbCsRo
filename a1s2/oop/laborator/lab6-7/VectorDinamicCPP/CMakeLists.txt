cmake_minimum_required(VERSION 3.26)
project(VectorDinamicCPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(VectorDinamicCPP
        VectorDinamicCPP/main.cpp
        VectorDinamicCPP/Pet.cpp
        VectorDinamicCPP/VectDinNewDelete.cpp
        VectorDinamicCPP/VectDinSmartPointer.cpp)

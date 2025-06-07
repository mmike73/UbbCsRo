cmake_minimum_required(VERSION 3.26)
project(VD)

set(CMAKE_CXX_STANDARD 14)

add_executable(VD main.cpp
        Pet.cpp
        Pet.h
        VectDinNewDelete.cpp
        VectDinNewDelete.h
        VectDinSmartPointer.cpp
        VectDinSmartPointer.h
        VectorDinamicTemplate.h)

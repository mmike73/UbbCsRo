cmake_minimum_required(VERSION 3.26)
project(vector_template)

set(CMAKE_CXX_STANDARD 20)

add_executable(vector_template main.cpp
        vector_template.h
        domain.cpp
)

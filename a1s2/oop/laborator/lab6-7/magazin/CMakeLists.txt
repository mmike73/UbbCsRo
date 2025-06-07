cmake_minimum_required(VERSION 3.26)
project(lab6_7)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab6_7 main.cpp
        ui.cpp
        ui.h
        domain.cpp
        domain.h
        repo.cpp
        repo.h
        service.cpp
        service.h
        validation.cpp
        validation.h
        tests.cpp
        tests.h
        comparatori.cpp
        comparatori.h
        vector_template.h
        exception.h
)

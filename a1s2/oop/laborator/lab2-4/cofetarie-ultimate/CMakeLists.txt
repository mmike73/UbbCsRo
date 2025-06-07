cmake_minimum_required(VERSION 3.26)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled main.c
        domain.c
        repo.c
        service.c
        tests.c
        ui.c
        validation.c
        vector_dinamic.c
        vector_dinamic.h)

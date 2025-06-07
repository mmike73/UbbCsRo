cmake_minimum_required(VERSION 3.26.4)
project(OOP_lab2_4)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(OOP_lab2_4 ui.c
        medicament.h
        medicament.c
        myList.h
        myList.c
        service.h
        service.c
        teste.c
        ui.h
        teste.h)

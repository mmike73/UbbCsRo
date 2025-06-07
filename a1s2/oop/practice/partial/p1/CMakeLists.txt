cmake_minimum_required(VERSION 3.26)
project(p1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/mihaimoldovan/Qt/6.7.0/macos/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Widgets
        REQUIRED)

add_executable(p1 main.cpp
        gui.cpp
        gui.h
        repo.h
        domain_procesor.cpp
        domain_procesor.h
        domain_placa.cpp
        domain_placa.h
        service.cpp
        service.h
        exception.cpp
        exception.h
        validator.cpp
        validator.h
        tests.cpp
        tests.h
        repo_procesoare.cpp
        repo_procesoare.h
        repo_placi.cpp
        repo_placi.h)
target_link_libraries(p1
        Qt::Core
        Qt::Widgets
)


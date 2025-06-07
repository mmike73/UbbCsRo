cmake_minimum_required(VERSION 3.26)
project(untitled)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/mihaimoldovan/Qt/6.7.0/macos/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Widgets
        REQUIRED)

add_executable(untitled main.cpp
        gui.cpp
        gui.h
        repo.cpp
        repo.h
        domain.cpp
        domain.h
        service.cpp
        service.h
        teste.cpp
        teste.h
)
target_link_libraries(untitled
        Qt::Core
        Qt::Widgets
)


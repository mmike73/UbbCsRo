cmake_minimum_required(VERSION 3.26)
project(p3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/mihaimoldovan/Qt/6.7.0/macos")

find_package(Qt6 COMPONENTS
        Core
        Widgets
        REQUIRED)

add_executable(p3 main.cpp
        gui.cpp
        gui.h
        test.cpp
        test.h
        file_repo.cpp
        file_repo.h
        service.cpp
        service.h
        domain.cpp
        domain.h
        exception.cpp
        exception.h)
target_link_libraries(p3
        Qt::Core
        Qt::Widgets
)


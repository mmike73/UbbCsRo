cmake_minimum_required(VERSION 3.26)
project(project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/mihaimoldovan/Qt/6.7.0/macos/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Widgets
        REQUIRED)

add_executable(project main.cpp
        test.cpp
        test.h
        domain.cpp
        domain.h
        repo.cpp
        repo.h
        service.cpp
        service.h
        gui.cpp
        gui.h
        valid.cpp
        valid.h
        exception.cpp
        exception.h
        observer.cpp
        observer.h
        my_model.cpp
        my_model.h)
target_link_libraries(project
        Qt::Core
        Qt::Widgets
)


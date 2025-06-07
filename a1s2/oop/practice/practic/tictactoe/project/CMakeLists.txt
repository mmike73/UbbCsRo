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
        domain.cpp
        domain.h
        repo.cpp
        repo.h
        service.cpp
        service.h
        test.cpp
        test.h
        observer.cpp
        observer.h
        exception.cpp
        exception.h)
target_link_libraries(project
        Qt::Core
        Qt::Widgets
)


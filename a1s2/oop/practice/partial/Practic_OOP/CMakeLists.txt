cmake_minimum_required(VERSION 3.26)
project(Practic_OOP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/mihaimoldovan/Qt/6.7.0/macos/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Widgets
        REQUIRED)

add_executable(Practic_OOP main.cpp
        gui.cpp
        gui.h
        service.cpp
        service.h
        repo.cpp
        repo.h
        domain.cpp
        domain.h
        exception.h
        test.cpp
        test.h
        validation.cpp
        validation.h)
target_link_libraries(Practic_OOP
        Qt::Core
        Qt::Widgets
)


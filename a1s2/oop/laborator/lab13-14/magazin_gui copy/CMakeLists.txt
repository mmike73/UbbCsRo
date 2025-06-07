cmake_minimum_required(VERSION 3.26)
project(magazin_gui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/mihaimoldovan/Qt/6.7.0/macos")

find_package(Qt6 COMPONENTS
        Core
        Widgets
        REQUIRED)

add_executable(magazin_gui main.cpp
        actiune_undo.h
        cos_cumparaturi.h
        domain.h
        exception.h
        service.h
        repo.h
        tests.h
        validation.h
        ui.h
        actiune_undo.cpp
        cos_cumparaturi.cpp
        domain.cpp
        repo.cpp
        service.cpp
        tests.cpp
        ui.cpp
        validation.cpp
        gui.cpp
        gui.h
        observer.h
        gui_cos.cpp
        gui_cos.h)
target_link_libraries(magazin_gui
        Qt::Core
        Qt::Widgets
)


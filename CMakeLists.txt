cmake_minimum_required(VERSION 3.22)
project(TerminalToolsetGUI LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets Concurrent REQUIRED)

add_subdirectory(core)
add_subdirectory(ui)

add_executable(Toolset
    main.cpp
    mainwindow.h mainwindow.cpp
)

target_link_libraries(Toolset PRIVATE
    Qt6::Widgets
    Qt6::Concurrent          # <‑‑ add this
    corelib
    uilib
)

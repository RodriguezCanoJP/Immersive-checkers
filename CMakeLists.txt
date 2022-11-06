cmake_minimum_required(VERSION 3.23)
project(proyecto2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/qt@5/5.15.6/lib/cmake/Qt5")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(proyecto2 main.cpp boardsquare.h boardpiece.h checkersgame.h main.h ai.h ai.cpp backdrop.h checkersgame.cpp backtracking.h backtracking.cpp)
target_link_libraries(proyecto2
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )


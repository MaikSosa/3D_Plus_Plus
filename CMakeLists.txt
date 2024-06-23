cmake_minimum_required(VERSION 3.28)
project(module)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake-build-debug/)
set(SDL2_PATH "Z:/Documentos/Homework (do not open)/10th semester/CSE 310/W06/module/SDL2-2.30.4/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories( ${SDL2_INCLUDE_DIR} )

add_executable(module
        main.cpp
        screen.h)

target_link_libraries( ${PROJECT_NAME} ${SDL2_LIBRARY} )

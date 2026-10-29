cmake_minimum_required(VERSION 3.20)

project(MyEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 CONFIG REQUIRED)

add_executable(MyEngine
    src/main.cpp
    src/window.cpp
)

target_link_libraries(MyEngine PRIVATE SDL3::SDL3)
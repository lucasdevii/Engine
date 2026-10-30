cmake_minimum_required(VERSION 3.20)

project(MyEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/vendor/imgui")

find_package(SDL3 CONFIG REQUIRED)

add_executable(MyEngine
    src/main.cpp
    src/window/window.cpp
)

target_link_libraries(MyEngine PRIVATE SDL3::SDL3)

target_sources(MyEngine PRIVATE
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp

    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(MyEngine PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)
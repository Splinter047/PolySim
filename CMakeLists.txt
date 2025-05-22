cmake_minimum_required(VERSION 3.29)
project(PolySim)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG 4.0
)

FetchContent_MakeAvailable(raylib raygui)

add_executable(${PROJECT_NAME} main.cpp)

set(GENERATED_HEADERS_DIR "${CMAKE_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${GENERATED_HEADERS_DIR})

file(COPY "${raygui_SOURCE_DIR}/src/raygui.h" DESTINATION
        "${GENERATED_HEADERS_DIR}")

target_include_directories(${PROJECT_NAME} PRIVATE
        ${GENERATED_HEADERS_DIR}
)

target_link_libraries(${PROJECT_NAME} raylib)
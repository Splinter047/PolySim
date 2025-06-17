cmake_minimum_required(VERSION 3.29) # Will not work on any previous version
project(PolySim) # Define your project name

# 'set(var_name value' is used to create/assign value to variables
set(CMAKE_CXX_STANDARD 20) # Select the C++ Release to use
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Set the selected release as a hard req

# GLFW doesn't play nice with Wayland
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_X11 ON CACHE BOOL "" FORCE)

include(FetchContent) # Library/Feature to download over http

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
) # Define the repo to download

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # Raylib specific settings, ignore
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG 4.0
) # Define the repo to download

FetchContent_MakeAvailable(raylib raygui) # Clone the above defined repos

add_executable(${PROJECT_NAME} src/main.cpp
        include/vector.h
        include/polygon.h
		src/polygon.cpp
        include/transformation.h
		include/pen_tool.h
		src/pen_tool.cpp
		include/scene.h
		src/scene.cpp
		include/state_manager.h
		src/state_manager.cpp
		include/force.h
		src/force.cpp
		include/file_manager.h
		src/file_manager.cpp) # Choose files to compile

# Needed for properly linking raygui
set(GENERATED_HEADERS_DIR "${CMAKE_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${GENERATED_HEADERS_DIR}) # Creates the specified dir

# Self explanatory, just copying the raygui headers
file(COPY "${raygui_SOURCE_DIR}/src/raygui.h" DESTINATION
        "${GENERATED_HEADERS_DIR}")

# Including the copied headers into your project
target_include_directories(${PROJECT_NAME} PRIVATE
        ${GENERATED_HEADERS_DIR}
)

# Similar here
target_link_libraries(${PROJECT_NAME} raylib)

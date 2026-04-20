cmake_minimum_required(VERSION 3.24)

project(FullGame
    VERSION 0.1.0
    DESCRIPTION "Custom 3D engine and multiplayer third-person game"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(FULLGAME_ENABLE_WARNINGS "Enable strict warnings" ON)

find_package(glfw3 3.3 REQUIRED)
find_package(Vulkan REQUIRED)

add_subdirectory(engine)
add_subdirectory(game)

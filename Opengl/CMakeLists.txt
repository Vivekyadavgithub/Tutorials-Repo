cmake_minimum_required(VERSION 3.0...3.25.1 FATAL_ERROR)

project(Opengl-tut LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/vendor)
link_directories(${CMAKE_SOURCE_DIR}/vendor/libs)

add_subdirectory(0.Hello-Window)
add_subdirectory(1.Hello-Triangle)
add_subdirectory(2.Textures)


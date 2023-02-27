cmake_minimum_required(VERSION 3.0...3.25.1 FATAL_ERROR)

project(Opengl-proj-cmake LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(vendor)
link_directories(${CMAKE_SOURCE_DIR}/vendor/Debug_Libs/)

#ind_package(OpenGL REQUIRED)

add_executable(opengl-proj main.cpp 
        ${CMAKE_SOURCE_DIR}/vendor/glad/glad.c)
target_link_libraries(opengl-proj glfw3d)

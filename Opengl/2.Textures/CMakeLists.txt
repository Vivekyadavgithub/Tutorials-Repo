cmake_minimum_required(VERSION 3.0...3.25.1 FATAL_ERROR)

project(Textures LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
add_executable(Textures texture-tut.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/glad/glad.c)

target_link_libraries(Textures glfw3d)
target_include_directories(Textures PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../vendor)
target_link_directories(Textures PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/libs) #for running independently
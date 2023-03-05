cmake_minimum_required(VERSION 3.0...3.25.1 FATAL_ERROR)

project(Hello-Window LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS " include dir: ${CMAKE_CURRENT_SOURCE_DIR}")

find_package(OpenGL REQUIRED)
add_executable(Hello-Window Hello-Window.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/glad/glad.c)
#target_include_directories(Hello-Window PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../vendor)
#target_link_directories(Hello-Window PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/libs)
target_link_libraries(Hello-Window glfw3)

cmake_minimum_required(VERSION 3.0...3.25.1 FATAL_ERROR)

project(Hello-Tirangle LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../vendor)
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../vendor/libs)
#add_library( glfw SHARED IMPORTED )
#set_target_properties( glfw PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_FILE}/../vendor/libs/glfw3d.lib )
find_package(OpenGL REQUIRED)
add_executable(Hello-Triangle Hello-Triangle.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/glad/glad.c)
target_link_libraries(Hello-Triangle glfw3)

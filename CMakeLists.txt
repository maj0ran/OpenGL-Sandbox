cmake_minimum_required(VERSION 3.13)
project(OpenGL-Sandbox)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp glad.c shaderHandler.cpp shaderHandler.h)

add_executable(OpenGLSandbox ${SOURCES})

find_library(GLFW NAMES libglfw3 PATHS lib)

target_link_libraries(OpenGLSandbox ${GLFW})

file(COPY shader DESTINATION .)
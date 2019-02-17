cmake_minimum_required(VERSION 3.13)
project(OpenGLSandbox)

set(CMAKE_CXX_STANDARD 17)

set (SOURCES main.cpp glad.c shaderHandler.cpp shaderHandler.h)

add_executable(OpenGLSandbox ${SOURCES})

target_link_libraries(OpenGLSandbox C:\\Users\\mrn\\CLionProjects\\OpenGLSandbox\\lib\\libglfw3.a)
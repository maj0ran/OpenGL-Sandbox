cmake_minimum_required(VERSION 3.13)
project(OpenGL-Sandbox)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp
        glad.c
        shaderHandler.cpp
        shaderHandler.h
        mrn/polygon_data.h mrn/Shader.cpp mrn/Shader.h stb_image.h
        glm/glm/glm.hpp mrn/Vertex.h polygons.cpp Gfx.cpp Gfx.h)

add_executable(OpenGLSandbox ${SOURCES})

find_library(GLFW NAMES libglfw3 PATHS lib)
target_link_libraries(OpenGLSandbox ${GLFW})

add_custom_command(TARGET OpenGLSandbox PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shader $<TARGET_FILE_DIR:OpenGLSandbox>/shader)
add_custom_command(TARGET OpenGLSandbox PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/textures $<TARGET_FILE_DIR:OpenGLSandbox>/textures)
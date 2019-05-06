cmake_minimum_required(VERSION 3.13)
project(OpenGL-Sandbox)

set(CMAKE_CXX_STANDARD 17)




# GLFW
add_subdirectory(3rdparty/glfw-3.3)
include_directories(3rdparty/glfw-3.3/include/GLFW)

# GLM
# GLM is header-only so no compiling needed
include_directories(3rdparty/glm/glm)

# GLAD
include_directories(3rdparty/glad/include)

#stb_image
include_directories(3rdparty/stb)

#Freetype
add_subdirectory(3rdparty/freetype-2.10.0)
include_directories(3rdparty/freetype-2.10.0/include)

set(SOURCES main.cpp
        3rdparty/glad/src/glad.c
        mrn/Shader.cpp mrn/Shader.h
        mrn/Vertex.h
        mrn/Mesh.cpp
        mrn/Mesh.h
        mrn/Model.cpp
        mrn/Model.h
        mrn/Camera.cpp mrn/Camera.h
        mrn/Scene.cpp mrn/Scene.h
        mrn/Primitives.cpp mrn/Primitives.h
        mrn/FontRenderer.cpp mrn/FontRenderer.h)

add_executable(OpenGLSandbox ${SOURCES})
target_link_libraries(OpenGLSandbox glfw freetype)

add_custom_command(TARGET OpenGLSandbox PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shader $<TARGET_FILE_DIR:OpenGLSandbox>/shader)
add_custom_command(TARGET OpenGLSandbox PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/textures $<TARGET_FILE_DIR:OpenGLSandbox>/textures)
add_custom_command(TARGET OpenGLSandbox PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/fonts $<TARGET_FILE_DIR:OpenGLSandbox>/fonts)
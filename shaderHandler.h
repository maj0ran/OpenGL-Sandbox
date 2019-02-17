//
// Created by mrn on 16.02.2019.
//

#ifndef OPENGLSANDBOX_SHADERHANDLER_H
#define OPENGLSANDBOX_SHADERHANDLER_H

#include <stdio.h>
#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"

const char* readFile(const char *src);
GLuint loadAndCompileShader(const char* source, GLenum shaderType, char infoLog[512]);

#endif //OPENGLSANDBOX_SHADERHANDLER_H

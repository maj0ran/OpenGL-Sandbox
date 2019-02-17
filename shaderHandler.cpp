//
// Created by mrn on 16.02.2019.
//

#include <cstdlib>
#include "shaderHandler.h"

#include <string>
#include <iostream>
#include <memory.h>

const char* readShaderSource(const char* src) {

    FILE* f = fopen(src, "r");
    fseek(f, 0, SEEK_END);
    long filesize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *string = (char*)malloc(filesize + 1);
    fread(string, filesize, 1, f);
    fclose(f);
    string[filesize] = 0;

    return string;

}

GLuint loadAndCompileShader(const char* source, GLenum shaderType, char infoLog[512]) {
    int shaderCompileSuccess;

    const char* s = readShaderSource(source);


    GLuint shaderId;
    shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &s, nullptr);
    glCompileShader(shaderId);
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderCompileSuccess);
    if(!shaderCompileSuccess) {
        glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else {
        memset(infoLog, 0, 512);
    }

    return shaderId;

}
//
// Created by mrn on 16.02.2019.
//

#include <cstdlib>
#include "shaderHandler.h"

#include <string>
#include <iostream>
#include <memory.h>

#include <fstream>

using namespace std;



const char* readShaderSource(const char* filepath) {
    fpos<mbstate_t> size = -1;
    char* contents = nullptr;
    ifstream file(filepath, ios::in|ios::ate);

    if(!file.is_open()) {
        cout << "Error reading file:" << filepath << std::endl;
        return nullptr;
    }

    file.seekg(0, ios::end);
    size = file.tellg();
    contents = new char[size];
    file.seekg(0, ios::beg);
    file.read(contents, size);
    file.close();
    return contents;
}

GLuint loadAndCompileShader(const char* source, GLenum shaderType, char infoLog[512]) {
    int shaderCompileSuccess;

    const char* s = readShaderSource(source);

    std::cout << s << std::endl;

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
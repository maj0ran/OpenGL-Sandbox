//
// Created by mrn on 18.02.2019.
//

#ifndef OPENGL_SANDBOX_SHADER_H
#define OPENGL_SANDBOX_SHADER_H

#include "../include/glad/glad.h"

namespace mrn {
    class Shader {
    public:
        GLuint id;

        Shader(const char *vertexPath, const char *fragmentPath);

        void use();

    private:
        const char *readFile(const char *filepath);


    };

}
#endif //OPENGL_SANDBOX_SHADER_H

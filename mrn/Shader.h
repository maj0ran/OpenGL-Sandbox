//
// Created by mrn on 18.02.2019.
//

#ifndef OPENGL_SANDBOX_SHADER_H
#define OPENGL_SANDBOX_SHADER_H

#include "../include/glad/glad.h"
#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/matrix_transform.hpp"
#include "../glm/glm/gtc/type_ptr.hpp"

using namespace glm;

namespace mrn {
    class Shader {
    public:
        GLuint id;
        mat4 proj = perspective(radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
        Shader(const char *vertexPath, const char *fragmentPath);

        void use();
        void translate();

    private:
        const char *readFile(const char *filepath);

    };

}
#endif //OPENGL_SANDBOX_SHADER_H

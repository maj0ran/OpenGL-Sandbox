//
// Created by mrn on 09.03.2019.
//

#ifndef OPENGL_SANDBOX_MODEL_H
#define OPENGL_SANDBOX_MODEL_H

#include "../glm/glm/glm.hpp"
#include "Mesh.h"
#include "Shader.h"

using namespace glm;

namespace mrn {
    class Model {
    public:
        Model();
        ~Model();

        Shader* shader;
        Mesh* mesh;
        GLuint vertex_array_id;

        void translate(float x, float y, float z);
        vec3 getPos();

        void attachShader(Shader* shader);

        mat4 getTranslationMat();

    private:
        vec3 pos;
        vec3 rot;
        vec3 scale;

        mat4 trans_mat;
        mat4 rot_mat;
        mat4 scale_mat;
    };

}


#endif //OPENGL_SANDBOX_MODEL_H

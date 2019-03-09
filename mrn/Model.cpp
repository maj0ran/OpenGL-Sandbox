//
// Created by mrn on 09.03.2019.
//

#include "Model.h"

using namespace glm;

namespace mrn {

    Model::Model() {

    }

    Model::~Model() {

    }

    void Model::translate(vec3 pos) {
        this->pos = pos;
        GLint transform_loc = glGetUniformLocation(shader->id, "transform");
        mat4 trans = mat4(1.0f);
        trans = glm::translate(trans, pos);
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, value_ptr(trans));
    }

    vec3 Model::getPos() {
        return pos;
    }

}


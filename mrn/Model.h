//
// Created by mrn on 09.03.2019.
//

#ifndef OPENGL_SANDBOX_MODEL_H
#define OPENGL_SANDBOX_MODEL_H

#include "../glm/glm/glm.hpp"
#include "Polygon.h"
#include "Shader.h"

using namespace glm;

namespace mrn {
    class Model {
    public:
        Model();
        ~Model();

        Shader* shader;
        Polygon* data;

        void translate(vec3 pos);
        vec3 getPos();

    private:
        vec3 pos;
        vec3 rot;
        vec3 scale;
    };

}


#endif //OPENGL_SANDBOX_MODEL_H

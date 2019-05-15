//
// Created by mrn on 11.03.2019.
//

#ifndef OPENGL_SANDBOX_WORLD_H
#define OPENGL_SANDBOX_WORLD_H


#include "camera/Camera.h"
#include "Model.h"

namespace mrn {

    class Scene {
    public:

        Scene();
        ~Scene();

        mrn::Camera cam;
        std::vector<mrn::Model> objects;

        void render();
    };
}

#endif //OPENGL_SANDBOX_WORLD_H

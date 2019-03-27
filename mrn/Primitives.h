//
// Created by mrn on 13.03.2019.
//

#ifndef OPENGL_SANDBOX_PRIMITIVES_H
#define OPENGL_SANDBOX_PRIMITIVES_H

#include "Mesh.h"

namespace mrn {
    class Primitive {
        public:
        static Mesh* createCube();
        static Mesh* createTriangle();
        static Mesh* createPyramid();
    };
}

#endif //OPENGL_SANDBOX_PRIMITIVES_H

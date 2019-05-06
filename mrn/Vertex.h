//
// Created by mrn on 20.02.2019.
//

#ifndef OPENGL_SANDBOX_VERTEX_H
#define OPENGL_SANDBOX_VERTEX_H

#include <stddef.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

using namespace glm;

namespace mrn {
    typedef struct _Vertex {
        vec3 pos;
        vec3 rgb;
        vec2 tex;
    } Vertex;


}

#endif //OPENGL_SANDBOX_VERTEX_H


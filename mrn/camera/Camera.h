//
// Created by mrn on 10.03.2019.
//

#ifndef OPENGL_SANDBOX_CAMERA_H
#define OPENGL_SANDBOX_CAMERA_H

#include <glm.hpp>
#include "glad/glad.h"

using namespace glm;

namespace mrn {
    class Camera {
    public:
        Camera(vec3 pos, vec3 front);
        ~Camera();

        // The name direction vector is not the best chosen name,
        // since it is actually pointing in the reverse direction of what it is targeting.
        vec3 direction;

        vec3 front;
        vec3 right;
        vec3 up;

        GLint view_mat_shader_location;

        mat4 view;
        mat4 projection;
        GLint projection_mat_shader_location;

        void lookAt(vec3 target);
        void setPos(vec3 pos);
        vec3 getPos();

        void setFov(float fov);
        float getFov();
        void update();
    private:
        float fov;
        vec3 pos;
        vec3 target;

        vec3 worldUp = vec3(0.0f, 1.0f, 0.0f);

        void calcProjectionMat();



    };

}

#endif //OPENGL_SANDBOX_CAMERA_H

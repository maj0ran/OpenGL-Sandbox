//
// Created by mrn on 10.03.2019.
//

#ifndef OPENGL_SANDBOX_CAMERA_H
#define OPENGL_SANDBOX_CAMERA_H

#include "../glm/glm/glm.hpp"
#include "../include/glad/glad.h"

using namespace glm;

namespace mrn {
    class Camera {
    public:
        Camera();
        ~Camera();

        // The name direction vector is not the best chosen name,
        // since it is actually pointing in the reverse direction of what it is targeting.
        vec3 direction;

        vec3 front;
        vec3 right;
        vec3 up;

        mat4 view;
        GLint view_mat_shader_location;


        mat4 projection;
        GLint projection_mat_shader_location;

        void lookAt(float x, float y, float z);
        void setPos(float x, float y, float z);
        vec3 getPos();

        void setFov(float fov);
        float getFov();
        void update();
    private:
        float fov;
        vec3 pos;
        vec3 target;

        void calcProjectionMat();



    };

}

#endif //OPENGL_SANDBOX_CAMERA_H

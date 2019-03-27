//
// Created by mrn on 10.03.2019.
//

#include "Camera.h"

#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/matrix_transform.hpp"

using namespace glm;

namespace mrn {

    mrn::Camera::Camera() {
        pos = vec3(0.0, 0.0, 3.0);
        front = vec3(0.0, 0.0, -1.0);
        up = vec3(0.0, 1.0, 0.0);
    }

    mrn::Camera::~Camera() = default;

    // TODO: is it correct to set right and up here?
    void Camera::lookAt(float x, float y, float z) {
        this->target = vec3(x, y, z);
        this->direction = normalize(pos - target);
        this->view = glm::lookAt(pos, target, up);

        vec3 up = vec3(0.0f, 1.0f, 0.0f);
        this->right = normalize(cross(up, direction));
        this->up = cross(direction, right);

    }

    void Camera::setPos(float x, float y, float z) {
        this->pos = vec3(x, y, z);
    }

    void Camera::setFov(float fov) {
        this->fov = fov;
        calcProjectionMat();
    }

    float Camera::getFov() {
        return fov;
    }

    vec3 Camera::getPos() {
        return this->pos;
    }

    void Camera::calcProjectionMat() {
        projection = perspective(radians(getFov()), 800.0f/600.0f, 0.1f, 100.0f);
    }

    void Camera::update() {
        this->view = glm::lookAt(pos, pos + front, up);
    }


}
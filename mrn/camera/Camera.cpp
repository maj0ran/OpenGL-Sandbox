//
// Created by mrn on 10.03.2019.
//


/**
 * This is the base-class for every Camera.
 * Every Camera has a position, a front and a up vector.
 * Furthermore, every camera has a fov and a view+projection matrix
 */
#include "Camera.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace glm;

namespace mrn {

    mrn::Camera::Camera(vec3 pos, vec3 front) {
        this->pos = pos;
        this->front = front;
    }

    mrn::Camera::~Camera() = default;

    // TODO: is it correct to set right and up here?
    void Camera::lookAt(vec3 target) {
        // Constructing Camera Coordinate System
        this->front = normalize(pos - front);
        this->right = normalize(cross(worldUp, front));
        this->up = cross(front, right);

        // Calculating View-Matrix
        this->view = glm::lookAt(pos, target, up);
    }

    void Camera::setPos(vec3 pos) {
        this->pos = pos;
    }

    vec3 Camera::getPos() {
        return this->pos;
    }


    void Camera::setFov(float fov) {
        this->fov = fov;
        calcProjectionMat();
    }

    float Camera::getFov() {
        return fov;
    }


    void Camera::calcProjectionMat() {
        projection = perspective(radians(getFov()), 800.0f/600.0f, 0.1f, 100.0f);
    }

    void Camera::update() {
    //    front = pos - vec3(0, 0, -1);
    //    this->front = normalize(pos - front);
        this->right = normalize(cross(worldUp, front));
        this->up = cross(front, right);
        this->view = glm::lookAt(pos, pos + front, up);
    }


}
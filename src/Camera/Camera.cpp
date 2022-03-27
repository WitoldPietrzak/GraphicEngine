//
// Created by Witek on 27.03.2022.
//

#include "Camera.h"

Camera::Camera(const Vector3 &position, const Vector3 &targetVector, const Vector3 &upVector) : position(position),
                                                                                                targetVector(
                                                                                                        targetVector),
                                                                                                upVector(upVector) {}

const Vector3 &Camera::getPosition() const {
    return position;
}

void Camera::setPosition(const Vector3 &position) {
    Camera::position = position;
}

const Vector3 Camera::getTargetVector() const {
    return targetVector;
}

void Camera::setTargetVector(const Vector3 &targetVector) {
    Camera::targetVector = targetVector;
}

const Vector3 &Camera::getUpVector() const {
    return upVector;
}

void Camera::setUpVector(const Vector3 &upVector) {
    Camera::upVector = upVector;
}

Camera::~Camera() {

}


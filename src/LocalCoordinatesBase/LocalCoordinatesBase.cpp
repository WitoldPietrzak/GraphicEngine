//
// Created by Witek on 12.05.2022.
//

#include "LocalCoordinatesBase.h"
#include "../Quaternion/Quaternion.h"


LocalCoordinatesBase::LocalCoordinatesBase() {}

LocalCoordinatesBase::LocalCoordinatesBase(const Vector3 &center, const Vector3 &rotationAxis, float rotationAngle)
        : center(center), rotationAxis(rotationAxis), rotationAngle(rotationAngle) {}

const Vector3 &LocalCoordinatesBase::getCenter() const {
    return center;
}

void LocalCoordinatesBase::setCenter(const Vector3 &center) {
    LocalCoordinatesBase::center = center;
}

const Vector3 &LocalCoordinatesBase::getRotationAxis() const {
    return rotationAxis;
}

void LocalCoordinatesBase::setRotationAxis(const Vector3 &rotationAxis) {
    LocalCoordinatesBase::rotationAxis = rotationAxis;
}

float LocalCoordinatesBase::getRotationAngle() const {
    return rotationAngle;
}

void LocalCoordinatesBase::setRotationAngle(float rotationAngle) {
    LocalCoordinatesBase::rotationAngle = rotationAngle;
}

Vector3 LocalCoordinatesBase::toBaseCoordinates(const Vector3 &local) const {
    auto global = Quaternion::rotateVector(local, -rotationAngle, rotationAxis);
    return global;
}

Vector3 LocalCoordinatesBase::fromBaseCoordinates(const Vector3 &global) const {

    auto local = Quaternion::rotateVector(global, rotationAngle, rotationAxis);

    return local;
}



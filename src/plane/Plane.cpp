//
// Created by witek on 01.03.2022.
//

#include "Plane.h"

Point Plane::getX() const {
    return x;
}

void Plane::setX(Point x) {
    Plane::x = x;
}

Vector3 Plane::getNormalVector() const {
    return normalVector;
}

void Plane::setNormalVector(Vector3 normalVector) {
    Plane::normalVector = normalVector;
}

float Plane::getDisplacement() const {
    return displacement;
}

void Plane::setDisplacement(float displacement) {
    Plane::displacement = displacement;
}

Plane::Plane(Point x, Vector3 normalVector, float displacement) : x(x), normalVector(normalVector), displacement(displacement) {}

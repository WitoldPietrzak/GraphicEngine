//
// Created by ancym on 12.03.2022.
//

#include "Ray.h"

Vector3 Ray::getOrigin() const {
    return origin;
}

void Ray::setOrigin(Vector3 origin) {
    Ray::origin = origin;
}

Vector3 Ray::getDirection() const {
    return direction;
}


void Ray::setDirection(Vector3 direction) {
    Ray::direction = direction;
}

float Ray::getTMin() const {
    return tMin;
}

void Ray::setTMin(float tMin) {
    Ray::tMin = tMin;
}

float Ray::getTMax() const {
    return tMax;
}

void Ray::setTMax(float tMax) {
    Ray::tMax = tMax;
}

Ray::Ray(Vector3 origin, Vector3 direction) : origin(origin), direction(direction) {}

Ray::Ray(Ray const &ray) : origin(ray.origin), direction(ray.direction) {}

Vector3 Ray::getPointInDistance(float distance) {
    return this->origin + this->direction * distance;
}






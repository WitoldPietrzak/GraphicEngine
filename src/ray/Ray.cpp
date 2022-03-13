//
// Created by ancym on 12.03.2022.
//

#include "Ray.h"
#include "../vector3/Vector3.h"
#include "../Point/Point.h"

Point Ray::getOrigin() const {
    return origin;
}

void Ray::setOrigin(Point origin) {
    Ray::origin = origin;
}

Vector3 Ray::getVector() const {
    return vector;
}

void Ray::setVector (Vector3 vector) {
    Ray::vector = vector;
}

Ray::Ray(Point origin, Vector3 vector) : origin(origin), vector(vector) {}
Ray::Ray(Ray const &ray) : origin(ray.origin), vector(ray.vector) {}





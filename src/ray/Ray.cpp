//
// Created by ancym on 12.03.2022.
//

#include "Ray.h"

Point3 Ray::getOrigin() const {
    return origin;
}

void Ray::setOrigin(Point3 origin) {
    Ray::origin = origin;
}

Vector3 Ray::getVector() const {
    return vector;
}

void Ray::setVector(Vector3 vector) {
    Ray::vector = vector;
}

Ray::Ray(Point3 origin, Vector3 vector) : origin(origin), vector(vector) {}

Ray::Ray(Ray const &ray) : origin(ray.origin), vector(ray.vector) {}





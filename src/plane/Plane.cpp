//
// Created by witek on 01.03.2022.
//

#include <vector>
#include "Plane.h"

Vector3 Plane::getNormalVector() const {
    return normalVector;
}

void Plane::setNormalVector(Vector3 normalVector) {
    Plane::normalVector = normalVector;
}

std::vector<Vector3> Plane::intersections(const Ray &ray) const {
    auto ndotxr = this->normalVector.multiplyScalar(ray.getOrigin());
    auto ndotv = this->normalVector.multiplyScalar(ray.getDirection());
    if (ndotv == 0) {
        return std::vector<Vector3>();
    }

    auto t = (this->distance - ndotxr) / ndotv;
    if (t < 0) {
        return std::vector<Vector3>();
    }
    auto intersectionPoint = ray.getOrigin() + ray.getDirection() * t;
    std::vector<Vector3> intersections;
    intersections.push_back(intersectionPoint);

    return intersections;
}

float Plane::getDistance() const {
    return distance;
}

void Plane::setDistance(float distance) {
    Plane::distance = distance;
}

Plane::Plane(const Vector3 &normalVector, float distance) : normalVector(normalVector), distance(distance) {}

Plane::Plane(const Vector3 &normalVector, const Vector3 &point) : normalVector(normalVector),
                                                                  distance(calculateDistance(normalVector, point)) {}


float Plane::calculateDistance(Vector3 normalVector, const Vector3 &point) {
    return (normalVector *
            (normalVector.multiplyScalar(point) / normalVector.multiplyScalar(normalVector))).getLength();
}

float Plane::calculateDistance(Vector3 point) {

    return this->normalVector.multiplyScalar(
            point - Ray(Vector3(0, 0, 0), normalVector).getPointInDistance(this->distance));
}

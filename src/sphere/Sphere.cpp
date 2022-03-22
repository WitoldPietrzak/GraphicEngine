//
// Created by witek on 01.03.2022.
//

#include "Sphere.h"
#include "../vector3/Vector3.h"
#include <cmath>
#include <vector>


Vector3 Sphere::getCenter() const {
    return center;
}

void Sphere::setCenter(Vector3 center) {
    Sphere::center = center;
}

float Sphere::getRadius() const {
    return radius;
}

void Sphere::setRadius(float radius) {
    Sphere::radius = radius;
}

Sphere::Sphere(Vector3 center, float radius) : center(center), radius(radius) {}

Sphere::Sphere(const Sphere &sphere) : center(sphere.center), radius(sphere.radius) {}

std::vector<Vector3> Sphere::intersections(Ray ray) const {

    std::vector<Vector3> intersections = std::vector<Vector3>();

    //
    auto v = this->getCenter() - ray.getOrigin();
    auto b = v.multiplyScalar(ray.getDirection());
    auto delta = (b * b) - v.multiplyScalar(v) + powf(this->getRadius(), 2);
    if (delta < 0) {
        return intersections;
    }
    auto sqrtDelta = sqrtf(delta);
    auto det1 = b - sqrtDelta;
    auto det2 = b + sqrtDelta;
    if (sqrtDelta == 0) {
        intersections.push_back(ray.getPointInDistance(det1));
        return intersections;
    }
    if (det1 > 0) {
        intersections.push_back(ray.getPointInDistance(det1));
    }
    if (det2 > 0) {
        intersections.push_back(ray.getPointInDistance(det2));
    }
    return intersections;
}

bool Sphere::belongs(const Vector3 &point) const {
    return powf(point.getX() - this->getCenter().getX(), 2) + powf(point.getY() - this->getCenter().getY(), 2) +
           powf(point.getZ() - this->getCenter().getZ(), 2) - powl(this->getRadius(), 2) == 0;
}

bool Sphere::inside(const Vector3 &point) const {
    return powf(point.getX() - this->getCenter().getX(), 2) + powf(point.getY() - this->getCenter().getY(), 2) +
           powf(point.getZ() - this->getCenter().getZ(), 2) - powl(this->getRadius(), 2) < 0;
}


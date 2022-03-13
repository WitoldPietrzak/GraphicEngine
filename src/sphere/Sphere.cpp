//
// Created by witek on 01.03.2022.
//

#include "Sphere.h"
#include "../vector3/Vector3.h"

Point Sphere::getCenter() const {
    return center;
}

void Sphere::setCenter(Point center) {
    Sphere::center = center;
}

Ray Sphere::getRay() const {
    return ray;
}

void Sphere::setRay(Ray ray) {
    Sphere::ray = ray;
}

int Sphere::getIntersectionNumber(Ray ray) const {
    int intersectionNumber = 0;
    return intersectionNumber;
}

Point Sphere::getIntersectionPoint(Ray ray) const {
    Point intersectionPoint = Point(0, 0, 0);
    return intersectionPoint;
}

Sphere::Sphere(Point center, Ray ray) : center(center), ray(ray) {}
Sphere::Sphere(const Sphere &sphere) : center(sphere.center), ray(sphere.ray) {}
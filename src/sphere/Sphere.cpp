//
// Created by witek on 01.03.2022.
//

#include "Sphere.h"
#include "../vector3/Vector3.h"

Point3 Sphere::getCenter() const {
    return center;
}

void Sphere::setCenter(Point3 center) {
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

Point3 Sphere::getIntersectionPoint(Ray ray) const {
    Point3 intersectionPoint = Point3(0, 0, 0);
    return intersectionPoint;
}

Sphere::Sphere(Point3 center, Ray ray) : center(center), ray(ray) {}
Sphere::Sphere(const Sphere &sphere) : center(sphere.center), ray(sphere.ray) {}
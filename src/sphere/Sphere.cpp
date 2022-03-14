//
// Created by witek on 01.03.2022.
//

#include "Sphere.h"
#include "../vector3/Vector3.h"


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

Point3 Sphere::getIntersectionPoints(Ray ray, Point3* intersections, float distance) const {
    Vector3 vec1 = ray.getOrigin() - center;
    float b = - vec1.multiplyScalar(ray.getDirection());
    float det = (b * b) - vec1.multiplyScalar(vec1) + radius*radius;
    if (det > 0) {
        float sqDet = sqrtf(det);
        float root1 = b - sqDet;
        float root2 = b + sqDet;
        if (root2 > 0) {
            if (root1 < 0) {
                if (root2 < distance) {
                    distance = root2;
                }
            }
            else {
                if (root1 < distance) {
                    distance = root1;
                }
            }
        }
    }
    else
        return* intersections;

}

Sphere::Sphere(Vector3 center, float radius) : center(center), radius(radius) {}
Sphere::Sphere(const Sphere &sphere) : center(sphere.center), radius(sphere.radius) {}


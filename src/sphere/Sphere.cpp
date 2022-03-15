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

Point3 Sphere::getIntersectionPoints(Ray ray, Point3 *intersections, float distance) const {
    Vector3 vec1 = ray.getOrigin() - center;
    float b = -vec1.multiplyScalar(ray.getDirection());
    float det = (b * b) - vec1.multiplyScalar(vec1) + radius * radius;
    if (det > 0) {
        float sqDet = sqrtf(det);
        float root1 = b - sqDet;
        float root2 = b + sqDet;
        if (root2 > 0) {
            if (root1 < 0) {
                if (root2 < distance) {
                    distance = root2;
                }
            } else {
                if (root1 < distance) {
                    distance = root1;
                }
            }
        }
    } else
        return *intersections;

}

Sphere::Sphere(Vector3 center, float radius) : center(center), radius(radius) {}

Sphere::Sphere(const Sphere &sphere) : center(sphere.center), radius(sphere.radius) {}

std::vector<Vector3> Sphere::intersections(Ray ray) const {
    std::vector<Vector3> intersections = std::vector<Vector3>();

    auto L = new Vector3(ray.getOrigin(), this->center);
    auto tc = L->multiplyScalar(ray.getDirection());

    auto d = sqrtf(L->getLengthSquared() - tc * tc);
    if (d > this->radius) {
        return intersections;
    }
    auto tlc = sqrtf(this->radius * this->radius - d * d);
    auto t1 = tc - tlc;
    auto t2 = tc + tlc;
    if (tlc == 0) {
        intersections.push_back(ray.getPointInDistance(t1));
        return intersections;
    }
    if (t1 > 0) {
        intersections.push_back(ray.getPointInDistance(t1));
    }
    if (t2 > 0) {
        intersections.push_back(ray.getPointInDistance(t2));
    }
    return intersections;
}


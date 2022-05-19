//
// Created by witek on 01.03.2022.
//

#include "Sphere.h"
#include "../../Intersection/Intersection.h"
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

std::vector<Intersection> Sphere::intersections(Ray ray) const {

    std::vector<Intersection> intersections = std::vector<Intersection>();

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
        auto intersection = Intersection(ray.getPointInDistance(det1), (Structure &) *this);
        intersections.push_back(intersection);
        return intersections;
    }
    if (det1 > 0) {
        auto intersection = Intersection(ray.getPointInDistance(det1), (Structure &) *this);
        intersections.push_back(intersection);
    }
    if (det2 > 0) {
        auto intersection = Intersection(ray.getPointInDistance(det2), (Structure &) *this);
        intersections.push_back(intersection);
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

Sphere::Sphere(const Vector3 &center, float radius, LightIntensity color) : center(center), radius(radius),
                                                                            Structure(color) {
    localCoordinatesBase.setCenter(center);
}

Vector3 Sphere::getNormalVector(Vector3 point) const {
    return (center - point).getNormalized();
}

void Sphere::MapUV(const Vector3 &point, float &u, float &v) const {
    auto localPoint = localCoordinatesBase.fromBaseCoordinates(point);
    auto localCenter = localCoordinatesBase.fromBaseCoordinates(center);
    auto pointToCenterVector = (localCenter - localPoint).getNormalized();
    u = 0.5f + atan2f(pointToCenterVector.getX(), pointToCenterVector.getZ()) / (2 * M_PI);
    v = 0.5f + asin(pointToCenterVector.getY()) / (M_PI);
}

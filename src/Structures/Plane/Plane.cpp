//
// Created by witek on 01.03.2022.
//

#include <vector>
#include "Plane.h"
#include "../../Exceptions/InfiniteIntersectionException.h"
#include "../../Intersection/Intersection.h"

Vector3 Plane::getNormalVector() const {
    return normalVector;
}

void Plane::setNormalVector(Vector3 normalVector) {
    Plane::normalVector = normalVector;
}

std::vector<Intersection> Plane::intersections(Ray ray) const {
    auto ndotxr = this->normalVector.multiplyScalar(ray.getOrigin());
    auto ndotv = this->normalVector.multiplyScalar(ray.getDirection());
    if (ndotv == 0) {
        if (belongs(ray.getOrigin())) {
//            throw InfiniteIntersectionException();
            return std::vector<Intersection>();
        }
        return std::vector<Intersection>();
    }

    auto t = (this->distance - ndotxr) / ndotv;
    if (t < 0) {
        return std::vector<Intersection>();
    }
    auto intersectionPoint = ray.getOrigin() + ray.getDirection() * t;
    std::vector<Intersection> intersections;
    auto intersection = Intersection(intersectionPoint, (Structure &) *this);
    intersections.push_back(intersection);
    return intersections;
}

float Plane::getDistance() const {
    return distance;
}

void Plane::setDistance(float distance) {
    Plane::distance = distance;
}

Plane::Plane(): normalVector(Vector3(0,1,0)), distance(0), Structure(LightIntensity::BLACK()) {}

Plane::Plane(const Vector3 &normalVector, float distance) : normalVector(normalVector), distance(distance),
                                                            Structure(LightIntensity::BLACK()) {}

Plane::Plane(const Vector3 &normalVector, const Vector3 &point) : normalVector(normalVector),
                                                                  distance(calculateDistance(normalVector, point)),
                                                                  Structure(LightIntensity::BLACK()) {}


float Plane::calculateDistance(const Vector3& normalVector, const Vector3 &point) {
auto distance = (normalVector.multiplyScalar(point))/normalVector.getLength();
    return distance;

}

float Plane::calculateDistance(Vector3 point) {

    return this->normalVector.multiplyScalar(
            point - Ray(Vector3(0, 0, 0), normalVector).getPointInDistance(this->distance));
}

bool Plane::belongs(const Vector3 &point) const {
    return this->getNormalVector().getX() * point.getX() + this->getNormalVector().getY() * point.getY() +
           this->getNormalVector().getZ() * point.getZ() + this->getDistance() == 0;
}

Plane::Plane(const Vector3 &normalVector, float distance, LightIntensity &color) : normalVector(normalVector),
                                                                                   distance(distance),
                                                                                   Structure(color) {}

Plane::Plane(const Vector3 &normalVector, const Vector3 &point, LightIntensity &color) : normalVector(normalVector),
                                                                                         distance(calculateDistance(
                                                                                                 normalVector, point)),
                                                                                         Structure(
                                                                                                 color) {}

Vector3 Plane::getNormalVector(Vector3 point) const {
    return normalVector;
}

void Plane::MapUV(const Vector3 &point, float &u, float &v) const {
    return;

}

void Plane::switchSide() {
    distance = -distance;
    normalVector = -normalVector;

}

void Plane::move(Vector3 direction) {
    Vector3 point = normalVector*distance;
    point += direction;
    distance = calculateDistance(normalVector,point);

}

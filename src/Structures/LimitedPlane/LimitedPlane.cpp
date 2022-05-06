//
// Created by Witek on 28.03.2022.
//

#include "LimitedPlane.h"
#include "../../Intersection/Intersection.h"


const Vector3 &LimitedPlane::getPointLt() const {
    return pointLT;
}

void LimitedPlane::setPointLt(const Vector3 &pointLt) {
    pointLT = pointLt;
}

const Vector3 &LimitedPlane::getPointRt() const {
    return pointRT;
}

void LimitedPlane::setPointRt(const Vector3 &pointRt) {
    pointRT = pointRt;
}

const Vector3 &LimitedPlane::getPointLb() const {
    return pointLB;
}

void LimitedPlane::setPointLb(const Vector3 &pointLb) {
    pointLB = pointLb;
}

const Vector3 &LimitedPlane::getPointRb() const {
    return pointRB;
}

void LimitedPlane::setPointRb(const Vector3 &pointRb) {
    pointRB = pointRb;
}

std::vector<Intersection> LimitedPlane::intersections(Ray ray) const {
    auto points = Plane::intersections(ray);
    if (points.empty()) {
        return points;
    }
    auto point = points[0];
    auto RT = pointLT.multiplyScalar(pointRT - pointLT) <= point.getPoint().multiplyScalar(pointRT - pointLT);
    auto RB = point.getPoint().multiplyScalar(pointRT - pointLT) <= pointRT.multiplyScalar(pointRT - pointLT);
    auto LT = pointLT.multiplyScalar(pointLB - pointLT) <= point.getPoint().multiplyScalar(pointLB - pointLT);
    auto LB = point.getPoint().multiplyScalar(pointLB - pointLT) <= pointLB.multiplyScalar(pointLB - pointLT);
    if (RT && LB && RB && LT) {
        return points;
    }
    return std::vector<Intersection>();
}

LimitedPlane::LimitedPlane(const Vector3 &normalVector, const Vector3 &point, LightIntensity color,
                           const Vector3 &pointLt, const Vector3 &pointRt, const Vector3 &pointLb,
                           const Vector3 &pointRb) : Plane(normalVector, point, color), pointLT(pointLt),
                                                     pointRT(pointRt), pointLB(pointLb), pointRB(pointRb) {}

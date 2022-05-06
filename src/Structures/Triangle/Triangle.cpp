//
// Created by Witek on 30.03.2022.
//

#include "Triangle.h"
#include "../../Intersection/Intersection.h"

#define PLUS_ZERO 0.00001
#define MINUS_ZERO -0.0001

std::vector<Intersection> Triangle::intersections(Ray ray) const {

    auto planeIntersections = plane.intersections(ray);
    if (planeIntersections.empty()) {
        return planeIntersections;
    }
    auto triangleIntersections = std::vector<Intersection>();
    for (auto &intersection : planeIntersections) {
        auto fa = a - intersection.getPoint();
        auto fb = b - intersection.getPoint();
        auto fc = c - intersection.getPoint();
        Vector3 crossVector = fa.multiplyVector(fb);
        if (crossVector.multiplyScalar(plane.getNormalVector()) < MINUS_ZERO) {
            continue;
        }
        crossVector = fb.multiplyVector(fc);
        if (crossVector.multiplyScalar(plane.getNormalVector()) < MINUS_ZERO) {
            continue;
        }
        crossVector = fc.multiplyVector(fa);
        if (crossVector.multiplyScalar(plane.getNormalVector()) < MINUS_ZERO) {
            continue;
        }
        intersection.setStructure(*this);
        triangleIntersections.push_back(intersection);
    }
    return triangleIntersections;
}

Triangle::Triangle(const Vector3 &a, const Vector3 &b, const Vector3 &c) : a(a), b(b), c(c),
                                                                           plane((b - a).multiplyVector(
                                                                                   c - a).getNormalized(), a) {
}

Triangle::Triangle(const Vector3 &a, const Vector3 &b, const Vector3 &c, const LightIntensity &color) : Structure(
        color), a(a), b(b), c(c), plane((b - a).multiplyVector(c - a).getNormalized(), a) {}

const Vector3 &Triangle::getA() const {
    return a;
}

void Triangle::setA(const Vector3 &a) {
    Triangle::a = a;
}

const Vector3 &Triangle::getB() const {
    return b;
}

void Triangle::setB(const Vector3 &b) {
    Triangle::b = b;
}

const Vector3 &Triangle::getC() const {
    return c;
}

void Triangle::setC(const Vector3 &c) {
    Triangle::c = c;
}

Vector3 Triangle::getNormalVector() const {

    return plane.getNormalVector();
}

Vector3 Triangle::getNormalVector(Vector3 point) const {
    return getNormalVector();
}

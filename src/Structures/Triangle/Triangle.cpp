//
// Created by Witek on 30.03.2022.
//

#include "Triangle.h"

#define PLUS_ZERO 0.00001
#define MINUS_ZERO -0.0001

std::vector<Vector3> Triangle::intersections(Ray ray) const {

    auto planeIntersections = plane.intersections(ray);
    if (planeIntersections.empty()) {
        return planeIntersections;
    }
    auto triangleIntersections = std::vector<Vector3>();
    for (auto &intersection : planeIntersections) {
        auto fa = a - intersection;
        auto fb = b - intersection;
        auto fc = c - intersection;
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

const Vector3 &Triangle::getNormalVector() const {
    return plane.getNormalVector();
}

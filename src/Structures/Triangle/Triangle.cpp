//
// Created by Witek on 30.03.2022.
//

#include "Triangle.h"

std::vector<Vector3> Triangle::intersections(Ray ray) const {
    return std::vector<Vector3>();
}

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

const Plane &Triangle::getPlane() const {
    return plane;
}

void Triangle::setPlane(const Plane &plane) {
    Triangle::plane = plane;
}

Triangle::Triangle(const LightIntensity &color, const Vector3 &a, const Vector3 &b, const Vector3 &c,
                   const Plane &plane) : Structure(color), a(a), b(b), c(c), plane(plane) {}

Triangle::Triangle(const Vector3 &a, const Vector3 &b, const Vector3 &c, const Plane &plane) : a(a), b(b), c(c),
                                                                                               plane(plane) {}

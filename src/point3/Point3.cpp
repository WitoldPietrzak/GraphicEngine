//
// Created by Witek on 08.03.2022.
//

#include "Point3.h"

float Point3::getX() const {
    return x;
}

void Point3::setX(float x) {
    Point3::x = x;
}

float Point3::getY() const {
    return y;
}

void Point3::setY(float y) {
    Point3::y = y;
}

float Point3::getZ() const {
    return z;
}

void Point3::setZ(float z) {
    Point3::z = z;
}

Point3::Point3(float x, float y, float z) : x(x), y(y), z(z) {}

bool Point3::operator==(const Point3 &obj) {
    return (this->x == obj.x && this->y == obj.y && this->z == obj.z);
}

bool Point3::operator!=(const Point3 &obj) {
    return !(this->x == obj.x && this->y == obj.y && this->z == obj.z);
}

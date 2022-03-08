//
// Created by Witek on 08.03.2022.
//

#include "Point.h"

float Point::getX() const {
    return x;
}

void Point::setX(float x) {
    Point::x = x;
}

float Point::getY() const {
    return y;
}

void Point::setY(float y) {
    Point::y = y;
}

float Point::getZ() const {
    return z;
}

void Point::setZ(float z) {
    Point::z = z;
}

Point::Point(float x, float y, float z) : x(x), y(y), z(z) {}

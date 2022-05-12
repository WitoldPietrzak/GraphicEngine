//
// Created by Witek on 11.05.2022.
//

#include "Quaternion.h"
#include <cmath>

Quaternion::Quaternion(float r, const Vector3 &v) : r(r), v(v) {}

float Quaternion::getR() const {
    return r;
}

void Quaternion::setR(float r) {
    Quaternion::r = r;
}

const Vector3 &Quaternion::getV() const {
    return v;
}

void Quaternion::setV(const Vector3 &v) {
    Quaternion::v = v;
}

bool Quaternion::operator==(const Quaternion &rhs) const {
    return r == rhs.r &&
           v == rhs.v;
}

bool Quaternion::operator!=(const Quaternion &rhs) const {
    return !(rhs == *this);
}

Quaternion Quaternion::operator*(const Quaternion &obj) const {
    return Quaternion(r * obj.r - v.multiplyScalar(obj.v),
                      v.multiply(obj.r) + obj.v.multiply(r) + v.multiplyVector(obj.v));
}

Quaternion Quaternion::operator*(const float &k) const {
    return Quaternion(k * r, v.multiply(k));
}

Quaternion Quaternion::operator+(const Quaternion &obj) const {
    return Quaternion(r + obj.r, v + (obj.v));
}

Quaternion Quaternion::conjuagte() const {
    return Quaternion(r, -v);
}

float Quaternion::length() const {
    return sqrtf(pow(r, 2) + pow(v.getX(), 2) + pow(v.getY(), 2) + pow(v.getZ(), 2));
}

float Quaternion::lengthSquared() const {
    return pow(r, 2) + pow(v.getX(), 2) + pow(v.getY(), 2) + pow(v.getZ(), 2);
}

Quaternion Quaternion::normalzed() const {
    auto norm = length();
    return Quaternion(r / length(), v / length());
}

Quaternion Quaternion::operator/(const float &k) const {
    return Quaternion(r / k, v / k);
}

Quaternion Quaternion::inverse() const {
    return this->conjuagte() / lengthSquared();
}

float Quaternion::dot(const Quaternion &obj) const {
    return (r * obj.r + v.multiplyScalar(obj.v));
}

 Quaternion Quaternion::rotationQuaternion(const float &angle, const Vector3 &axis ){
    return Quaternion(cosf(angle/2),axis*sinf(angle/2));
}

Vector3 Quaternion::rotateVector(const Vector3 &vector, const float &angle, const Vector3 &axis){
    auto quaternion = rotationQuaternion(angle,axis);
    auto pureQuaternion = Quaternion(0, vector);
    auto rotatedQuaternion = quaternion*pureQuaternion*(quaternion.inverse());
    return rotatedQuaternion.v;


}

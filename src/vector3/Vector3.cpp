//
// Created by witek on 01.03.2022.
//

#include "Vector3.h"
#include <cmath>
#include "../Exceptions/DivisionException.h"

float Vector3::getX() const {
    return x;
}

void Vector3::setX(float x) {
    Vector3::x = x;
}

float Vector3::getY() const {
    return y;
}

void Vector3::setY(float y) {
    Vector3::y = y;
}

float Vector3::getZ() const {
    return z;
}

void Vector3::setZ(float z) {
    Vector3::z = z;
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3::Vector3(const Vector3 &v1, const Vector3 &v2) : x(v2.x - v1.x), y(v2.y - v1.y), z(v2.z - v1.z) {}

Vector3::Vector3(Vector3 const &vector3) = default;

float Vector3::getLength() const {
    return sqrtf(powf(this->x, 2.0f) + powf(this->y, 2.0f) + powf(this->z, 2.0f));
}

float Vector3::getLengthSquared() const {
    return powf(this->x, 2.0f) + powf(this->y, 2.0f) + powf(this->z, 2.0f);
}

Vector3 Vector3::sum(const Vector3 &obj) const {
    return Vector3(this->x + obj.x, this->y + obj.y, this->z + obj.z);
}

Vector3 Vector3::sum(float k) const {
    return Vector3(this->x + k, this->y + k, this->z + k);
}

Vector3 Vector3::sub(const Vector3 &obj)  const {
    return Vector3(this->x - obj.x, this->y - obj.y, this->z - obj.z);
}

Vector3 Vector3::multiply(float k) const {
    return Vector3(this->x * k, this->y * k, this->z * k);
}

Vector3 Vector3::div(float k) const {
    return Vector3(this->x / k, this->y / k, this->z / k);
}

Vector3 Vector3::div(const Vector3 &vector3) {
    return Vector3(this->x / vector3.x, this->y / vector3.y, this->z / vector3.z);
}

Vector3 Vector3::multiply(const Vector3 &vector3) const {
    return Vector3(this->x * vector3.x, this->y * vector3.y, this->z * vector3.z);
}

Vector3 Vector3::multiplyVector(const Vector3 &vector3) const {
    return Vector3(
            this->y * vector3.z - this->z * vector3.y,
            this->z * vector3.x - this->x * vector3.z,
            this->x * vector3.y - this->y * vector3.x);
}

float Vector3::multiplyScalar( Vector3 vector3) const {
    return (this->x * vector3.x + this->y * vector3.y + this->z * vector3.z);
}

Vector3 Vector3::operator+() const {
    return Vector3(this->x, this->y, this->z);
}

Vector3 Vector3::operator-() const {
    return Vector3(-this->x, -this->y, -this->z);
}

Vector3 Vector3::operator+(const Vector3 &obj) const {
    return sum(obj);
}

Vector3 Vector3::operator+(float k) const {
    return sum(k);
}

Vector3 Vector3::operator-(const Vector3 &obj) const {
    return sub(obj);
}

Vector3 Vector3::operator*(const Vector3 &obj) const {
    return multiply(obj);
}

Vector3 Vector3::operator*(float k) const {
    return multiply(k);
}

Vector3 Vector3::operator/(const Vector3 &obj) {
    return div(obj);
}

Vector3 Vector3::operator/(float k) const {
    return div(k);
}

void Vector3::operator+=(const Vector3 &obj) {
    Vector3 buff = sum(obj);
    this->x = buff.x;
    this->y = buff.y;
    this->z = buff.z;
}

void Vector3::operator-=(const Vector3 &obj) {
    Vector3 buff = sub(obj);
    this->x = buff.x;
    this->y = buff.y;
    this->z = buff.z;
}

void Vector3::operator*=(const Vector3 &obj) {
    Vector3 buff = multiply(obj);
    this->x = buff.x;
    this->y = buff.y;
    this->z = buff.z;
}

void Vector3::operator/=(const Vector3 &obj) {
    Vector3 buff = div(obj);
    this->x = buff.x;
    this->y = buff.y;
    this->z = buff.z;
}

void Vector3::operator*=(float k) {
    Vector3 buff = multiply(k);
    this->x = buff.x;
    this->y = buff.y;
    this->z = buff.z;
}

void Vector3::operator/=(float k) {
    Vector3 buff = div(k);
    this->x = buff.x;
    this->y = buff.y;
    this->z = buff.z;
}

bool Vector3::operator==(const Vector3 &obj) {
    return (this->x == obj.x && this->y == obj.y && this->z == obj.z);

}

bool Vector3::operator==(const Vector3 &obj) const {
    return (this->x == obj.x && this->y == obj.y && this->z == obj.z);
}

bool Vector3::operator!=(const Vector3 &obj) {
    return !(this->x == obj.x && this->y == obj.y && this->z == obj.z);
}

void Vector3::normalize() {
    float n = this->getLength();
    if (n == 0) {
        return;
//        throw DivisionException();
    }

    auto result = this->div(n);
    this->x = result.x;
    this->y = result.y;
    this->z = result.z;
}

Vector3 Vector3::getNormalized(){
    float n = this->getLength();
    if (n == 0) {
        return this->multiply(n);
//        throw DivisionException();
    }
    return this->div(n);
}

Vector3 Vector3::operator-(Vector3 obj) {
    return sub(obj);
}

Vector3 Vector3::bisectingVector(Vector3 vector1, Vector3 vector2) {
    return vector1*vector2.getLength()+vector2*vector1.getLength();
}

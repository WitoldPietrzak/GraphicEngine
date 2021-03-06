//
// Created by witek on 01.03.2022.
//

#ifndef FOTO_VECTOR3_H
#define FOTO_VECTOR3_H


#include <string>

class Vector3 {

private:
    float x{}, y{}, z{};
public:
    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getZ() const;

    void setZ(float z);

    float getLength() const;

    float getLengthSquared() const;

    Vector3();

    Vector3(float x, float y, float z);

    Vector3(const Vector3 &v1, const Vector3 &v2);

    Vector3(const Vector3 &vector3);

    Vector3 sum(const Vector3 &obj) const;

    Vector3 sum(float k) const;

    Vector3 sub(const Vector3 &obj) const;

    Vector3 multiply(float k) const;

    Vector3 multiply(const Vector3 &vector3) const;

    Vector3 multiplyVector(const Vector3 &vector3) const;

    float multiplyScalar(Vector3 vector3) const;

    Vector3 div(float k) const;

    Vector3 div(const Vector3 &vector3);


    void normalize();

    Vector3 getNormalized() const;

    static Vector3 bisectingVector(Vector3 vector1, Vector3 vector2);

    static float calculateAngle(const Vector3 &vector1, const Vector3 &vector2);

    Vector3 rotateVector(Vector3 rotationVector, float number);

    Vector3 rotatePoint(Vector3 center, Vector3 rotationVector, float number);

    Vector3 operator+() const;

    Vector3 operator-() const;

    Vector3 operator+(const Vector3 &obj) const;

    Vector3 operator+(float k) const;

    Vector3 operator-(const Vector3 &obj) const;

    Vector3 operator-(Vector3 obj);

    Vector3 operator*(const Vector3 &obj) const;

    Vector3 operator*(float k) const;

    Vector3 operator/(const Vector3 &obj);

    Vector3 operator/(float k) const;

    void operator+=(const Vector3 &obj);

    void operator-=(const Vector3 &obj);

    void operator*=(const Vector3 &obj);

    void operator/=(const Vector3 &obj);

    bool operator==(const Vector3 &obj);

    bool operator==(const Vector3 &obj) const ;

    bool operator!=(const Vector3 &obj);

    void operator*=(float k);

    void operator/=(float k);
};


#endif //FOTO_VECTOR3_H

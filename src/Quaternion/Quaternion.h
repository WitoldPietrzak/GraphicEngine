//
// Created by Witek on 11.05.2022.
//

#ifndef FOTO_QUATERNION_H
#define FOTO_QUATERNION_H


#include "../Vector3/Vector3.h"

class Quaternion {
private:
    float r;
    Vector3 v;
public:
    Quaternion(float r, const Vector3 &v);

    float getR() const;

    void setR(float r);

    const Vector3 &getV() const;

    void setV(const Vector3 &v);

    bool operator==(const Quaternion &rhs) const;

    bool operator!=(const Quaternion &rhs) const;

    Quaternion operator+(const Quaternion &obj) const;

    Quaternion operator-(const Quaternion &obj) const;

    Quaternion operator*(const Quaternion &obj) const;

    Quaternion operator*(const float &k) const;

    Quaternion operator/(const float &k) const;

    Quaternion conjuagte() const;

    float length() const;

    Quaternion normalzed() const;

    Quaternion inverse() const;


    float lengthSquared() const;

    float dot(const Quaternion &obj) const;

    static Quaternion rotationQuaternion(const float &angle, const Vector3 &axis);

    static Vector3 rotateVector(const Vector3 &vector, const float &angle, const Vector3 &axis);
};


#endif //FOTO_QUATERNION_H

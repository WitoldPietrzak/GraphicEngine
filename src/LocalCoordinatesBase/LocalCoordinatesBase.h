//
// Created by Witek on 12.05.2022.
//

#ifndef FOTO_LOCALCOORDINATESBASE_H
#define FOTO_LOCALCOORDINATESBASE_H


#include "../Vector3/Vector3.h"

class LocalCoordinatesBase {
private:
    Vector3 center = Vector3(0, 0, 0);
    Vector3 rotationAxis = Vector3(0,0,0);
    float rotationAngle = 0;
public:

    LocalCoordinatesBase();

    LocalCoordinatesBase(const Vector3 &center, const Vector3 &rotationAxis, float rotationAngle);

    const Vector3 &getCenter() const;

    void setCenter(const Vector3 &center);

    const Vector3 &getRotationAxis() const;

    void setRotationAxis(const Vector3 &rotationAxis);

    float getRotationAngle() const;

    void setRotationAngle(float rotationAngle);

    Vector3 toBaseCoordinates(const Vector3 &local) const;

    Vector3 fromBaseCoordinates(const Vector3 &global) const;

};


#endif //FOTO_LOCALCOORDINATESBASE_H

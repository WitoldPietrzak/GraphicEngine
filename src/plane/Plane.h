//
// Created by witek on 01.03.2022.
//

#ifndef FOTO_PLANE_H
#define FOTO_PLANE_H


#include "../structure/Structure.h"
#include "../point3/Point3.h"
#include "../vector3/Vector3.h"

class Plane: Structure {

private:
    Point3 x;
    Vector3 normalVector;
    float displacement;

public:
    Point3 getX() const;

    void setX(Point3 x);

    Vector3 getNormalVector() const;

    void setNormalVector(Vector3 normalVector);

    float getDisplacement() const;

    void setDisplacement(float displacement);

    Plane(Point3 x, Vector3 normalVector, float displacement);



};


#endif //FOTO_PLANE_H

//
// Created by witek on 01.03.2022.
//

#ifndef FOTO_PLANE_H
#define FOTO_PLANE_H


#include "../structure/Structure.h"
#include "../Point/Point.h"
#include "../vector3/Vector3.h"

class Plane: Structure {

private:
    Point x;
    Vector3 normalVector;
    float displacement;

public:
    Point getX() const;

    void setX(Point x);

    Vector3 getNormalVector() const;

    void setNormalVector(Vector3 normalVector);

    float getDisplacement() const;

    void setDisplacement(float displacement);

    Plane(Point x, Vector3 normalVector, float displacement);



};


#endif //FOTO_PLANE_H

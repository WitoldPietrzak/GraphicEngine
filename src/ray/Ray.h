//
// Created by ancym on 12.03.2022.
//

#include "../Point/Point.h"
#include "../vector3/Vector3.h"

#ifndef FOTO_RAY_H
#define FOTO_RAY_H

#endif //FOTO_RAY_H

class Ray {

private:
    Point origin;
//    Point direction;
//    Point destination;
    Vector3 vector;
public:
    Point getOrigin() const;

    void setOrigin(Point origin);

    Vector3 getVector() const;

    void setVector (Vector3 vector);

    Ray(Point origin, Vector3 vector);
    Ray(Ray const &ray);



};
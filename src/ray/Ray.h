//
// Created by ancym on 12.03.2022.
//

#include "../point3/Point3.h"
#include "../vector3/Vector3.h"

#ifndef FOTO_RAY_H
#define FOTO_RAY_H

#endif //FOTO_RAY_H

class Ray {

private:
    Point3 origin;
//    Point direction;
//    Point destination;
    Vector3 vector;
public:
    Point3 getOrigin() const;

    void setOrigin(Point3 origin);

    Vector3 getVector() const;

    void setVector (Vector3 vector);

    Ray(Point3 origin, Vector3 vector);
    Ray(Ray const &ray);



};
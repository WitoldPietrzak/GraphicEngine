//
// Created by witek on 01.03.2022.
//

#ifndef FOTO_SPHERE_H
#define FOTO_SPHERE_H

#include "../structure/Structure.h"
#include "../point3/Point3.h"
#include "../ray/Ray.h"


class Sphere: Structure{

private:
    Point3 center;
    Ray ray;

public:
    Point3 getCenter() const;

    void setCenter(Point3 center);

    Ray getRay() const;

    void setRay(Ray ray);

    int getIntersectionNumber(Ray ray) const;

    Point3 getIntersectionPoint(Ray ray) const;

    Sphere(Point3 center, Ray ray);
    Sphere(const Sphere &sphere);



};


#endif //FOTO_SPHERE_H

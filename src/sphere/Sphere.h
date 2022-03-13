//
// Created by witek on 01.03.2022.
//

#ifndef FOTO_SPHERE_H
#define FOTO_SPHERE_H

#include "../structure/Structure.h"
#include "../Point/Point.h"
#include "../ray/Ray.h"


class Sphere: Structure{

private:
    Point center;
    Ray ray;

public:
    Point getCenter() const;

    void setCenter(Point center);

    Ray getRay() const;

    void setRay(Ray ray);

    int getIntersectionNumber(Ray ray) const;

    Point getIntersectionPoint(Ray ray) const;

    Sphere(Point center, Ray ray);
    Sphere(const Sphere &sphere);



};


#endif //FOTO_SPHERE_H

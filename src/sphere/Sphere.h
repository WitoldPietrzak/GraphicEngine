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

    Vector3 center;
    float radius;

public:
    Vector3 getCenter() const;

    void setCenter(Vector3 center);

    float getRadius() const;

    void setRadius(float radius);

    Point3 getIntersectionPoints(Ray ray, Point3* intersections, float distance) const;

    Sphere(Vector3 center, float radius);

    Sphere(const Sphere &sphere);

};


#endif //FOTO_SPHERE_H

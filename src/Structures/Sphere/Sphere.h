//
// Created by witek on 01.03.2022.
//

#ifndef FOTO_SPHERE_H
#define FOTO_SPHERE_H

#include <vector>
#include "../../Vector3/Vector3.h"
#include "../Structure/Structure.h"


class Sphere: public Structure{

private:

    Vector3 center;
    float radius;

public:
    Vector3 getCenter() const;

    void setCenter(Vector3 center);

    float getRadius() const;

    void setRadius(float radius);

    std::vector<Intersection> intersections(Ray ray) const override;

    bool belongs(const Vector3& point) const;
    bool inside(const Vector3& point) const;

    Sphere(Vector3 center, float radius);

    Sphere(const Sphere &sphere);

    Sphere(const Vector3& center, float radius, LightIntensity color);

    Vector3 getNormalVector(Vector3 point) const override;

    void MapUV(const Vector3 &point, float &u, float &v) const override;


};


#endif //FOTO_SPHERE_H

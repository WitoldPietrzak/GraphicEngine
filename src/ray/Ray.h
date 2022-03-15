//
// Created by ancym on 12.03.2022.
//

#include "../point3/Point3.h"
#include "../vector3/Vector3.h"

#ifndef FOTO_RAY_H
#define FOTO_RAY_H

class Ray {

private:

    Vector3 origin;
    Vector3 direction;
    Vector3 destination = Vector3(0,0,0);
    float distance = 0.0;
    float tMin = 0.0;
    float tMax = 0.0;
public:

    Vector3 getOrigin() const;

    void setOrigin(Vector3 origin);

    Vector3 getDirection() const;

    void setDirection (Vector3 direction);

    Vector3 getDestination() const;

    void setDestination(Vector3 destination);

    float getDistance();

    void setDistance(float distance);

    float getTMin() const;

    void setTMin(float tMin);

    float getTMax() const;

    void setTMax(float tMax);

    Ray(Vector3 origin, Vector3 direction);

    Ray(Ray const &ray);

    Vector3 getPointInDistance(float distance);



};

#endif //FOTO_RAY_H
//
// Created by witek on 01.03.2022.
//

#ifndef FOTO_PLANE_H
#define FOTO_PLANE_H


#include "../structure/Structure.h"
#include "../point3/Point3.h"
#include "../vector3/Vector3.h"
#include "../ray/Ray.h"

class Plane: Structure {

private:
    Vector3 normalVector;
    float distance;

public:

    Vector3 getNormalVector() const;

    void setNormalVector(Vector3 normalVector);

    float getDistance() const;

    void setDistance(float distance);

    Plane(const Vector3 &normalVector, float distance);

    Plane(const Vector3 &normalVector, const Vector3 &point);

    std::vector<Vector3> intersections(const Ray& ray) const;

    static float calculateDistance (Vector3 normalVector, const Vector3& point);

    float calculateDistance(Vector3 point);



};


#endif //FOTO_PLANE_H

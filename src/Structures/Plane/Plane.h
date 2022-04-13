//
// Created by witek on 01.03.2022.
//

#ifndef FOTO_PLANE_H
#define FOTO_PLANE_H


#include "../Structure/Structure.h"
#include "../../Vector3/Vector3.h"

class Plane: public Structure {

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

    Plane(const Vector3 &normalVector, float distance, LightIntensity &color);

    Plane(const Vector3 &normalVector, const Vector3 &point, LightIntensity &color);

    std::vector<Vector3> intersections(Ray ray) const override;

    static float calculateDistance (Vector3 normalVector, const Vector3& point);

    float calculateDistance(Vector3 point);

    bool belongs(const Vector3& point) const;

    void move(Vector3 &direction) override;


};


#endif //FOTO_PLANE_H

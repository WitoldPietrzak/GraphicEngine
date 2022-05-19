//
// Created by Witek on 28.03.2022.
//

#ifndef FOTO_LIMITEDPLANE_H
#define FOTO_LIMITEDPLANE_H


#include "../Plane/Plane.h"

class LimitedPlane : public Plane {
private:
    Vector3 pointLT;
    Vector3 pointRT;
    Vector3 pointLB;
    Vector3 pointRB;

public:
    LimitedPlane(const Vector3 &normalVector, const Vector3 &point, LightIntensity color, const Vector3 &pointLt,
                 const Vector3 &pointRt, const Vector3 &pointLb, const Vector3 &pointRb);

    LimitedPlane(const Vector3 &pointLt, const Vector3 &pointRt,
                 const Vector3 &pointLb, const Vector3 &pointRb);

    LimitedPlane(const Vector3 &startPoint, const Vector3 &widthVector, const Vector3 &heightVector);

    const Vector3 &getPointLt() const;

    void setPointLt(const Vector3 &pointLt);

    const Vector3 &getPointRt() const;

    void setPointRt(const Vector3 &pointRt);

    const Vector3 &getPointLb() const;

    void setPointLb(const Vector3 &pointLb);

    const Vector3 &getPointRb() const;

    void setPointRb(const Vector3 &pointRb);

    float getWidth() const;

    float getHeight() const;

    std::vector<Intersection> intersections(Ray ray) const override;

    void MapUV(const Vector3 &point, float &u, float &v) const override;
};


#endif //FOTO_LIMITEDPLANE_H

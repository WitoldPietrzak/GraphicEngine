//
// Created by witek on 20.06.2022.
//

#ifndef FOTO_DISTRIBUTEDLIGHT_H
#define FOTO_DISTRIBUTEDLIGHT_H


#include "../Light.h"

class DistributedLight: public Light {
    Vector3 point, vectorX, vectorY;
    float linAt =0;
    float constAtt = 1;

public:
    DistributedLight(const LightIntensity &lightIntensity, const Vector3 &point, const Vector3 &vectorX,
                     const Vector3 &vectorY);

    const Vector3 &getPoint() const;

    void setPoint(const Vector3 &point);

    const Vector3 &getVectorX() const;

    void setVectorX(const Vector3 &vectorX);

    const Vector3 &getVectorY() const;

    void setVectorY(const Vector3 &vectorY);

    float getLinAt() const;

    void setLinAt(float linAt);

    float getConstAtt() const;

    void setConstAtt(float constAtt);

    void move(Vector3 direction) override;

    const Vector3 getRandomPointOnSurface() const;

};


#endif //FOTO_DISTRIBUTEDLIGHT_H

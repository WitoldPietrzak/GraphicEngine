//
// Created by witek on 06.05.2022.
//

#ifndef FOTO_POINTLIGHT_H
#define FOTO_POINTLIGHT_H


#include "../Light.h"
#include "../../vector3/Vector3.h"

class PointLight: public Light{
private:
    Vector3 position = {0,0,0};
    float linAt =0;
    float constAtt = 1;
public:
    PointLight();

    PointLight(const Vector3 &position);

    PointLight(const LightIntensity &lightIntensity, const Vector3 &position);

    const Vector3 &getPosition() const;

    void setPosition(const Vector3 &position);

    float getLinAt() const;

    void setLinAt(float linAt);

    float getConstAtt() const;

    void setConstAtt(float constAtt);

    LightIntensity getLightIntensity(Vector3 point);

    void move(Vector3 direction) override;
};


#endif //FOTO_POINTLIGHT_H

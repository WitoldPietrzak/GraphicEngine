//
// Created by witek on 06.05.2022.
//

#ifndef FOTO_LIGHT_H
#define FOTO_LIGHT_H


#include "../LightIntensity/LightIntensity.h"
#include "../vector3/Vector3.h"

class Light {
protected:
    LightIntensity lightIntensity = LightIntensity::WHITE();
    Vector3 movemment = Vector3(0,0,0);
public:
    Light();
    Light(const LightIntensity &lightIntensity);
    const LightIntensity getLightIntensity() const;
    void setLightIntensity(const LightIntensity &lightIntensity);

    const Vector3 &getMovemment() const;

    void setMovemment(const Vector3 &movemment);

    virtual void move(Vector3 direction)  = 0;
};


#endif //FOTO_LIGHT_H

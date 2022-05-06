//
// Created by witek on 06.05.2022.
//

#ifndef FOTO_LIGHT_H
#define FOTO_LIGHT_H


#include "../LightIntensity/LightIntensity.h"

class Light {
private:
    LightIntensity lightIntensity = LightIntensity::WHITE();
public:
    Light();
    Light(const LightIntensity &lightIntensity);
    const LightIntensity &getLightIntensity() const;
    void setLightIntensity(const LightIntensity &lightIntensity);
};


#endif //FOTO_LIGHT_H

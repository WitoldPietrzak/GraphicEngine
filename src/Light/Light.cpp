//
// Created by witek on 06.05.2022.
//

#include "Light.h"

const LightIntensity &Light::getLightIntensity() const {
    return lightIntensity;
}

void Light::setLightIntensity(const LightIntensity &lightIntensity) {
    Light::lightIntensity = lightIntensity;
}

Light::Light(const LightIntensity &lightIntensity) : lightIntensity(lightIntensity) {}

Light::Light() {}

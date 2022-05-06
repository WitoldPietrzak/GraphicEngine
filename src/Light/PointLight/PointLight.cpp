//
// Created by witek on 06.05.2022.
//

#include "PointLight.h"

PointLight::PointLight(const LightIntensity &lightIntensity, const Vector3 &position) : Light(lightIntensity),
                                                                                        position(position) {}

PointLight::PointLight(const Vector3 &position) : position(position) {}

PointLight::PointLight() {}

const Vector3 &PointLight::getPosition() const {
    return position;
}

void PointLight::setPosition(const Vector3 &position) {
    PointLight::position = position;
}

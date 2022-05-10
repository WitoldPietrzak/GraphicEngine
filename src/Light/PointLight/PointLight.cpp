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

float PointLight::getLinAt() const {
    return linAt;
}

void PointLight::setLinAt(float linAt) {
    PointLight::linAt = linAt;
}

float PointLight::getConstAtt() const {
    return constAtt;
}

void PointLight::setConstAtt(float constAtt) {
    PointLight::constAtt = constAtt;
}

LightIntensity PointLight::getLightIntensity(Vector3 point) {
    return lightIntensity.div((constAtt + (linAt * (position - point).getLength())));
}

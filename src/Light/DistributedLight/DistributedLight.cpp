//
// Created by witek on 20.06.2022.
//

#include "DistributedLight.h"

DistributedLight::DistributedLight(const LightIntensity &lightIntensity, const Vector3 &point, const Vector3 &vectorX,
                                   const Vector3 &vectorY) : Light(lightIntensity), point(point), vectorX(vectorX),
                                                             vectorY(vectorY) {}

const Vector3 &DistributedLight::getPoint() const {
    return point;
}

void DistributedLight::setPoint(const Vector3 &point) {
    DistributedLight::point = point;
}

const Vector3 &DistributedLight::getVectorX() const {
    return vectorX;
}

void DistributedLight::setVectorX(const Vector3 &vectorX) {
    DistributedLight::vectorX = vectorX;
}

const Vector3 &DistributedLight::getVectorY() const {
    return vectorY;
}

void DistributedLight::setVectorY(const Vector3 &vectorY) {
    DistributedLight::vectorY = vectorY;
}

float DistributedLight::getLinAt() const {
    return linAt;
}

void DistributedLight::setLinAt(float linAt) {
    DistributedLight::linAt = linAt;
}

float DistributedLight::getConstAtt() const {
    return constAtt;
}

void DistributedLight::setConstAtt(float constAtt) {
    DistributedLight::constAtt = constAtt;
}

void DistributedLight::move(Vector3 direction) {
    point+=direction;

}

const Vector3 DistributedLight::getRandomPointOnSurface() const {

    Vector3 xOffset  = vectorX* ((float) rand()/(RAND_MAX));
    Vector3 yOffset  = vectorY* ((float) rand()/(RAND_MAX));
    return point+xOffset+yOffset;
}

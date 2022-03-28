//
// Created by Witek on 27.03.2022.
//

#include "PerspectiveCamera.h"

Image PerspectiveCamera::renderScene(const Scene &scene, int width, int height) {

    auto vectorX = -this->targetVector.multiplyVector(this->getUpVector()).getNormalized();
    auto vectorY = this->upVector;

    Image image = Image(width, height);
    Vector3 imageCenter = this->position + (this->targetVector * this->distance);
    Vector3 imageTopLeft = imageCenter - (vectorX * this->fovX / 2.0f) + (vectorY * this->fovY / 2.0f);

    auto pixelSizeX = this->getFovX() / image.getWidth();
    auto pixelSizeY = this->getFovY() / image.getHeight();
    for (int i = 0; i < image.getHeight(); i++) {
        for (int j = 0; j < image.getWidth(); j++) {
            // TODO sampling
            auto rayTarget = imageTopLeft+(vectorX*pixelSizeX*j)-(vectorY*pixelSizeY*i)+(vectorX*pixelSizeX/2.0f)-(vectorY*pixelSizeY/2.0f);
            auto color = sampler.doSampling(scene, this->position, rayTarget, vectorX, vectorY, pixelSizeX, pixelSizeY);
            image.setPixel(j, i, color);


        }
    }
    return image;
}

float PerspectiveCamera::getDistance() const {
    return distance;
}

void PerspectiveCamera::setDistance(float distance) {
    PerspectiveCamera::distance = distance;
}

float PerspectiveCamera::getFovX() const {
    return fovX;
}

void PerspectiveCamera::setFovX(float fovX) {
    PerspectiveCamera::fovX = fovX;
}

float PerspectiveCamera::getFovY() const {
    return fovY;
}

void PerspectiveCamera::setFovY(float fovY) {
    PerspectiveCamera::fovY = fovY;
}

const PerspectiveSampler &PerspectiveCamera::getSampler() const {
    return sampler;
}

void PerspectiveCamera::setSampler(const PerspectiveSampler &sampler) {
    PerspectiveCamera::sampler = sampler;
}

PerspectiveCamera::PerspectiveCamera(const Vector3 &position, const Vector3 &targetVector, const Vector3 &upVector,
                                     float distance, float fovX, float fovY, const PerspectiveSampler &sampler)
        : Camera(position, targetVector, upVector), distance(distance), fovX(fovX), fovY(fovY), sampler(sampler) {}

//
// Created by Witek on 27.03.2022.
//

#include "PerspectiveCamera.h"
#include <cmath>
#include <random>
#include <bits/stdc++.h>

Image PerspectiveCamera::renderScene(Scene scene, int width, int height) {

    auto vectorX = -this->targetVector.multiplyVector(this->getUpVector()).getNormalized();
    auto vectorY = this->upVector;

    Image image = Image(width, height);
    Vector3 imageCenter = this->position + (this->targetVector * this->distance);
    Vector3 imageTopLeft = imageCenter - (vectorX * this->fovX / 2.0f) + (vectorY * this->fovY / 2.0f);

    auto pixelSizeX = this->getFovX() / image.getWidth();
    auto pixelSizeY = this->getFovY() / image.getHeight();


    auto timeMoments = generateTimeMoments(timeSampleCount);
    for (int l = 0; l < std::max(timeSampleCount, 1); l++) {

        if (!timeMoments.empty()) {
            if (l == 0) {
                scene.increaseTime(timeMoments[l]);
            } else {
                scene.increaseTime(timeMoments[l] - timeMoments[l - 1]);
            }
        }
        for (int i = 0; i < image.getHeight(); i++) {
            for (int j = 0; j < image.getWidth(); j++) {
                if(j==image.getWidth()-1){
                    float debug = (i*image.getWidth()+(j*1.0f)+(l*image.getWidth()*image.getHeight()))/(1.0f * image.getHeight()*image.getWidth()* std::max(timeSampleCount, 1));
                    std::cout<<(debug*100)<<"% \n";
                }

                Vector3 rayTargetPosition = imageTopLeft + (vectorX * pixelSizeX * j) - (vectorY * pixelSizeY * i) +
                                            (vectorX * pixelSizeX / 2.0f) - (vectorY * pixelSizeY / 2.0f);

                LightIntensity color = LightIntensity(0, 0, 0);
                if (lensRadius <= 0 || depthSampleCount <= 0) {
                    color = sampler.doSampling(scene, this->position, rayTargetPosition, vectorX, vectorY,
                                               pixelSizeX, pixelSizeY);
                } else {
                    for (int k = 0; k < depthSampleCount; k++) {
                        Vector3 startPoint = calculatePointOnLens(vectorX, vectorY);
                        color.add(sampler.doSampling(scene, startPoint, rayTargetPosition, vectorX, vectorY, pixelSizeX,
                                                     pixelSizeY));
                    }
                }
                color = color.div((lensRadius > 0 ? (float)std::max(depthSampleCount,1) : 1.0f));
                l == 0 ? image.setPixel(j, i, color) : image.setPixel(j, i, image.getPixel(j, i).sum(color));


            }
        }
    }
    image.div(std::max((float)timeSampleCount, 1.0f));
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

float PerspectiveCamera::getLensRadius() const {
    return lensRadius;
}

void PerspectiveCamera::setLensRadius(float lensRadius) {
    PerspectiveCamera::lensRadius = lensRadius;
}

Vector3 PerspectiveCamera::calculatePointOnLens(const Vector3 &vectorX, const Vector3 &vectorY) {
    auto randomRadius = lensRadius * sqrtf(((float) rand() / (RAND_MAX)));
    float randomAngle = ((float) rand() / (RAND_MAX)) * M_PI * 2;
    auto xOffset = randomRadius * cosf(randomAngle);
    auto yOffset = randomRadius * sinf(randomAngle);
    return this->position + (vectorX * xOffset) + (vectorY * yOffset);

}

std::vector<float> PerspectiveCamera::generateTimeMoments(int amount) {
    std::vector<float> timeMoments = std::vector<float>();
    for (int i = 0; i < amount; i++) {
        timeMoments.push_back(sqrtf(((float) rand() / (RAND_MAX))));
    }
    std::sort(timeMoments.begin(), timeMoments.end(), std::less<>());
    return timeMoments;
}

int PerspectiveCamera::getDepthSampleCount() const {
    return depthSampleCount;
}

void PerspectiveCamera::setDepthSampleCount(int depthSampleCount) {
    PerspectiveCamera::depthSampleCount = depthSampleCount;
}

int PerspectiveCamera::getTimeSampleCount() const {
    return timeSampleCount;
}

void PerspectiveCamera::setTimeSampleCount(int timeSampleCount) {
    PerspectiveCamera::timeSampleCount = timeSampleCount;
}

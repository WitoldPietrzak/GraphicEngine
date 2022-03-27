//
// Created by Witek on 27.03.2022.
//

#include "OrthogonalCamera.h"

OrthogonalCamera::OrthogonalCamera(const Vector3 &position, const Vector3 &targetVector, const Vector3 &upVector,
                                   float width, float height) : Camera(position, targetVector, upVector), width(width),
                                                                height(height) {}

Image OrthogonalCamera::renderScene(const Scene &scene, int width, int height) {

    Image image = Image(width, height);
    auto pixelSizeX = this->getWidth() / image.getWidth();
    auto pixelSizeY = this->getHeight() / image.getHeight();
    auto vectorX = -this->targetVector.multiplyVector(this->getUpVector()).getNormalized();
    auto vectorY = this->upVector;
    for (int i = 0; i < image.getHeight(); i++) {
        for (int j = 0; j < image.getWidth(); j++) {
            auto origin = this->position + (vectorY * this->getHeight() / 2.0f) - (vectorX * this->getWidth() / 2.0f) -
                          (vectorY * i * pixelSizeY) + (vectorX * j * pixelSizeX);
            auto centeredOrigin = origin + (vectorX * pixelSizeX / 2.0f) + (vectorY * pixelSizeY / 2.0f);
            Ray ray = Ray(centeredOrigin, this->targetVector);
            LightIntensity color = scene.getBackgroundColor();
            float distance = -1;
            for (auto &structure: scene.getStructures()) {
                auto currentIntersections = structure->intersections(ray);
                if (currentIntersections.empty()) {
                    continue;
                }
                for (auto &intersection: currentIntersections) {
                    auto currentDistance = (intersection - ray.getOrigin()).getLength();
                    if (currentDistance < distance || distance == -1) {
                        distance = currentDistance;
                        color = structure->getColor();
                    }
                }
            }
            image.setPixel(j, i, color);


        }
    }
    return image;
}

float OrthogonalCamera::getWidth() const {
    return width;
}

void OrthogonalCamera::setWidth(float width) {
    OrthogonalCamera::width = width;
}

float OrthogonalCamera::getHeight() const {
    return height;
}

void OrthogonalCamera::setHeight(float height) {
    OrthogonalCamera::height = height;
}

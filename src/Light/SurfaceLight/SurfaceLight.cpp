//
// Created by witek on 08.05.2022.
//

#include "SurfaceLight.h"

const std::vector<PointLight *> &SurfaceLight::getPointLights() const {
    return pointLights;
}

std::vector<PointLight *>
SurfaceLight::generateSurfaceLight(Vector3 point, const Vector3& v1, const Vector3& v2, int density, LightIntensity color) {
    std::vector<PointLight *> lights;
    auto start = point;
    auto endX = point + v1;
    auto endY = point + v2;
    auto distanceX = v1.getLength();
    auto distanceY = v2.getLength();

    if (density == 1) {
        auto middleLight = new PointLight(color, start + (endX / 2) + (endY / 2));
        lights.push_back(middleLight);
        return lights;
    } else {
        auto singleMoveDistanceX = distanceX / (density - 1);
        auto singleMoveDistanceY = distanceY / (density - 1);
        for (int y = 0; y < density; y++) {
            for (int x = 0; x < density; x++) {
                lights.push_back(new PointLight(color, start + endX.multiply(x * singleMoveDistanceX) + endY.multiply(y * singleMoveDistanceY)));
            }
        }
    }

    return lights;


}

SurfaceLight::SurfaceLight(const Vector3& point, const Vector3& v1, const Vector3& v2, int density, LightIntensity color) : pointLights(
        generateSurfaceLight(point, v1, v2, density, color)) {

}

std::vector<PointLight *> SurfaceLight::generateSurfaceLight(const Vector3& point, const Vector3& v1, const Vector3& v2, int density) {
    return generateSurfaceLight(point, v1, v2, density, LightIntensity(255, 255, 255));
}

SurfaceLight::SurfaceLight(const Vector3& point, const Vector3& v1, const Vector3& v2, int density) : pointLights(
        generateSurfaceLight(point, v1, v2, density)) {

}

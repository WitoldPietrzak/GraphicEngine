//
// Created by witek on 08.05.2022.
//

#ifndef FOTO_SURFACELIGHT_H
#define FOTO_SURFACELIGHT_H


#include <vector>
#include "../Light.h"
#include "../PointLight/PointLight.h"

class SurfaceLight: public Light{
private:
    std::vector<PointLight*> pointLights;
public:

    SurfaceLight(const Vector3& point, const Vector3& v1, const Vector3& v2, int density, LightIntensity color);

    SurfaceLight(const Vector3& point, const Vector3& v1, const Vector3& v2, int density);

    std::vector<PointLight *> generateSurfaceLight(Vector3 point, const Vector3& v1, const Vector3& v2, int density, LightIntensity color);

    std::vector<PointLight *> generateSurfaceLight(const Vector3& point, const Vector3& v1, const Vector3& v2, int density);

    const std::vector<PointLight *> &getPointLights() const;
    
    void setLinAt(float linAt);

    void setConstAtt(float constAtt);

    void move(Vector3 direction) override;


};


#endif //FOTO_SURFACELIGHT_H

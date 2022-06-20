//
// Created by Witek on 27.03.2022.
//

#ifndef FOTO_PERSPECTIVECAMERA_H
#define FOTO_PERSPECTIVECAMERA_H


#include "../Camera.h"
#include "../../Sampling/Perspective/PerspectiveSampler.h"

class PerspectiveCamera: public Camera {
private:
    float distance, fovX, fovY;
    float lensRadius = 0;
    PerspectiveSampler sampler;
    int depthSampleCount = 0;
    int timeSampleCount = 0;

    Vector3 calculatePointOnLens(const Vector3 &vectorX, const Vector3 &vectorY);

    std::vector<float> generateTimeMoments(int amount);
public:
    PerspectiveCamera(const Vector3 &position, const Vector3 &targetVector, const Vector3 &upVector, float distance,
                      float fovX, float fovY, const PerspectiveSampler &sampler);

    Image renderScene(Scene scene, int width, int height) override;

    float getDistance() const;

    void setDistance(float distance);

    float getFovX() const;

    void setFovX(float fovX);

    float getFovY() const;

    void setFovY(float fovY);

    const PerspectiveSampler &getSampler() const;

    void setSampler(const PerspectiveSampler &sampler);

    float getLensRadius() const;

    void setLensRadius(float lensRadius);


    int getDepthSampleCount() const;

    void setDepthSampleCount(int depthSampleCount);

    int getTimeSampleCount() const;

    void setTimeSampleCount(int timeSampleCount);


};


#endif //FOTO_PERSPECTIVECAMERA_H

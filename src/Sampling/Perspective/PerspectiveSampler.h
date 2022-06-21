//
// Created by Witek on 28.03.2022.
//

#ifndef FOTO_PERSPECTIVESAMPLER_H
#define FOTO_PERSPECTIVESAMPLER_H


#include "../../Vector3/Vector3.h"
#include "../../Scene/Scene.h"

enum PixelSamplingType {
    AdaptiveSupersampling, DistributedSampling
};

class PerspectiveSampler {
private:
    int maxDepth = 4;
    int maxRayDepth = 4;
    int lightSampleCount = 100;
    PixelSamplingType samplingType = AdaptiveSupersampling;
    int pixelSampleCount = 4;
    bool distributedReflections = false;
    int reflectionSampleCount = 0;

    void sampleSpecularAndDiffuse(const Scene &scene, const Intersection& intersection, const Vector3& cameraPosition, LightIntensity &specular, LightIntensity &diffuse);

    Vector3 generateOffsetVector(Vector3 vector, float size);
public:
    PerspectiveSampler();

    explicit PerspectiveSampler(int maxDepth);

    LightIntensity
    doSampling(const Scene &scene, const Vector3 &center, Vector3 &target, Vector3 vectorX, Vector3 vectorY,
               float pixelWidthX, float pixelWidthY);

    LightIntensity
    doSampling(const Scene &scene, Vector3 center, Vector3 target, Vector3 vectorX, Vector3 vectorY, float pixelWidthX,
               float pixelWidthY, int depth, int location, LightIntensity centerColor, LightIntensity cornerColor);

    LightIntensity sampleRay(const Ray &ray, const Scene &scene);

    LightIntensity sampleRay(const Ray &ray, const Scene &scene, int rayDepth, bool insideStructure);

    int getMaxDepth() const;

    void setMaxDepth(int maxDepth);

    int getMaxRayDepth() const;

    void setMaxRayDepth(int maxRayDepth);

    int getLightSampleCount() const;

    void setLightSampleCount(int lightSampleCount);

    int getPixelSampleCount() const;

    void setPixelSampleCount(int pixelSampleCount);

    PixelSamplingType getSamplingType() const;

    void setSamplingType(PixelSamplingType samplingType);

    bool isDistributedReflections() const;

    void setDistributedReflections(bool distributedReflections);

    int getReflectionSampleCount() const;

    void setReflectionSampleCount(int reflectionSampleCount);
};


#endif //FOTO_PERSPECTIVESAMPLER_H

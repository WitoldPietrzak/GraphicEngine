//
// Created by Witek on 28.03.2022.
//

#ifndef FOTO_PERSPECTIVESAMPLER_H
#define FOTO_PERSPECTIVESAMPLER_H


#include "../../Vector3/Vector3.h"
#include "../../Scene/Scene.h"

class PerspectiveSampler {
private:
    int maxDepth;


    LightIntensity sampleDiffuse(const Scene &scene, const Intersection& intersection);
    LightIntensity sampleSpecular(const Scene &scene, const Intersection& intersection, const Vector3 cameraPosition);
    void sampleSpecularAndDiffuse(const Scene &scene, const Intersection& intersection, const Vector3& cameraPosition, LightIntensity &specular, LightIntensity &diffuse);
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

    int getMaxDepth() const;

    void setMaxDepth(int maxDepth);

};


#endif //FOTO_PERSPECTIVESAMPLER_H

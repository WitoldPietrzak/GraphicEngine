//
// Created by Witek on 27.03.2022.
//

#ifndef FOTO_ORTHOGONALSAMPLER_H
#define FOTO_ORTHOGONALSAMPLER_H


#include "../../Vector3/Vector3.h"
#include "../../Scene/Scene.h"

class OrthogonalSampler {
private:
public:
    LightIntensity doSampling(const Scene& scene, Vector3 center, const Vector3& target, Vector3 vectorX, Vector3 vectorY, float pixelWidthX, float pixelWidthY, int maxDepth);
    LightIntensity doSampling(const Scene& scene, Vector3 center, const Vector3& target, Vector3 vectorX, Vector3 vectorY, float pixelWidthX, float pixelWidthY, int maxDepth, int depth, int location, LightIntensity centerColor, LightIntensity cornerColor);
    LightIntensity sampleRay(const Ray& ray, const Scene& scene);


};


#endif //FOTO_ORTHOGONALSAMPLER_H

//
// Created by Witek on 27.03.2022.
//

#include "OrthogonalSampler.h"

LightIntensity
OrthogonalSampler::doSampling(const Scene &scene, Vector3 center, const Vector3 &target, Vector3 vectorX,
                              Vector3 vectorY,
                              float pixelWidthX,
                              float pixelWidthY) {

    Ray middle = Ray(center, target);
    Ray topLeft = Ray(center - (vectorX * pixelWidthX / 2.0f) + (vectorY * pixelWidthY / 2.0f), target);
    Ray topRight = Ray(center + (vectorX * pixelWidthX / 2.0f) + (vectorY * pixelWidthY / 2.0f), target);
    Ray bottomLeft = Ray(center - (vectorX * pixelWidthX / 2.0f) - (vectorY * pixelWidthY / 2.0f), target);
    Ray bottomRight = Ray(center + (vectorX * pixelWidthX / 2.0f) - (vectorY * pixelWidthY / 2.0f), target);

    auto colorMD = sampleRay(middle, scene);

//    if (maxDepth <= 0) {
//        return colorMD;
//    }
    auto colorTL = sampleRay(topLeft, scene);
    auto colorTR = sampleRay(topRight, scene);
    auto colorBL = sampleRay(bottomLeft, scene);
    auto colorBR = sampleRay(bottomRight, scene);

    if (colorTL != colorMD) {
        colorTL = doSampling(scene, (center + topLeft.getOrigin()) / 2, target, vectorX, vectorY, pixelWidthX / 2,
                             pixelWidthY / 2, 1, 0, colorMD, colorTL);
    }
    if (colorTR != colorMD) {
        colorTR = doSampling(scene, (center + topRight.getOrigin()) / 2, target, vectorX, vectorY, pixelWidthX / 2,
                             pixelWidthY / 2, 1, 1, colorMD, colorTR);
    }
    if (colorBL != colorMD) {
        colorBL = doSampling(scene, (center + bottomLeft.getOrigin()) / 2, target, vectorX, vectorY, pixelWidthX / 2,
                             pixelWidthY / 2, 1, 2, colorMD, colorBL);
    }
    if (colorBR != colorMD) {
        colorBR = doSampling(scene, (center + bottomRight.getOrigin()) / 2, target, vectorX, vectorY, pixelWidthX / 2,
                             pixelWidthY / 2, 1, 3, colorMD, colorBR);
    }

    int R = ((colorMD.getR() + colorTL.getR()) / 2
             + (colorMD.getR() + colorTR.getR()) / 2
             + (colorMD.getR() + colorBL.getR()) / 2
             + (colorMD.getR() + colorBR.getR()) / 2) / 4;
    int G = ((colorMD.getG() + colorTL.getG()) / 2
             + (colorMD.getG() + colorTR.getG()) / 2
             + (colorMD.getG() + colorBL.getG()) / 2
             + (colorMD.getG() + colorBR.getG()) / 2) / 4;
    int B = ((colorMD.getB() + colorTL.getB()) / 2
             + (colorMD.getB() + colorTR.getB()) / 2
             + (colorMD.getB() + colorBL.getB()) / 2
             + (colorMD.getB() + colorBR.getB()) / 2) / 4;
    return {R, G, B};


}

LightIntensity OrthogonalSampler::sampleRay(const Ray &ray, const Scene &scene) {
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
    return color;
}

LightIntensity
OrthogonalSampler::doSampling(const Scene &scene, Vector3 center, const Vector3 &target, Vector3 vectorX,
                              Vector3 vectorY,
                              float pixelWidthX, float pixelWidthY, int depth,
                              int location, LightIntensity centerColor, LightIntensity cornerColor) {

    Ray middle = Ray(center, target);
    Ray topLeft = Ray(center - (vectorX * pixelWidthX / 2.0f) + (vectorY * pixelWidthY / 2.0f), target);
    Ray topRight = Ray(center + (vectorX * pixelWidthX / 2.0f) + (vectorY * pixelWidthY / 2.0f), target);
    Ray bottomLeft = Ray(center - (vectorX * pixelWidthX / 2.0f) - (vectorY * pixelWidthY / 2.0f), target);
    Ray bottomRight = Ray(center + (vectorX * pixelWidthX / 2.0f) - (vectorY * pixelWidthY / 2.0f), target);

    LightIntensity colorMD;
    LightIntensity colorTL;
    LightIntensity colorTR;
    LightIntensity colorBL;
    LightIntensity colorBR;

    colorMD = sampleRay(middle, scene);
    // 0 = TL 1 = TR 2 = BL 3 = BR
    switch (location) {
        case 0: {
            colorTL = cornerColor;
            colorTR = sampleRay(topRight, scene);
            colorBL = sampleRay(bottomLeft, scene);
            colorBR = centerColor;
            break;
        }
        case 1: {
            colorTL = sampleRay(topLeft, scene);
            colorTR = cornerColor;
            colorBL = centerColor;
            colorBR = sampleRay(bottomRight, scene);
            break;
        }
        case 2: {
            colorTL = sampleRay(topLeft, scene);
            colorTR = centerColor;
            colorBL = cornerColor;
            colorBR = sampleRay(bottomRight, scene);
            break;
        }
        case 3: {
            colorTL = centerColor;
            colorTR = sampleRay(topRight, scene);
            colorBL = sampleRay(bottomLeft, scene);
            colorBR = cornerColor;
            break;

        }
        default: {
            colorTL = sampleRay(topLeft, scene);
            colorTR = sampleRay(topRight, scene);
            colorBL = sampleRay(bottomLeft, scene);
            colorBR = sampleRay(bottomRight, scene);
        }
    }

    if (depth < maxDepth) {
        if (colorTL != colorMD) {
            colorTL = doSampling(scene, (center + topLeft.getOrigin()) / 2, target, vectorX, vectorY, pixelWidthX / 2,
                                 pixelWidthY / 2, depth + 1, 0, colorMD, colorTL);
        }
        if (colorTR != colorMD) {
            colorTR = doSampling(scene, (center + topRight.getOrigin()) / 2, target, vectorX, vectorY, pixelWidthX / 2,
                                 pixelWidthY / 2, depth + 1, 1, colorMD, colorTR);
        }
        if (colorBL != colorMD) {
            colorBL = doSampling(scene, (center + bottomLeft.getOrigin()) / 2, target, vectorX, vectorY,
                                 pixelWidthX / 2,
                                 pixelWidthY / 2, depth + 1, 2, colorMD, colorBL);
        }
        if (colorBR != colorMD) {
            colorBR = doSampling(scene, (center + bottomRight.getOrigin()) / 2, target, vectorX, vectorY,
                                 pixelWidthX / 2,
                                 pixelWidthY / 2, depth + 1, 3, colorMD, colorBR);
        }
    }


    int R = ((colorMD.getR() + colorTL.getR()) / 2
             + (colorMD.getR() + colorTR.getR()) / 2
             + (colorMD.getR() + colorBL.getR()) / 2
             + (colorMD.getR() + colorBR.getR()) / 2) / 4;
    int G = ((colorMD.getG() + colorTL.getG()) / 2
             + (colorMD.getG() + colorTR.getG()) / 2
             + (colorMD.getG() + colorBL.getG()) / 2
             + (colorMD.getG() + colorBR.getG()) / 2) / 4;
    int B = ((colorMD.getB() + colorTL.getB()) / 2
             + (colorMD.getB() + colorTR.getB()) / 2
             + (colorMD.getB() + colorBL.getB()) / 2
             + (colorMD.getB() + colorBR.getB()) / 2) / 4;
    return {R, G, B};
}

OrthogonalSampler::OrthogonalSampler() : maxDepth(4) {}

OrthogonalSampler::OrthogonalSampler(int maxDepth) : maxDepth(maxDepth) {}

int OrthogonalSampler::getMaxDepth() const {
    return maxDepth;
}

void OrthogonalSampler::setMaxDepth(int maxDepth) {
    OrthogonalSampler::maxDepth = maxDepth;
}

//
// Created by Witek on 28.03.2022.
//

#include "PerspectiveSampler.h"

int PerspectiveSampler::getMaxDepth() const {
    return maxDepth;
}

void PerspectiveSampler::setMaxDepth(int maxDepth) {
    PerspectiveSampler::maxDepth = maxDepth;
}

LightIntensity
PerspectiveSampler::doSampling(const Scene &scene, const Vector3& center,Vector3 &target, Vector3 vectorX,
                               Vector3 vectorY,
                               float pixelWidthX,
                               float pixelWidthY) {


    auto vectorMD = target-center;
    auto vectorTL = (target-(vectorX*pixelWidthX/2.0f)+(vectorY*pixelWidthY/2.0f))-center;
    auto vectorTR = (target+(vectorX*pixelWidthX/2.0f)+(vectorY*pixelWidthY/2.0f))-center;
    auto vectorBL = (target-(vectorX*pixelWidthX/2.0f)-(vectorY*pixelWidthY/2.0f))-center;
    auto vectorBR = (target+(vectorX*pixelWidthX/2.0f)-(vectorY*pixelWidthY/2.0f))-center;

    Ray middle = Ray(center, vectorMD.getNormalized());
    Ray topLeft = Ray(center, vectorTL.getNormalized());
    Ray topRight = Ray(center,vectorTR.getNormalized());
    Ray bottomLeft = Ray(center, vectorBL.getNormalized());
    Ray bottomRight = Ray(center,vectorBR.getNormalized());

    auto colorMD = sampleRay(middle, scene);

    if (maxDepth <= 0) {
        return colorMD;
    }
    auto colorTL = sampleRay(topLeft, scene);
    auto colorTR = sampleRay(topRight, scene);
    auto colorBL = sampleRay(bottomLeft, scene);
    auto colorBR = sampleRay(bottomRight, scene);

    if (colorTL != colorMD) {
        colorTL = doSampling(scene, center, (target+vectorTL)/2.0f, vectorX, vectorY, pixelWidthX / 2,
                             pixelWidthY / 2, 1, 0, colorMD, colorTL);
    }
    if (colorTR != colorMD) {
        colorTR = doSampling(scene, center, (target+vectorTR)/2.0f, vectorX, vectorY, pixelWidthX / 2,
                             pixelWidthY / 2, 1, 1, colorMD, colorTR);
    }
    if (colorBL != colorMD) {
        colorBL = doSampling(scene, center, (target+vectorBL)/2.0f, vectorX, vectorY, pixelWidthX / 2,
                             pixelWidthY / 2, 1, 2, colorMD, colorBL);
    }
    if (colorBR != colorMD) {
        colorBR = doSampling(scene, center, (target+vectorBR)/2.0f, vectorX, vectorY, pixelWidthX / 2,
                             pixelWidthY / 2, 1, 3, colorMD, colorBR);
    }

    int R = (colorMD.getR() + colorTL.getR() + colorTR.getR() + colorBL.getR() + colorBR.getR()) / 5;
    int G = (colorMD.getG() + colorTL.getG() + colorTR.getG() + colorBL.getG() + colorBR.getG()) / 5;
    int B = (colorMD.getB() + colorTL.getB() + colorTR.getB() + colorBL.getB() + colorBR.getB()) / 5;
    return {R, G, B};


}

LightIntensity PerspectiveSampler::sampleRay(const Ray &ray, const Scene &scene) {
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
PerspectiveSampler::doSampling(const Scene &scene, Vector3 center, Vector3 target, Vector3 vectorX,
                               Vector3 vectorY,
                               float pixelWidthX, float pixelWidthY, int depth,
                               int location, LightIntensity centerColor, LightIntensity cornerColor) {

    auto vectorMD = target-center;
    auto vectorTL = (target-(vectorX*pixelWidthX/2.0f)+(vectorY*pixelWidthY/2.0f))-center;
    auto vectorTR = (target+(vectorX*pixelWidthX/2.0f)+(vectorY*pixelWidthY/2.0f))-center;
    auto vectorBL = (target-(vectorX*pixelWidthX/2.0f)-(vectorY*pixelWidthY/2.0f))-center;
    auto vectorBR = (target+(vectorX*pixelWidthX/2.0f)-(vectorY*pixelWidthY/2.0f))-center;

    Ray middle = Ray(center, vectorMD.getNormalized());
    Ray topLeft = Ray(center, vectorTL.getNormalized());
    Ray topRight = Ray(center,vectorTR.getNormalized());
    Ray bottomLeft = Ray(center, vectorBL.getNormalized());
    Ray bottomRight = Ray(center,vectorBR.getNormalized());

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
            colorTL = doSampling(scene, center, (target+vectorTL)/2.0f, vectorX, vectorY, pixelWidthX / 2,
                                 pixelWidthY / 2, depth+ 1, 0, colorMD, colorTL);
        }
        if (colorTR != colorMD) {
            colorTR = doSampling(scene, center, (target+vectorTR)/2.0f, vectorX, vectorY, pixelWidthX / 2,
                                 pixelWidthY / 2, depth+1, 1, colorMD, colorTR);
        }
        if (colorBL != colorMD) {
            colorBL = doSampling(scene, center, (target+vectorBL)/2.0f, vectorX, vectorY, pixelWidthX / 2,
                                 pixelWidthY / 2, depth+1, 2, colorMD, colorBL);
        }
        if (colorBR != colorMD) {
            colorBR = doSampling(scene, center, (target+vectorBR)/2.0f, vectorX, vectorY, pixelWidthX / 2,
                                 pixelWidthY / 2, depth+1, 3, colorMD, colorBR);
        }
    }


    int R = (colorMD.getR() + colorTL.getR() + colorTR.getR() + colorBL.getR() + colorBR.getR()) / 5;
    int G = (colorMD.getG() + colorTL.getG() + colorTR.getG() + colorBL.getG() + colorBR.getG()) / 5;
    int B = (colorMD.getB() + colorTL.getB() + colorTR.getB() + colorBL.getB() + colorBR.getB()) / 5;
    return {R, G, B};
}

PerspectiveSampler::PerspectiveSampler():maxDepth(4) {}

PerspectiveSampler::PerspectiveSampler(int maxDepth) : maxDepth(maxDepth) {}

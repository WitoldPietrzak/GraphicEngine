//
// Created by Witek on 28.03.2022.
//

#include <iostream>
#include "PerspectiveSampler.h"
#include "../../Intersection/Intersection.h"
#include <cmath>
#define PLUS_ZERO 0.00001

int PerspectiveSampler::getMaxDepth() const {
    return maxDepth;
}

void PerspectiveSampler::setMaxDepth(int maxDepth) {
    this->maxDepth = maxDepth;
}

LightIntensity
PerspectiveSampler::doSampling(const Scene &scene, const Vector3 &center, Vector3 &target, Vector3 vectorX,
                               Vector3 vectorY,
                               float pixelWidthX,
                               float pixelWidthY) {


    auto vectorMD = target - center;
    auto vectorTL = (target - (vectorX * pixelWidthX / 2.0f) + (vectorY * pixelWidthY / 2.0f)) - center;
    auto vectorTR = (target + (vectorX * pixelWidthX / 2.0f) + (vectorY * pixelWidthY / 2.0f)) - center;
    auto vectorBL = (target - (vectorX * pixelWidthX / 2.0f) - (vectorY * pixelWidthY / 2.0f)) - center;
    auto vectorBR = (target + (vectorX * pixelWidthX / 2.0f) - (vectorY * pixelWidthY / 2.0f)) - center;

    Ray middle = Ray(center, vectorMD.getNormalized());
    Ray topLeft = Ray(center, vectorTL.getNormalized());
    Ray topRight = Ray(center, vectorTR.getNormalized());
    Ray bottomLeft = Ray(center, vectorBL.getNormalized());
    Ray bottomRight = Ray(center, vectorBR.getNormalized());

    auto colorMD = sampleRay(middle, scene);

    if (maxDepth <= 0) {
        return colorMD;
    }
    auto colorTL = sampleRay(topLeft, scene);
    auto colorTR = sampleRay(topRight, scene);
    auto colorBL = sampleRay(bottomLeft, scene);
    auto colorBR = sampleRay(bottomRight, scene);

    if (maxDepth > 1) {
        if (colorTL != colorMD) {
            colorTL = doSampling(scene, center, (target + vectorTL / 2.0f), vectorX, vectorY, pixelWidthX / 2,
                                 pixelWidthY / 2, 1, 0, colorMD, colorTL);
        }
        if (colorTR != colorMD) {
            colorTR = doSampling(scene, center, (target + vectorTR / 2.0f), vectorX, vectorY, pixelWidthX / 2,
                                 pixelWidthY / 2, 1, 1, colorMD, colorTR);
        }
        if (colorBL != colorMD) {
            colorBL = doSampling(scene, center, (target + vectorBL / 2.0f), vectorX, vectorY, pixelWidthX / 2,
                                 pixelWidthY / 2, 1, 2, colorMD, colorBL);
        }
        if (colorBR != colorMD) {
            colorBR = doSampling(scene, center, (target + vectorBR / 2.0f), vectorX, vectorY, pixelWidthX / 2,
                                 pixelWidthY / 2, 1, 3, colorMD, colorBR);
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

LightIntensity PerspectiveSampler::sampleRay(const Ray &ray, const Scene &scene) {
    LightIntensity color = scene.getBackgroundColor();
    float distance = -1;
    Structure *nearestStructure = nullptr;
    Intersection *nearestIntersection = nullptr;
    auto intersections = std::vector<Intersection>();
    for (auto &structure: scene.getStructures()) {
        auto currentIntersections = structure->intersections(ray);
        if (currentIntersections.empty()) {
            continue;
        }
        for (auto &intersection: currentIntersections) {
            auto currentDistance = (intersection.getPoint() - ray.getOrigin()).getLength();
            if (currentDistance < distance || distance == -1) {
                distance = currentDistance;
                nearestStructure = structure;
                intersections.clear();
                intersections.push_back(intersection);
                nearestIntersection = &intersection;
            }
        }
    }
    if (nearestStructure == nullptr) {
        return scene.getBackgroundColor();
    }

    nearestIntersection = &intersections[0];

    LightIntensity diffuseLight;
    LightIntensity specularLight;
    sampleSpecularAndDiffuse(scene,*nearestIntersection,ray.getOrigin(),specularLight,diffuseLight);
    diffuseLight = diffuseLight.multiply(nearestStructure->getMaterial().getDiffuse());
    specularLight = specularLight.multiply(nearestStructure->getMaterial().getSpecular());

    LightIntensity ambientLight = scene.getAmbient();
    ambientLight = ambientLight.multiply(nearestStructure->getMaterial().getAmbient());

    return (ambientLight + diffuseLight + specularLight).multiply(nearestStructure->getColor());
}

LightIntensity
PerspectiveSampler::doSampling(const Scene &scene, Vector3 center, Vector3 target, Vector3 vectorX,
                               Vector3 vectorY,
                               float pixelWidthX, float pixelWidthY, int depth,
                               int location, LightIntensity centerColor, LightIntensity cornerColor) {


    auto vectorMD = target - center;
    auto vectorTL = (target - (vectorX * pixelWidthX / 2.0f) + (vectorY * pixelWidthY / 2.0f)) - center;
    auto vectorTR = (target + (vectorX * pixelWidthX / 2.0f) + (vectorY * pixelWidthY / 2.0f)) - center;
    auto vectorBL = (target - (vectorX * pixelWidthX / 2.0f) - (vectorY * pixelWidthY / 2.0f)) - center;
    auto vectorBR = (target + (vectorX * pixelWidthX / 2.0f) - (vectorY * pixelWidthY / 2.0f)) - center;

    Ray middle = Ray(center, vectorMD.getNormalized());
    Ray topLeft = Ray(center, vectorTL.getNormalized());
    Ray topRight = Ray(center, vectorTR.getNormalized());
    Ray bottomLeft = Ray(center, vectorBL.getNormalized());
    Ray bottomRight = Ray(center, vectorBR.getNormalized());

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
            colorTL = doSampling(scene, center, (target + vectorTL / 2.0f), vectorX, vectorY, pixelWidthX / 2,
                                 pixelWidthY / 2, depth + 1, 0, colorMD, colorTL);
        }
        if (colorTR != colorMD) {
            colorTR = doSampling(scene, center, (target + vectorTR / 2.0f), vectorX, vectorY, pixelWidthX / 2,
                                 pixelWidthY / 2, depth + 1, 1, colorMD, colorTR);
        }
        if (colorBL != colorMD) {
            colorBL = doSampling(scene, center, (target + vectorBL / 2.0f), vectorX, vectorY, pixelWidthX / 2,
                                 pixelWidthY / 2, depth + 1, 2, colorMD, colorBL);
        }
        if (colorBR != colorMD) {
            colorBR = doSampling(scene, center, (target + vectorBR / 2.0f), vectorX, vectorY, pixelWidthX / 2,
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

PerspectiveSampler::PerspectiveSampler() : maxDepth(4) {}

PerspectiveSampler::PerspectiveSampler(int maxDepth) : maxDepth(maxDepth) {}

LightIntensity PerspectiveSampler::sampleDiffuse(const Scene &scene, const Intersection &intersection) {
    auto lightSources = scene.getLightSources();
    auto diffuse = LightIntensity::BLACK();
    auto normal = intersection.getStructure().getNormalVector(intersection.getPoint());

    for (auto &lightSource: lightSources) {
        bool inShadow = false;
        auto lightVector = (lightSource->getPosition() - intersection.getPoint()).getNormalized();
        auto ray = Ray(intersection.getPoint(), lightVector.getNormalized());
        for (auto &structure: scene.getStructures()) {
            auto intersections = structure->intersections(ray);
            if (!intersections.empty() && structure != &intersection.getStructure()) {
                for (auto &inersect: intersections) {
                    if ((inersect.getPoint() - intersection.getPoint()).getLength() > PLUS_ZERO && (inersect.getPoint()-intersection.getPoint()).getLength() < (lightSource->getPosition()- intersection.getPoint()).getLength()) {
                        inShadow = true;
                        break;
                    }
                }
                if (inShadow) {
                    break;
                }

            }
        }
        if (inShadow) {
            continue;
        }

        auto color = lightSource->getLightIntensity();
        color = color.multiply(std::max(-normal.multiplyScalar(lightVector), 0.0f));
        diffuse += color;

    }

    return diffuse;
}

LightIntensity
PerspectiveSampler::sampleSpecular(const Scene &scene, const Intersection &intersection,
                                   const Vector3 cameraPosition) {
    auto lightSources = scene.getLightSources();
    auto specular = LightIntensity::BLACK();
    auto normal = intersection.getStructure().getNormalVector(intersection.getPoint());

    for (auto &lightSource: lightSources) {
        bool inShadow = false;
        auto lightVector = (lightSource->getPosition() - intersection.getPoint()).getNormalized();
        auto cameraVector = (cameraPosition - intersection.getPoint()).getNormalized();
        auto bisectingVector = Vector3::bisectingVector(cameraVector, lightVector).getNormalized();
        auto ray = Ray(intersection.getPoint(), lightVector.getNormalized());
        for (auto &structure: scene.getStructures()) {
            auto intersections = structure->intersections(ray);
            if (!intersections.empty() && structure != &intersection.getStructure()) {
                for (auto &inersect: intersections) {
                    if ((inersect.getPoint() - intersection.getPoint()).getLength() > PLUS_ZERO && (inersect.getPoint()-intersection.getPoint()).getLength() < (lightSource->getPosition()- intersection.getPoint()).getLength()) {
                        inShadow = true;
                        break;
                    }
                }
                if (inShadow) {
                    break;
                }

            }
        }
        if (inShadow) {
            continue;
        }

        auto color = lightSource->getLightIntensity();
        color = color.multiply(powf(std::max(normal.multiplyScalar(-bisectingVector), 0.0f), 128));
        specular += color;

    }
    return specular;
}

void PerspectiveSampler::sampleSpecularAndDiffuse(const Scene &scene, const Intersection &intersection,
                                                  const Vector3& cameraPosition, LightIntensity &specular,
                                                  LightIntensity &diffuse) {
    auto lightSources = scene.getLightSources();
    specular = LightIntensity::BLACK();
    diffuse = LightIntensity::BLACK();
    auto normal = intersection.getStructure().getNormalVector(intersection.getPoint());

    for (auto &lightSource: lightSources) {
        bool inShadow = false;
        auto lightVector = (lightSource->getPosition() - intersection.getPoint()).getNormalized();
        auto cameraVector = (cameraPosition - intersection.getPoint()).getNormalized();
        auto bisectingVector = Vector3::bisectingVector(cameraVector, lightVector).getNormalized();
        auto ray = Ray(intersection.getPoint(), lightVector.getNormalized());
        for (auto &structure: scene.getStructures()) {
            auto intersections = structure->intersections(ray);
            if (!intersections.empty()) {
                for (auto &inersect: intersections) {
                    if ((inersect.getPoint() - intersection.getPoint()).getLength() > PLUS_ZERO && (inersect.getPoint()-intersection.getPoint()).getLength() < (lightSource->getPosition()- intersection.getPoint()).getLength()) {
                        inShadow = true;
                        break;
                    }
                }
                if (inShadow) {
                    break;
                }

            }
        }
        if (inShadow) {
            continue;
        }

        auto color = lightSource->getLightIntensity();
        auto specularColor = color.multiply(powf(std::max(normal.multiplyScalar(-bisectingVector), 0.0f), 128));
        auto diffuseColor = color.multiply(std::max(-normal.multiplyScalar(lightVector), 0.0f));
        specular += specularColor;
        diffuse += diffuseColor;

    }
}

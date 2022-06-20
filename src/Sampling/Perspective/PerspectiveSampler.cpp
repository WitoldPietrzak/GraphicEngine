//
// Created by Witek on 28.03.2022.
//

#include <iostream>
#include "PerspectiveSampler.h"
#include "../../Intersection/Intersection.h"
#include <cmath>

#define PLUS_ZERO 0.0001

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


    switch (samplingType) {
        case SamplingType::AdaptiveSupersampling: {
            auto vectorMD = target - center;
            auto vectorTL = (target - (vectorX * pixelWidthX / 2.0f) + (vectorY * pixelWidthY / 2.0f)) - center;
            auto vectorTR = (target + (vectorX * pixelWidthX / 2.0f) + (vectorY * pixelWidthY / 2.0f)) - center;
            auto vectorBL = (target - (vectorX * pixelWidthX / 2.0f) - (vectorY * pixelWidthY / 2.0f)) - center;
            auto vectorBR = (target + (vectorX * pixelWidthX / 2.0f) - (vectorY * pixelWidthY / 2.0f)) - center;

            Ray middle = Ray(center, vectorMD.getNormalized());

            auto colorMD = sampleRay(middle, scene);

            if (maxDepth <= 0) {
                return colorMD;
            }

            Ray topLeft = Ray(center, vectorTL.getNormalized());
            Ray topRight = Ray(center, vectorTR.getNormalized());
            Ray bottomLeft = Ray(center, vectorBL.getNormalized());
            Ray bottomRight = Ray(center, vectorBR.getNormalized());

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
        case SamplingType::DistributedSampling: {
            auto colorMD = LightIntensity(0,0,0);
            for (int i = 0; i < pixelSampleCount; i++) {
                auto vectorTL = (target - (vectorX * pixelWidthX / 2.0f) + (vectorY * pixelWidthY / 2.0f));
                Vector3 xOffset  = vectorX* ((float) rand()/(RAND_MAX)) * pixelWidthX;
                Vector3 yOffset  = vectorY* ((float) rand()/(RAND_MAX)) * pixelWidthY;
                auto samplePoint = (vectorTL+xOffset+yOffset) - center;

                Ray ray = Ray(center, samplePoint.getNormalized());
                auto tempColor = sampleRay(ray,scene);
                colorMD = colorMD+tempColor;
            }
            colorMD = colorMD.div(pixelSampleCount);
            return colorMD;
        }
        default: return LightIntensity::WHITE();


    }


}

LightIntensity PerspectiveSampler::sampleRay(const Ray &ray, const Scene &scene, int rayDepth, bool insideStructure) {
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
            if (currentDistance > PLUS_ZERO && (currentDistance < distance || distance == -1)) {
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
    auto intersectionMaterial = nearestIntersection->getStructure().getMaterial().getMaterialType();
    if (intersectionMaterial == MaterialType::diffuse_color || intersectionMaterial == MaterialType::diffuse_texture ||
        rayDepth > maxRayDepth) {
        LightIntensity diffuseLight;
        LightIntensity specularLight;
        sampleSpecularAndDiffuse(scene, *nearestIntersection, ray.getOrigin(), specularLight, diffuseLight);
        diffuseLight = diffuseLight.multiply(nearestStructure->getMaterial().getDiffuse());
        specularLight = specularLight.multiply(nearestStructure->getMaterial().getSpecular());

        LightIntensity ambientLight = scene.getAmbient();
        ambientLight = ambientLight.multiply(nearestStructure->getMaterial().getAmbient());

        return (ambientLight + diffuseLight + specularLight).multiply(
                nearestStructure->getColor(nearestIntersection->getPoint()));
    }
    if (intersectionMaterial == MaterialType::mirror) {
        auto normalVector = nearestIntersection->getStructure().getNormalVector(nearestIntersection->getPoint());
        auto reflectedRayVector =
                ray.getDirection() - normalVector * 2 * (normalVector.multiplyScalar(ray.getDirection()));
        auto reflectedRay = Ray(nearestIntersection->getPoint(), reflectedRayVector);
        return sampleRay(reflectedRay, scene, rayDepth + 1, insideStructure);

    }
    if (intersectionMaterial == MaterialType::refraction) {
        auto incomingRayDirection = ray.getDirection();
        auto normalVector = nearestIntersection->getStructure().getNormalVector(nearestIntersection->getPoint());
        float n_in;
        float n_out;
        if (insideStructure) {
            n_out = 1;
            n_in = nearestIntersection->getStructure().getMaterial().getRefractionIndex();
        } else {
            n_in = 1;
            n_out = nearestIntersection->getStructure().getMaterial().getRefractionIndex();
            normalVector = -normalVector;
        }
        auto dnScalar = incomingRayDirection.multiplyScalar(normalVector);

        Vector3 refractedRayVector = (((incomingRayDirection - (normalVector * dnScalar)) * n_in) / n_out) -
                                     (normalVector *
                                      std::sqrt(1 - (powf(n_in, 2) * (1 - powf(dnScalar, 2))) / powf(n_out, 2)));
        auto refractedRay = Ray(nearestIntersection->getPoint(), refractedRayVector);
        return sampleRay(refractedRay, scene, rayDepth + 1, !insideStructure);

    }
}

LightIntensity PerspectiveSampler::sampleRay(const Ray &ray, const Scene &scene) {

    return sampleRay(ray, scene, 1, false);

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

void PerspectiveSampler::sampleSpecularAndDiffuse(const Scene &scene, const Intersection &intersection,
                                                  const Vector3 &cameraPosition, LightIntensity &specular,
                                                  LightIntensity &diffuse) {
    std::vector<PointLight *> lightSources = std::vector<PointLight *>();
    scene.getLightSources(lightSampleCount, lightSources);
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
                    if ((inersect.getPoint() - intersection.getPoint()).getLength() > PLUS_ZERO &&
                        (inersect.getPoint() - intersection.getPoint()).getLength() <
                        (lightSource->getPosition() - intersection.getPoint()).getLength()) {
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

        auto color = lightSource->getLightIntensity(intersection.getPoint());
        auto specularColor = color.multiply(powf(std::max(normal.multiplyScalar(-bisectingVector), 0.0f),
                                                 intersection.getStructure().getMaterial().getSmoothness()));
        auto diffuseColor = color.multiply(std::max(-normal.multiplyScalar(lightVector), 0.0f));
        specular += specularColor;
        diffuse += diffuseColor;

    }
}

int PerspectiveSampler::getMaxRayDepth() const {
    return maxRayDepth;
}

void PerspectiveSampler::setMaxRayDepth(int maxRayDepth) {
    PerspectiveSampler::maxRayDepth = maxRayDepth;
}

int PerspectiveSampler::getLightSampleCount() const {
    return lightSampleCount;
}

void PerspectiveSampler::setLightSampleCount(int lightSampleCount) {
    PerspectiveSampler::lightSampleCount = lightSampleCount;
}

int PerspectiveSampler::getPixelSampleCount() const {
    return pixelSampleCount;
}

void PerspectiveSampler::setPixelSampleCount(int pixelSampleCount) {
    PerspectiveSampler::pixelSampleCount = pixelSampleCount;
}

SamplingType PerspectiveSampler::getSamplingType() const {
    return samplingType;
}

void PerspectiveSampler::setSamplingType(SamplingType samplingType) {
    PerspectiveSampler::samplingType = samplingType;
}

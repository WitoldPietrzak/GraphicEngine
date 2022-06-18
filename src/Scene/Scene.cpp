//
// Created by Witek on 27.03.2022.
//

#include "Scene.h"

#include <utility>
#include<bits/stdc++.h>

Scene::Scene(const std::vector<Structure *> &structures, const LightIntensity &backgroundColor) : structures(
        std::move(structures)), backgroundColor(backgroundColor) {}

Scene::Scene(const LightIntensity &backgroundColor) : backgroundColor(backgroundColor),
                                                      structures(std::vector<Structure *>()) {}

Scene::Scene() : structures(std::vector<Structure *>()), backgroundColor(LightIntensity::BLACK()) {}

Scene::Scene(std::vector<Structure *> structures) : structures(std::move(structures)),
                                                    backgroundColor(LightIntensity::BLACK()) {}


Scene::Scene(const LightIntensity &backgroundColor, const LightIntensity &ambient) : backgroundColor(backgroundColor),
                                                                                     ambient(ambient) {

}

Scene::Scene(std::vector<Structure *> structures, const LightIntensity &backgroundColor, const LightIntensity &ambient)
        : structures(std::move(structures)),
          backgroundColor(backgroundColor), ambient(ambient) {}

const std::vector<Structure *> &Scene::getStructures() const {
    return structures;
}

void Scene::setStructures(const std::vector<Structure *> &structures) {
    Scene::structures = structures;
}

const LightIntensity &Scene::getBackgroundColor() const {
    return backgroundColor;
}

void Scene::setBackgroundColor(const LightIntensity &backgroundColor) {
    Scene::backgroundColor = backgroundColor;
}

void Scene::addStructure(Structure *structure) {
    this->structures.push_back(structure);

}

void Scene::removeStructure(Structure *structure) {
    std::remove(this->structures.begin(), this->structures.end(), structure);

}

const LightIntensity &Scene::getAmbient() const {
    return ambient;
}

void Scene::setAmbient(const LightIntensity &ambient) {
    Scene::ambient = ambient;
}

const std::vector<PointLight *> &Scene::getLightSources() const {
    return lightSources;
}

void Scene::setLightSources(const std::vector<PointLight *> &lightSources) {
    Scene::lightSources = lightSources;
}

void Scene::addLightSource(PointLight *light) {
    this->lightSources.push_back(light);

}

void Scene::removeLightSource(PointLight *light) {
    std::remove(this->lightSources.begin(), this->lightSources.end(), light);

}

void Scene::addLightSource(SurfaceLight *light) {
    for (auto &pointLight: light->getPointLights()) {
        addLightSource(pointLight);
    }

}

void Scene::removeLightSource(SurfaceLight *light) {
    for (auto &pointLight: light->getPointLights()) {
        removeLightSource(pointLight);
    }
}

void Scene::increaseTime(float time) {
    for(auto &structure: structures){
        structure->move(structure->getMovemment()*time);
    }
    for(auto &light: lightSources){
        light->move(light->getMovemment()*time);
    }

}

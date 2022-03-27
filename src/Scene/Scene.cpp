//
// Created by Witek on 27.03.2022.
//

#include "Scene.h"

#include <utility>
#include<bits/stdc++.h>

Scene::Scene(const std::vector<Structure*>& structures, const LightIntensity &backgroundColor) : structures(
        std::move(structures)), backgroundColor(backgroundColor) {}

Scene::Scene(const LightIntensity &backgroundColor) : backgroundColor(backgroundColor),
                                                      structures(std::vector<Structure*>()) {}

Scene::Scene() : structures(std::vector<Structure*>()), backgroundColor(LightIntensity::BLACK()) {}

Scene::Scene(const std::vector<Structure*>& structures) : structures(std::move(structures)),
                                                  backgroundColor(LightIntensity::BLACK()) {}

const std::vector<Structure*> &Scene::getStructures() const {
    return structures;
}

void Scene::setStructures(const std::vector<Structure*> &structures) {
    Scene::structures = structures;
}

const LightIntensity &Scene::getBackgroundColor() const {
    return backgroundColor;
}

void Scene::setBackgroundColor(const LightIntensity &backgroundColor) {
    Scene::backgroundColor = backgroundColor;
}

void Scene::addStructure(Structure* structure) {
    this->structures.push_back(structure);

}

void Scene::removeStructure(Structure* structure)
{
    std::remove(this->structures.begin(),this->structures.end(),structure);

}

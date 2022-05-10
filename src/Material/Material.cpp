//
// Created by witek on 23.04.2022.
//

#include "Material.h"

float Material::getAmbient() const {
    return ambient;
}

void Material::setAmbient(float ambient) {
    Material::ambient = ambient;
}

float Material::getSpecular() const {
    return specular;
}

void Material::setSpecular(float specular) {
    Material::specular = specular;
}

float Material::getDiffuse() const {
    return diffuse;
}

void Material::setDiffuse(float diffuse) {
    Material::diffuse = diffuse;
}

float Material::getSmoothness() const {
    return smoothness;
}

void Material::setSmoothness(float smoothness) {
    Material::smoothness = smoothness;
}

Material::Material(float ambient, float specular, float diffuse, float smoothness) : ambient(ambient),
                                                                                     specular(specular),
                                                                                     diffuse(diffuse),
                                                                                     smoothness(smoothness) {}

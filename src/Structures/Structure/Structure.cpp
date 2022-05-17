//
// Created by Witek on 08.03.2022.
//

#include "Structure.h"
#include "../../Intersection/Intersection.h"

Structure::Structure(const LightIntensity &color) { material.setColor(color); }

const LightIntensity &Structure::getColor() const {
    return material.getColor();
}

void Structure::setColor(const LightIntensity &color) {
    material.setColor(color);
}

Structure::Structure() {
    material.getColor();
}

Structure::~Structure() {

}

const Material &Structure::getMaterial() const {
    return material;
}

void Structure::setMaterial(const Material &material) {
    Structure::material = material;
}

const LocalCoordinatesBase &Structure::getLocalCoordinatesBase() const {
    return localCoordinatesBase;
}

void Structure::setLocalCoordinatesBase(const LocalCoordinatesBase &localCoordinatesBase) {
    Structure::localCoordinatesBase = localCoordinatesBase;
}

LightIntensity Structure::getColor(const Vector3 &intersectionPoint) {
    if (material.getMaterialType() == MaterialType::diffuse_texture) {
        auto texture = material.getTexture();
        float u, v;
        this->MapUV(intersectionPoint, u, v);
        return texture.getPixel(u, v);
    }
    return material.getColor();
    return LightIntensity();
}

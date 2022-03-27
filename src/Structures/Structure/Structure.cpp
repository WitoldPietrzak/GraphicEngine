//
// Created by Witek on 08.03.2022.
//

#include "Structure.h"

Structure::Structure(const LightIntensity &color) : color(color) {}

const LightIntensity &Structure::getColor() const {
    return color;
}

void Structure::setColor(const LightIntensity &color) {
    Structure::color = color;
}

Structure::Structure() {
    this->color = LightIntensity::BLACK();
}

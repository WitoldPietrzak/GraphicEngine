//
// Created by witek on 06.05.2022.
//

#include "Intersection.h"

const Vector3 &Intersection::getPoint() const {
    return point;
}

void Intersection::setPoint(const Vector3 &point) {
    Intersection::point = point;
}

void Intersection::setStructure(const Structure &structure) {
    Intersection::structure = structure;
}


const Structure &Intersection::getStructure() const {
    return structure;
}

void Intersection::setStructure1(Structure &structure) {
    Intersection::structure = structure;
}

Intersection::Intersection(const Vector3 &point, Structure &structure) : point(point), structure(structure) {}

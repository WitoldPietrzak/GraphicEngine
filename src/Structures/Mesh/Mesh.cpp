//
// Created by Witek on 05.04.2022.
//

#include "Mesh.h"

#include <utility>
#include<bits/stdc++.h>

std::vector<Triangle *> Mesh::getTriangles() const {
    return triangles;
}

void Mesh::setTriangles(std::vector<Triangle *> triangles) {
    Mesh::triangles = std::move(triangles);
}

void Mesh::addTriangle(Triangle *triangle) {
    triangles.push_back(triangle);

}

void Mesh::removeTriangle(Triangle *triangle) {
    std::remove(this->triangles.begin(), this->triangles.end(), triangle);

}


Mesh::~Mesh() = default;

std::vector<Vector3> Mesh::intersections(Ray ray) const {
    std::vector<Vector3> intersections = std::vector<Vector3>();
    for (auto &triangle: triangles) {
        std::vector<Vector3> currentIntersections = triangle->intersections(ray);
        for (auto &intersection: currentIntersections) {
            intersections.push_back(intersection);
        }
    }
    return intersections;
}

Mesh::Mesh(const LightIntensity &color, std::vector<Triangle *> triangles) : Structure(color),
                                                                             triangles(std::move(triangles)) {}

Mesh::Mesh(std::vector<Triangle *> triangles) : triangles(std::move(triangles)) {}

Mesh::Mesh(const LightIntensity &color) : Structure(color) {}

Mesh::Mesh():triangles(std::vector<Triangle *>()) {}

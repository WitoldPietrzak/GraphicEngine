//
// Created by Witek on 05.04.2022.
//

#include "Mesh.h"

#include <utility>
#include<bits/stdc++.h>
#include "../../Intersection/Intersection.h"

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

std::vector<Intersection> Mesh::intersections(Ray ray) const {
    std::vector<Intersection> intersections = std::vector<Intersection>();
    for (auto &triangle: triangles) {
        std::vector<Intersection> currentIntersections = triangle->intersections(ray);
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

Vector3 Mesh::getNormalVector(Vector3 point) const {
    for(auto &triangle: triangles){
        return Vector3(0,0,0);
        //TODO
    }
    return Vector3(0,0,0);
}

void Mesh::setColor(const LightIntensity &color) {
    Structure::setColor(color);
    for(auto &triangle: triangles){
        triangle->setColor(color);
    }


}

void Mesh::setMaterial(const Material &material) {
    Structure::setMaterial(material);
    for(auto &triangle: triangles){
        triangle->setMaterial(material);
    }
}

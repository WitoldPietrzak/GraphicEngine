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
    Mesh::triangles = triangles;
}

void Mesh::addTriangle(Triangle* triangle) {
    triangles.push_back(triangle);

}

void Mesh::removeTriangle(Triangle* triangle) {
    std::remove(this->triangles.begin(),this->triangles.end(),triangle);

}

Mesh::Mesh(std::vector<Triangle *> triangles) : triangles(std::move(triangles)) {}

Mesh::~Mesh() {

}

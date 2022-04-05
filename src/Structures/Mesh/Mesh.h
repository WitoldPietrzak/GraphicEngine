//
// Created by Witek on 05.04.2022.
//

#ifndef FOTO_MESH_H
#define FOTO_MESH_H


#include <vector>
#include "../Triangle/Triangle.h"

class Mesh {
private:
    std::vector<Triangle*> triangles;
public:
    explicit Mesh(std::vector<Triangle *> triangles);

    virtual ~Mesh();

    std::vector<Triangle *> getTriangles() const;

    void setTriangles(std::vector<Triangle *> triangles);

    void addTriangle(Triangle* triangle);
    void removeTriangle(Triangle* triangle);

};


#endif //FOTO_MESH_H

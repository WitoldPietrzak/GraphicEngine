//
// Created by Witek on 05.04.2022.
//

#ifndef FOTO_MESH_H
#define FOTO_MESH_H


#include <vector>
#include "../Triangle/Triangle.h"

class Mesh: public Structure{
private:
    std::vector<Triangle*> triangles;
public:
    Mesh(const LightIntensity &color, std::vector<Triangle *> triangles);

    Mesh(std::vector<Triangle *> triangles);

    Mesh(const LightIntensity &color);

    Mesh();

    virtual ~Mesh();

    std::vector<Triangle *> getTriangles() const;

    void setTriangles(std::vector<Triangle *> triangles);

    void addTriangle(Triangle* triangle);
    void removeTriangle(Triangle* triangle);

    std::vector<Intersection> intersections(Ray ray) const override;

    Vector3 getNormalVector(Vector3 point) const override;

    void setColor(const LightIntensity &color) override;

    void setMaterial(const Material &material) override;


};


#endif //FOTO_MESH_H

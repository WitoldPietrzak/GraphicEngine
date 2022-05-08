//
// Created by Witek on 08.03.2022.
//

#ifndef FOTO_STRUCTURE_H
#define FOTO_STRUCTURE_H


#include <vector>
#include "../../Vector3/Vector3.h"
#include "../../Ray/Ray.h"
#include "../../LightIntensity/LightIntensity.h"
#include "../../Material/Material.h"

class Intersection;

class Structure {
protected:
    LightIntensity color = LightIntensity::BLACK();
    Material material = Material(0.3,0.5,0.5);
public:
    virtual std::vector<Intersection> intersections(Ray ray) const = 0;

    explicit Structure(const LightIntensity &color);

    Structure();

    virtual ~Structure();

    const LightIntensity &getColor() const;

    virtual void setColor(const LightIntensity &color);

    const Material &getMaterial() const;

    virtual void setMaterial(const Material &material);

    virtual Vector3 getNormalVector(Vector3 point) const = 0;


};


#endif //FOTO_STRUCTURE_H

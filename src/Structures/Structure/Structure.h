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
#include "../../LocalCoordinatesBase/LocalCoordinatesBase.h"

class Intersection;

class Structure {
protected:
    Material material = Material(0.3,0.3,0.5, 32);
    LocalCoordinatesBase localCoordinatesBase = LocalCoordinatesBase();
    bool transparent = false;
    Vector3 movemment = Vector3(0,0,0);
public:
    virtual std::vector<Intersection> intersections(Ray ray) const = 0;

    explicit Structure(const LightIntensity &color);

    Structure();

    virtual ~Structure();

    const LightIntensity &getColor() const;

    virtual void setColor(const LightIntensity &color);

    const Material &getMaterial() const;

    virtual void setMaterial(const Material &material);

    const LocalCoordinatesBase &getLocalCoordinatesBase() const;

    void setLocalCoordinatesBase(const LocalCoordinatesBase &localCoordinatesBase);

    LightIntensity getColor(const Vector3 &intersectionPoint);

    virtual Vector3 getNormalVector(Vector3 point) const = 0;

    const Vector3 &getMovemment() const;

    void setMovemment(const Vector3 &movemment);


    virtual void MapUV(const Vector3 &point, float &u, float &v) const = 0;

    virtual void move(Vector3 direction)  = 0;


};


#endif //FOTO_STRUCTURE_H

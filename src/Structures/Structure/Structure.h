//
// Created by Witek on 08.03.2022.
//

#ifndef FOTO_STRUCTURE_H
#define FOTO_STRUCTURE_H


#include <vector>
#include "../../Vector3/Vector3.h"
#include "../../Ray/Ray.h"
#include "../../LightIntensity/LightIntensity.h"

class Structure {
protected:
    LightIntensity color;
public:
    virtual std::vector<Vector3> intersections(Ray ray) const = 0;

    explicit Structure(const LightIntensity &color);

    Structure();

    virtual ~Structure();

    const LightIntensity &getColor() const;

    void setColor(const LightIntensity &color);

    virtual void move(Vector3 &direction)  = 0;


};


#endif //FOTO_STRUCTURE_H

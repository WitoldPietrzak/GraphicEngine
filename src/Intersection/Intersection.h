//
// Created by witek on 06.05.2022.
//

#ifndef FOTO_INTERSECTION_H
#define FOTO_INTERSECTION_H


#include "../vector3/Vector3.h"
#include "../Structures/Structure/Structure.h"

class Intersection {
private:
    Vector3 point = Vector3(0, 0, 0);
    Structure &structure;
public:

    Intersection(const Vector3 &point, Structure &structure);

    const Vector3 &getPoint() const;

    const Structure &getStructure() const;

    void setPoint(const Vector3 &point);

    void setStructure(const Structure &structure);

    void setStructure1(Structure &structure);


};


#endif //FOTO_INTERSECTION_H

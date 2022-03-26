//
// Created by Witek on 08.03.2022.
//

#ifndef FOTO_STRUCTURE_H
#define FOTO_STRUCTURE_H


#include <vector>
#include "../../Vector3/Vector3.h"
#include "../../Ray/Ray.h"

class Structure {
    virtual std::vector<Vector3> intersections(Ray ray) const = 0;


};


#endif //FOTO_STRUCTURE_H

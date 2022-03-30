//
// Created by Witek on 30.03.2022.
//

#ifndef FOTO_TRIANGLE_H
#define FOTO_TRIANGLE_H


#include "../Structure/Structure.h"

class Triangle: public Structure {
private:
    Vector3 a,b,c;
public:
    std::vector<Vector3> intersections(Ray ray) const override;

};


#endif //FOTO_TRIANGLE_H

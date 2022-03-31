//
// Created by Witek on 30.03.2022.
//

#ifndef FOTO_TRIANGLE_H
#define FOTO_TRIANGLE_H


#include "../Structure/Structure.h"
#include "../Plane/Plane.h"

class Triangle: public Structure {
private:
    Vector3 a,b,c;
    Plane plane;
public:
    Triangle(const LightIntensity &color, const Vector3 &a, const Vector3 &b, const Vector3 &c, const Plane &plane);

    Triangle(const Vector3 &a, const Vector3 &b, const Vector3 &c, const Plane &plane);

    std::vector<Vector3> intersections(Ray ray) const override;

    const Vector3 &getA() const;

    void setA(const Vector3 &a);

    const Vector3 &getB() const;

    void setB(const Vector3 &b);

    const Vector3 &getC() const;

    void setC(const Vector3 &c);

    const Plane &getPlane() const;

    void setPlane(const Plane &plane);


};


#endif //FOTO_TRIANGLE_H

#include <iostream>
#include "vector3/Vector3.h"
#include "sphere/Sphere.h"
#include "plane/Plane.h"


int main() {
    std::cout << "Hello, World!" << std::endl;

    Vector3 sphereVector = Vector3(0, 0, 0);
    Vector3 rayVector = Vector3(0, 0, -20);

    //2
    Sphere sphere = Sphere(sphereVector, 10);
    //3
    Ray R1 = Ray(rayVector, Vector3(rayVector, sphereVector).getNormalized());
    //4
    Ray R2 = Ray(rayVector, Vector3(0, 20, 0).getNormalized());
    //5
    auto point3 = sphere.intersections(R1);
    auto point4 = sphere.intersections(R2);
    //6
    Ray R3 = Ray(Vector3(0, 50, 10), Vector3(0, -100, 0).getNormalized());
    auto point5 = sphere.intersections(R3);
    //7
//    Plane plane = Plane()
    //8

    return 0;
}

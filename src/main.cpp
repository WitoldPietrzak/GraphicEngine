#include <iostream>
#include <vector>
#include "Vector3/Vector3.h"
#include "Exceptions/InfiniteIntersectionException.h"
#include "Structures/Sphere/Sphere.h"
#include "Structures/Plane/Plane.h"
#include "Image/Image.h"
#include "Camera/Camera.h"
#include "Camera/Orto/OrthogonalCamera.h"
#include "Camera/Persp/PerspectiveCamera.h"
#include "Structures/LimitedPlane/LimitedPlane.h"
#include "Structures/Triangle/Triangle.h"

void readVector(const Vector3 &vector3) {
    std::cout << "[ " << vector3.getX() << " " << vector3.getY() << " " << vector3.getZ() << " ]" << std::endl;
}

void readVectorList(const std::vector<Vector3> &vectors) {
    if (vectors.empty()) {
        std::cout << "Empty \n";
        return;
    }
    for (const auto &vector: vectors) {
        readVector(vector);
    }
}

void task1() {
    Vector3 sphereVector = Vector3(0, 0, 0);
    Vector3 rayVector = Vector3(0, 0, -20);

    //2 Zdefiniować sferę S o środku w punkcie (0,0,0) i promieniu 10.
    Sphere S1 = Sphere(sphereVector, 10);
    //3 Zdefiniować promień R1 o początku w punkcie (0,0,-20) i skierowany w środek kuli.
    Ray R1 = Ray(rayVector, Vector3(rayVector, sphereVector).getNormalized());
    //4 Zdefiniować promień R2 o początku w tym samym punkcie, co R1, skierowany równolegle do osi Y.
    Ray R2 = Ray(rayVector, Vector3(0, 1, 0).getNormalized());
    //5  Sprawdzić, czy istnieje przecięcie sfery S z promieniami R1 oraz R2
    auto I1 = S1.intersections(R1);
    auto I2 = S1.intersections(R2);
    std::cout << "5: \n";
    std::cout << "R1: \n";
    readVectorList(I1);
    std::cout << "R2: \n";
    readVectorList(I2);

    //6 Proszę zdefiniować dowolny promień R3, tak aby przecinał on sferę S w dokładnie jednym punkcie. Podać współrzędne punktu przecięcia
    Ray R3 = Ray(Vector3(0, 50, 10), Vector3(0, -1, 0).getNormalized());
    auto I3 = S1.intersections(R3);
    std::cout << "6: \n";
    std::cout << "R3: \n";
    readVectorList(I3);

    //7 Proszę zdefiniować płaszczyznę P przechodzącą przez punkt (0,0,0), której wektor normalny tworzy kąt 45 stopni z osiami Y i Z.
    Plane P1 = Plane(Vector3(0, 0.5, 0.5), Vector3(0, 0, 0));

    //8 Proszę znaleźć punkt przecięcia płaszczyzny P z promieniem R2.
    std::cout << "8: \n";
    std::cout << "R2: \n";
    auto I4 = P1.intersections(R2);
    readVectorList(I4);


    // Dodatkowe testy

    // Nieskonczone przeciecie
    std::cout << "Infinite intersections test: \n";
    auto P2 = Plane(Vector3(0, 1, 0), Vector3(0, 0, 0));
    auto R4 = Ray(Vector3(0, 0, 0), Vector3(0, 0, 1));
    try {
        auto I5 = P2.intersections(R4);
    } catch (InfiniteIntersectionException &exception) {
        std::cout << "Infinite intersections exception occured \n";
    }

    // Promien z poczatkiem w srodku S1
    auto R5 = Ray(Vector3(0, 0, 0), Vector3(1, 0, 0));
    auto I6 = S1.intersections(R5);
    std::cout << "Ray from inside S1: \n";
    readVectorList(I6);
}

void task2() {
    Structure *sphere = new Sphere(Vector3(0, 0, 0), 80, LightIntensity::BLUE());
    Structure *sphere2 = new Sphere(Vector3(-120, 0, -200), 80, LightIntensity::RED());

    OrthogonalCamera ort = OrthogonalCamera(Vector3(0, 0, 400), Vector3(0, 0, -1), Vector3(0, 1, 0), 600, 600,
                                            OrthogonalSampler(4));
    PerspectiveCamera perspectiveCamera = PerspectiveCamera(Vector3(0, 0, 400), Vector3(0, 0, -1), Vector3(0, 1, 0),
                                                            400, 400, 400, PerspectiveSampler(4));
    Scene scene = Scene();
    scene.setBackgroundColor(LightIntensity::BLACK());
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            LightIntensity color;
            if(j == 5){
                color = LightIntensity(51*i,0,0);
            }
            if(j == 4){
                color = LightIntensity(0,51*i,0);
            }
            if(j == 3){
                color = LightIntensity(0,0,51*i);
            }
            if(j == 2){
                color = LightIntensity(255,0,51*i);
            }
            if(j == 1){
                color = LightIntensity(0,255,51*i);
            }
            if(j == 0){
                color = LightIntensity(255,255,51*i);
            }
            scene.addStructure(new LimitedPlane(Vector3(0, 0, -1), Vector3(0, 0, -200), color,
                                                Vector3(-300 + (j * 100), 300 - (i * 100), -200),
                                                Vector3(-200 + (j * 100), 300 - (i * 100) , -200),
                                                Vector3(-300 + (j * 100), 200 - (i * 100), -200),
                                                Vector3(-200 + (j * 100), 200 - (i * 100), -200)));
        }
    }
    scene.addStructure(sphere);
    scene.addStructure(sphere2);
    auto test2 = ort.renderScene(scene, 500, 500);
    auto test3 = perspectiveCamera.renderScene(scene,500,500);
    test2.save("orthogonal.bmp");
    test3.save("perspective.bmp");



}

void task3() {
    Structure *sphere = new Sphere(Vector3(0, 0, 0), 80, LightIntensity::BLUE());
    Structure *sphere2 = new Sphere(Vector3(-120, 0, -200), 80, LightIntensity::RED());
    Structure *triangle = new Triangle(Vector3(-50,-50,0),Vector3(50,-50,0),Vector3(0,50,0),LightIntensity::WHITE());
    Structure *triangle2 = new Triangle(Vector3(0,-80,0),Vector3(90,-100,0),Vector3(50,20,0),LightIntensity::RED());

    OrthogonalCamera ort = OrthogonalCamera(Vector3(0, 0, -400), Vector3(0, 0, 1), Vector3(0, 1, 0), 600, 600,
                                            OrthogonalSampler(4));
    PerspectiveCamera perspectiveCamera = PerspectiveCamera(Vector3(0, 0, -400), Vector3(0, 0, 1), Vector3(0, 1, 0),
                                                            400, 400, 400, PerspectiveSampler(4));
    Scene scene = Scene();
    scene.setBackgroundColor(LightIntensity::BLACK());
//    scene.addStructure(sphere);
//    scene.addStructure(sphere2);
    scene.addStructure(triangle);
    scene.addStructure(triangle2);
    auto test2 = ort.renderScene(scene, 500, 500);
    auto test3 = perspectiveCamera.renderScene(scene,500,500);
    test2.save("orthogonal-triangle.bmp");
    test3.save("perspective-triangle.bmp");



}

int main() {
    task3();
    return 0;
}

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
#include "ObjParser/ObjParser.h"
#include "Light/SurfaceLight/SurfaceLight.h"
#include "Quaternion/Quaternion.h"
#include <cmath>

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

//void task1() {
//    Vector3 sphereVector = Vector3(0, 0, 0);
//    Vector3 rayVector = Vector3(0, 0, -20);
//
//    //2 Zdefiniować sferę S o środku w punkcie (0,0,0) i promieniu 10.
//    Sphere S1 = Sphere(sphereVector, 10);
//    //3 Zdefiniować promień R1 o początku w punkcie (0,0,-20) i skierowany w środek kuli.
//    Ray R1 = Ray(rayVector, Vector3(rayVector, sphereVector).getNormalized());
//    //4 Zdefiniować promień R2 o początku w tym samym punkcie, co R1, skierowany równolegle do osi Y.
//    Ray R2 = Ray(rayVector, Vector3(0, 1, 0).getNormalized());
//    //5  Sprawdzić, czy istnieje przecięcie sfery S z promieniami R1 oraz R2
//    auto I1 = S1.intersections(R1);
//    auto I2 = S1.intersections(R2);
//    std::cout << "5: \n";
//    std::cout << "R1: \n";
//    readVectorList(I1);
//    std::cout << "R2: \n";
//    readVectorList(I2);
//
//    //6 Proszę zdefiniować dowolny promień R3, tak aby przecinał on sferę S w dokładnie jednym punkcie. Podać współrzędne punktu przecięcia
//    Ray R3 = Ray(Vector3(0, 50, 10), Vector3(0, -1, 0).getNormalized());
//    auto I3 = S1.intersections(R3);
//    std::cout << "6: \n";
//    std::cout << "R3: \n";
//    readVectorList(I3);
//
//    //7 Proszę zdefiniować płaszczyznę P przechodzącą przez punkt (0,0,0), której wektor normalny tworzy kąt 45 stopni z osiami Y i Z.
//    Plane P1 = Plane(Vector3(0, 0.5, 0.5), Vector3(0, 0, 0));
//
//    //8 Proszę znaleźć punkt przecięcia płaszczyzny P z promieniem R2.
//    std::cout << "8: \n";
//    std::cout << "R2: \n";
//    auto I4 = P1.intersections(R2);
//    readVectorList(I4);
//
//
//    // Dodatkowe testy
//
//    // Nieskonczone przeciecie
//    std::cout << "Infinite intersections test: \n";
//    auto P2 = Plane(Vector3(0, 1, 0), Vector3(0, 0, 0));
//    auto R4 = Ray(Vector3(0, 0, 0), Vector3(0, 0, 1));
//    try {
//        auto I5 = P2.intersections(R4);
//    } catch (InfiniteIntersectionException &exception) {
//        std::cout << "Infinite intersections exception occured \n";
//    }
//
//    // Promien z poczatkiem w srodku S1
//    auto R5 = Ray(Vector3(0, 0, 0), Vector3(1, 0, 0));
//    auto I6 = S1.intersections(R5);
//    std::cout << "Ray from inside S1: \n";
//    readVectorList(I6);
//}

//void task2() {
//    Structure *sphere = new Sphere(Vector3(0, 0, 0), 80, LightIntensity::BLUE());
//    Structure *sphere2 = new Sphere(Vector3(-120, 0, -200), 80, LightIntensity::RED());
//
//    OrthogonalCamera ort = OrthogonalCamera(Vector3(0, 0, 400), Vector3(0, 0, -1), Vector3(0, 1, 0), 600, 600,
//                                            OrthogonalSampler(4));
//    PerspectiveCamera perspectiveCamera = PerspectiveCamera(Vector3(0, 0, 400), Vector3(0, 0, -1), Vector3(0, 1, 0),
//                                                            400, 400, 400, PerspectiveSampler(4));
//    Scene scene = Scene();
//    scene.setBackgroundColor(LightIntensity::BLACK());
//    for (int i = 0; i < 6; i++) {
//        for (int j = 0; j < 6; j++) {
//            LightIntensity color;
//            if(j == 5){
//                color = LightIntensity(51*i,0,0);
//            }
//            if(j == 4){
//                color = LightIntensity(0,51*i,0);
//            }
//            if(j == 3){
//                color = LightIntensity(0,0,51*i);
//            }
//            if(j == 2){
//                color = LightIntensity(255,0,51*i);
//            }
//            if(j == 1){
//                color = LightIntensity(0,255,51*i);
//            }
//            if(j == 0){
//                color = LightIntensity(255,255,51*i);
//            }
//            scene.addStructure(new LimitedPlane(Vector3(0, 0, -1), Vector3(0, 0, -200), color,
//                                                Vector3(-300 + (j * 100), 300 - (i * 100), -200),
//                                                Vector3(-200 + (j * 100), 300 - (i * 100) , -200),
//                                                Vector3(-300 + (j * 100), 200 - (i * 100), -200),
//                                                Vector3(-200 + (j * 100), 200 - (i * 100), -200)));
//        }
//    }
//    scene.addStructure(sphere);
//    scene.addStructure(sphere2);
//    auto test2 = ort.renderScene(scene, 500, 500);
//    auto test3 = perspectiveCamera.renderScene(scene,500,500);
//    test2.save("orthogonal.bmp");
//    test3.save("perspective.bmp");
//
//
//
//}

//void task3_test() {
//    Structure *sphere = new Sphere(Vector3(0, 0, 0), 80, LightIntensity::BLUE());
//    Structure *sphere2 = new Sphere(Vector3(-120, 0, -200), 80, LightIntensity::RED());
//    Structure *triangle = new Triangle(Vector3(-50,-50,0),Vector3(50,-50,0),Vector3(0,50,0),LightIntensity::WHITE());
//    Structure *triangle2 = new Triangle(Vector3(0,-80,0),Vector3(90,-100,0),Vector3(50,20,0),LightIntensity::RED());
//
//    OrthogonalCamera ort = OrthogonalCamera(Vector3(0, 0, -400), Vector3(0, 0, 1), Vector3(0, 1, 0), 600, 600,
//                                            OrthogonalSampler(4));
//    PerspectiveCamera perspectiveCamera = PerspectiveCamera(Vector3(0, 0, -400), Vector3(0, 0, 1), Vector3(0, 1, 0),
//                                                            400, 400, 400, PerspectiveSampler(4));
//    Scene scene = Scene();
//    scene.setBackgroundColor(LightIntensity::BLACK());
////    scene.addStructure(sphere);
////    scene.addStructure(sphere2);
//    scene.addStructure(triangle);
//    scene.addStructure(triangle2);
//    auto test2 = ort.renderScene(scene, 500, 500);
//    auto test3 = perspectiveCamera.renderScene(scene,500,500);
//    test2.save("orthogonal-triangle.bmp");
//    test3.save("perspective-triangle.bmp");
//
//
//
//}

//void task3() {
//
//    ObjParser parser = ObjParser();
//    Structure *mesh = parser.parse("object.obj");
//
//    OrthogonalCamera ort = OrthogonalCamera(Vector3(0, 0, -4), Vector3(0, 0, 1), Vector3(0, 1, 0), 4, 4,
//                                            OrthogonalSampler(4));
//    PerspectiveCamera perspectiveCamera = PerspectiveCamera(Vector3(0, 0, -4), Vector3(0, 0, 1), Vector3(0, 1, 0),
//                                                            4, 4, 4, PerspectiveSampler(4));
//    PerspectiveCamera perspectiveCamera2 = PerspectiveCamera(Vector3(-sqrtf(2), 2, -sqrtf(2)), Vector3(1, -1, 1).getNormalized(), Vector3(0, 1, 0),
//                                                            4, 4, 4, PerspectiveSampler(4));
//    Scene scene = Scene();
//    mesh->setColor(LightIntensity::RED());
//    scene.addStructure(mesh);
//    scene.setBackgroundColor(LightIntensity::BLACK());
//    auto test2 = ort.renderScene(scene, 500, 500);
//    auto test3 = perspectiveCamera.renderScene(scene,500,500);
//    auto test4 = perspectiveCamera2.renderScene(scene,500,500);
//    test2.save("orthogonal-mesh.bmp");
//    test3.save("perspective-mesh.bmp");
//    test4.save("perspective-mesh-angle.bmp");
//
//
//
//}

void task3(std::string name) {

    ObjParser parser = ObjParser();
    Structure *mesh = parser.parse(name);
    Structure *sphere = new Sphere(Vector3(-0.75,0.5,0.5),0.2,LightIntensity::RED());
    Structure *plane = new Plane(Vector3(0,0,1), Vector3(0,0,10));
    Structure *plane2 = new Plane(Vector3(0,-1,0), Vector3(0,0,0));
    plane->setColor(LightIntensity(255,255,255));
    plane2->setColor(LightIntensity(0,255,0));
    auto *light = new PointLight(LightIntensity(255,255,255), Vector3(0.5,1.5,-2));
    auto *light2 = new SurfaceLight(Vector3(0.5,1.5, -3), Vector3(3,0,0),Vector3(0,1,0),2);

    OrthogonalCamera orthogonalFront = OrthogonalCamera(Vector3(0, 0, -7), Vector3(0, 0, 1), Vector3(0, 1, 0), 8, 8,
                                                        OrthogonalSampler(4));

    OrthogonalCamera orthogonalAngle = OrthogonalCamera(Vector3(-sqrtf(4), 2, -sqrtf(4)), Vector3(1, -1, 1).getNormalized(), Vector3(0, 1, 0), 4, 4,
                                                        OrthogonalSampler(4));

    PerspectiveCamera perspectiveCamera = PerspectiveCamera(Vector3(0, 0, -4), Vector3(0, 0, 1), Vector3(0, 1, 0),
                                                            4, 6, 6, PerspectiveSampler(4));

    PerspectiveCamera perspectiveCamera2 = PerspectiveCamera(Vector3(2, 1, -4), (Vector3(0, 0.5, 0)-Vector3(2, 1, -4)).getNormalized(), Vector3(0, 1, 0),
                                                             4, 8, 8, PerspectiveSampler(4));
    Scene scene = Scene();
    mesh->setColor(LightIntensity::BLUE());
    scene.addStructure(mesh);
    scene.addStructure(sphere);
    scene.addStructure(plane);
    scene.addStructure(plane2);
    scene.setBackgroundColor(LightIntensity::WHITE());
    scene.setAmbient(LightIntensity(255,255,255));
    scene.addLightSource(light);
//    scene.addLightSource(light2);
//    auto test2 = orthogonalFront.renderScene(scene, 1000, 1000);
//    auto test3 = perspectiveCamera.renderScene(scene,500,500);
    auto test4 = perspectiveCamera2.renderScene(scene,500,500);
//    auto test5 = orthogonalAngle.renderScene(scene,500,500);
//    test2.save("orthogonal-custom.bmp");
//    test5.save("orthogonal-custom-angle.bmp");
//    test3.save("perspective-custom.bmp");
    test4.save("perspective-custom-angle.bmp");



}

void task3_teapot() {

    ObjParser parser = ObjParser();
    Structure *mesh = parser.parse("teapot.obj");

    OrthogonalCamera ort = OrthogonalCamera(Vector3(0, 1, -4), Vector3(0, 0, 1), Vector3(0, 1, 0), 5, 5,
                                            OrthogonalSampler(0));
    PerspectiveCamera perspectiveCamera = PerspectiveCamera(Vector3(0, 0, -4), Vector3(0, 0, 1), Vector3(0, 1, 0),
                                                            4, 4, 4, PerspectiveSampler(0));
    PerspectiveCamera perspectiveCamera2 = PerspectiveCamera(Vector3(-sqrtf(2), 2, -sqrtf(2)), Vector3(1, -1, 1).getNormalized(), Vector3(0, 1, 0),
                                                             4, 4, 4, PerspectiveSampler(0));
    Scene scene = Scene();
    mesh->setColor(LightIntensity::RED());
    scene.addStructure(mesh);
    scene.setBackgroundColor(LightIntensity::BLACK());
    scene.setAmbient(LightIntensity(255,255,255));
    auto test2 = ort.renderScene(scene, 256, 256);
//    auto test3 = perspectiveCamera.renderScene(scene,256,256);
//    auto test4 = perspectiveCamera2.renderScene(scene,256,256);
    test2.save("orthogonal-teapot.bmp");
//    test3.save("perspective-teapot.bmp");
//    test4.save("perspective-teapot-angle.bmp");



}


void task5() {


    Structure *sphere = new Sphere(Vector3(-0.75,0.2,0.3),0.2,LightIntensity::RED());
    Structure *plane = new Plane(Vector3(0,0,1), Vector3(0,0,10));
    Structure *plane2 = new Plane(Vector3(0,-1,0), Vector3(0,0,0));
    auto *limitedPlane = new LimitedPlane(Vector3(-3.7,1.5,0.5),Vector3(2.2,0,0),Vector3(0,-1.5,0));
    limitedPlane->switchSide();
    plane->setColor(LightIntensity(255,255,255));
    plane2->setColor(LightIntensity(0,255,0));

    std::string textureFileName = "tex1.bmp";
    std::string textureFileName2 = "tex2.bmp";
    auto mat = sphere->getMaterial();
    mat.setTexture(Image::load(textureFileName));
    mat.setMaterialType(MaterialType::diffuse_texture);

    auto mat2 = limitedPlane->getMaterial();
    mat2.setTexture(Image::load(textureFileName2));
    mat2.setMaterialType(MaterialType::diffuse_texture);

    sphere->setMaterial(mat);
    limitedPlane->setMaterial(mat2);
    limitedPlane->setColor(LightIntensity::RED());

    auto *light = new PointLight(LightIntensity(255,255,255), Vector3(0.5,1.5,-2));

    PerspectiveCamera perspectiveCamera = PerspectiveCamera(Vector3(0, 0, -4), Vector3(0, 0, 1), Vector3(0, 1, 0),
                                                            4, 6, 6, PerspectiveSampler(4));
    PerspectiveCamera perspectiveCamera2 = PerspectiveCamera(Vector3(1, 1, -1), (Vector3(0, 0.5, 0)-Vector3(1, 1, -1)).getNormalized(), Vector3(0, 1, 0),
                                                             4, 8, 8, PerspectiveSampler(2));
    Scene scene = Scene();
    scene.addStructure(sphere);
    scene.addStructure(limitedPlane);
    scene.addStructure(plane);
    scene.addStructure(plane2);
    scene.setBackgroundColor(LightIntensity::BLUE());
    scene.setAmbient(LightIntensity(255,255,255));
    scene.addLightSource(light);
//    auto test3 = perspectiveCamera.renderScene(scene,500,500);
    auto test4 = perspectiveCamera2.renderScene(scene,1024,1024);
//    test3.save("perspective-custom.bmp");
    test4.save("perspective-custom-angle-texture-5.bmp");



}

void task6() {


    Structure *sphere2 = new Sphere(Vector3(-1.3,1.5,1.5),1.5,LightIntensity::RED());
    Structure *sphere = new Sphere(Vector3(2,1.5,1),1.5,LightIntensity::RED());

    sphere->setColor(LightIntensity::RED());
    sphere2->setColor(LightIntensity::RED());

    //Dół
    auto *limitedPlane1 = new LimitedPlane(Vector3(-5,0,5),Vector3(10,0,0),Vector3(0,0,-10));

    //Góra
    auto *limitedPlane2_1 = new LimitedPlane(Vector3(-5,10,5),Vector3(10,0,0),Vector3(0,0,-4.5));
    auto *limitedPlane2_2 = new LimitedPlane(Vector3(-5,10,-0.5),Vector3(10,0,0),Vector3(0,0,-4.5));
    auto *limitedPlane2_3 = new LimitedPlane(Vector3(-5,10,0.5),Vector3(4.5,0,0),Vector3(0,0,-1));
    auto *limitedPlane2_4 = new LimitedPlane(Vector3(0.5,10,0.5),Vector3(4.5,0,0),Vector3(0,0,-1));
    limitedPlane1->switchSide();

    //Lewo prawo
    auto *limitedPlane3 = new LimitedPlane(Vector3(-5,0,5),Vector3(0,0,-10),Vector3(0,10,0));
    auto *limitedPlane4 = new LimitedPlane(Vector3(5,0,5),Vector3(0,0,-10),Vector3(0,10,0));
    limitedPlane3->switchSide();

    // Przód tył
    auto *limitedPlane5 = new LimitedPlane(Vector3(-5,0,5),Vector3(10,0,0),Vector3(0,10,0));
    auto *limitedPlane6 = new LimitedPlane(Vector3(-5,0,-5),Vector3(10,0,0),Vector3(0,10,0));
    limitedPlane6->switchSide();

    limitedPlane1->setColor(LightIntensity(255,255,255));
    limitedPlane2_1->setColor(LightIntensity(255,255,255));
    limitedPlane2_2->setColor(LightIntensity(255,255,255));
    limitedPlane2_3->setColor(LightIntensity(255,255,255));
    limitedPlane2_4->setColor(LightIntensity(255,255,255));

    limitedPlane3->setColor(LightIntensity::RED());
    limitedPlane4->setColor(LightIntensity::BLUE());

    limitedPlane5->setColor(LightIntensity::YELLOW());
    limitedPlane6->setColor(LightIntensity::GREEN());

    auto mat = sphere->getMaterial();
    mat.setMaterialType(MaterialType::refraction);
    mat.setRefractionIndex(1.83);

    auto mat2 = sphere2->getMaterial();
    mat2.setMaterialType(MaterialType::mirror);

//    sphere->setMaterial(mat);
//    sphere2->setMaterial(mat2);

//    auto *light = new PointLight(LightIntensity(2550,2550,2550), Vector3(0,10,0));
    auto *softLight = new SurfaceLight(Vector3(-0.5,10.1,-0.5),Vector3(1,0,0),Vector3(0,0,1),4,LightIntensity(155,155,155));
//    light->setLinAt(0.5);

    PerspectiveCamera perspectiveCamera2 = PerspectiveCamera(Vector3(0, 5, -4.5), Vector3(0, 0, 1).getNormalized(), Vector3(0, 1, 0),
                                                             1, 4, 4, PerspectiveSampler(1));
    Scene scene = Scene();
    scene.addStructure(sphere);
    scene.addStructure(sphere2);
    scene.addStructure(limitedPlane1);
    scene.addStructure(limitedPlane2_1);
    scene.addStructure(limitedPlane2_2);
    scene.addStructure(limitedPlane2_3);
    scene.addStructure(limitedPlane2_4);
    scene.addStructure(limitedPlane3);
    scene.addStructure(limitedPlane4);
    scene.addStructure(limitedPlane5);
    scene.addStructure(limitedPlane6);

    scene.setBackgroundColor(LightIntensity::WHITE());
    scene.setAmbient(LightIntensity(255,255,255));
    scene.addLightSource(softLight);
    auto test4 = perspectiveCamera2.renderScene(scene,1024,1024);
    test4.save("task6-complete-soft.bmp");



}

void distributedRTSoftShadows() {


    Structure *sphere = new Sphere(Vector3(0,1,0),1,LightIntensity::RED());

    sphere->setColor(LightIntensity::RED());


    auto *limitedPlane1 = new Plane(Vector3(0,1,0),Vector3(0,0,0));
    limitedPlane1->switchSide();

    auto *limitedPlane2 =  new LimitedPlane(Vector3(-90,0,30),Vector3(180,0,0),Vector3(0,90,0));


    limitedPlane1->setColor(LightIntensity(255,255,255));

    std::string textureFileName = "background.bmp";
    auto mat = limitedPlane2->getMaterial();
    mat.setTexture(Image::load(textureFileName));
    mat.setMaterialType(MaterialType::diffuse_texture);
    limitedPlane2->setMaterial(mat);

    auto *light = new PointLight(LightIntensity(2550,2550,2550), Vector3(0,6,2));
    auto *softLight = new SurfaceLight(Vector3(-0.5,5.5,2),Vector3(1,0,0),Vector3(0,1,0),8,LightIntensity(2550/64,2550/64,2550/64));
    auto *distributedLight = new DistributedLight(LightIntensity(2550,2550,2550),Vector3(-0.5,5.5,2),Vector3(1,0,0),Vector3(0,1,0));

    PerspectiveCamera perspectiveCamera = PerspectiveCamera(Vector3(0, 5, -6), Vector3(0, 0, 1).getNormalized(), Vector3(0, 1, 0),
                                                             1, 4, 4, PerspectiveSampler(1));
    Scene scene = Scene();
    scene.addStructure(sphere);
    scene.addStructure(limitedPlane1);
    scene.addStructure(limitedPlane2);

    scene.setBackgroundColor(LightIntensity::BLACK());
    scene.setAmbient(LightIntensity(255,255,255));
    scene.addLightSource(softLight);
    auto test4 = perspectiveCamera.renderScene(scene,512,512);
    test4.save("shadow-soft-64-points.bmp");



}

void distributedRTDepthOfField() {


    Structure *sphere = new Sphere(Vector3(0,0.6,-2.2),0.6,LightIntensity::RED());
    Structure *sphere2 = new Sphere(Vector3(7,1.5,4),1.5,LightIntensity::BLUE());
    Structure *sphere3 = new Sphere(Vector3(15,1.5,7),1.5,LightIntensity::YELLOW());

    sphere->setColor(LightIntensity::RED());


    auto *limitedPlane1 = new Plane(Vector3(0,1,0),Vector3(0,0,0));
    limitedPlane1->switchSide();

    auto *limitedPlane2 =  new LimitedPlane(Vector3(-90,0,30),Vector3(180,0,0),Vector3(0,90,0));


    limitedPlane1->setColor(LightIntensity(255,255,255));

    std::string textureFileName = "background.bmp";
    auto mat = limitedPlane2->getMaterial();
    mat.setTexture(Image::load(textureFileName));
    mat.setMaterialType(MaterialType::diffuse_texture);
    limitedPlane2->setMaterial(mat);

    auto *light = new PointLight(LightIntensity(2550,2550,2550), Vector3(-1.5,2,-3));

    PerspectiveCamera perspectiveCamera = PerspectiveCamera(Vector3(0, 1, -3), Vector3(0, 0, 1).getNormalized(), Vector3(0, 1, 0),
                                                            10, 40, 40, PerspectiveSampler(1));
    perspectiveCamera.setLensRadius(0.04);
    Scene scene = Scene();
    scene.addStructure(sphere);
    scene.addStructure(sphere2);
    scene.addStructure(sphere3);
    scene.addStructure(limitedPlane1);
    scene.addStructure(limitedPlane2);

    scene.setBackgroundColor(LightIntensity::BLACK());
    scene.setAmbient(LightIntensity(255,255,255));
    scene.addLightSource(light);
    auto test4 = perspectiveCamera.renderScene(scene,512,512);
    test4.save("depth-far.bmp");



}

void distributedRTMovement() {


    Structure *sphere = new Sphere(Vector3(-1,1.5,0),1.5,LightIntensity::RED());
    Structure *sphere2 = new Sphere(Vector3(7,6,4),1.5,LightIntensity::BLUE());
    Structure *sphere3 = new Sphere(Vector3(15,1.5,7),1.5,LightIntensity::YELLOW());

    sphere->setMovemment(Vector3(1,0,0));
    sphere2->setMovemment(Vector3(0,-4.5,0));


    sphere->setColor(LightIntensity::RED());


    auto *limitedPlane1 = new Plane(Vector3(0,1,0),Vector3(0,0,0));
    limitedPlane1->switchSide();

    auto *limitedPlane2 =  new LimitedPlane(Vector3(-90,0,30),Vector3(180,0,0),Vector3(0,90,0));


    limitedPlane1->setColor(LightIntensity(255,255,255));

    std::string textureFileName = "background.bmp";
    auto mat = limitedPlane2->getMaterial();
    mat.setTexture(Image::load(textureFileName));
    mat.setMaterialType(MaterialType::diffuse_texture);
    limitedPlane2->setMaterial(mat);

    auto *light = new PointLight(LightIntensity(255,255,255), Vector3(-1.5,2,-3));

    PerspectiveCamera perspectiveCamera = PerspectiveCamera(Vector3(0, 1, -3), Vector3(0, 0, 1).getNormalized(), Vector3(0, 1, 0),
                                                            10, 40, 40, PerspectiveSampler(1));
    Scene scene = Scene();
    scene.addStructure(sphere);
    scene.addStructure(sphere2);
    scene.addStructure(sphere3);
    scene.addStructure(limitedPlane1);
    scene.addStructure(limitedPlane2);

    scene.setBackgroundColor(LightIntensity::BLACK());
    scene.setAmbient(LightIntensity(255,255,255));
    scene.addLightSource(light);
    auto test4 = perspectiveCamera.renderScene(scene,512,512);
    test4.save("movement-8-samples.bmp");



}

void distributedRTAntiAliasing() {


    Structure *sphere = new Sphere(Vector3(0,0.6,-2.2),0.6,LightIntensity::RED());
    Structure *sphere2 = new Sphere(Vector3(7,1.5,4),1.5,LightIntensity::BLUE());
    Structure *sphere3 = new Sphere(Vector3(15,1.5,7),1.5,LightIntensity::YELLOW());

    sphere->setColor(LightIntensity::RED());


    auto *limitedPlane1 = new Plane(Vector3(0,1,0),Vector3(0,0,0));
    limitedPlane1->switchSide();

    auto *limitedPlane2 =  new LimitedPlane(Vector3(-90,0,30),Vector3(180,0,0),Vector3(0,90,0));


    limitedPlane1->setColor(LightIntensity(255,255,255));

    std::string textureFileName = "background.bmp";
    auto mat = limitedPlane2->getMaterial();
    mat.setTexture(Image::load(textureFileName));
    mat.setMaterialType(MaterialType::diffuse_texture);
    limitedPlane2->setMaterial(mat);

    auto *light = new PointLight(LightIntensity(2550,2550,2550), Vector3(-1.5,2,-3));

    auto sampler = PerspectiveSampler(3);
    sampler.setSamplingType(SamplingType::DistributedSampling);
    sampler.setPixelSampleCount(2);
    PerspectiveCamera perspectiveCamera = PerspectiveCamera(Vector3(0, 1, -3), Vector3(0, 0, 1).getNormalized(), Vector3(0, 1, 0),
                                                            10, 40, 40, sampler);
    perspectiveCamera.setLensRadius(0.04);
    Scene scene = Scene();
    scene.addStructure(sphere);
    scene.addStructure(sphere2);
    scene.addStructure(sphere3);
    scene.addStructure(limitedPlane1);
    scene.addStructure(limitedPlane2);

    scene.setBackgroundColor(LightIntensity::BLACK());
    scene.setAmbient(LightIntensity(255,255,255));
    scene.addLightSource(light);
    auto test4 = perspectiveCamera.renderScene(scene,512,512);
    test4.save("antialiasing-distributed-samples-2.bmp");



}
int main() {
    distributedRTAntiAliasing();
    return 0;
}

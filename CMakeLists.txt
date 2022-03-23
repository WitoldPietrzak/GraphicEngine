cmake_minimum_required(VERSION 3.4)
project(foto)

set(CMAKE_CXX_STANDARD 14)
add_executable(foto src/main.cpp src/vector3/Vector3.cpp src/vector3/Vector3.h src/vector2/Vector2.cpp src/vector2/Vector2.h src/sphere/Sphere.cpp src/sphere/Sphere.h src/plane/Plane.cpp src/plane/Plane.h src/structure/Structure.cpp src/structure/Structure.h src/point3/Point3.cpp src/point3/Point3.h src/Exceptions/DivisionException.cpp src/Exceptions/DivisionException.h src/ray/Ray.cpp src/ray/Ray.h src/Exceptions/InfiniteIntersectionException.cpp src/Exceptions/InfiniteIntersectionException.h src/LightIntensity/LightIntensity.cpp src/LightIntensity/LightIntensity.h)

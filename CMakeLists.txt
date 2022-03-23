cmake_minimum_required(VERSION 3.4)
project(foto)

set(CMAKE_CXX_STANDARD 14)
add_executable(foto src/main.cpp src/Vector3/Vector3.cpp src/Vector3/Vector3.h src/Vectors/vector2/Vector2.cpp src/Vectors/vector2/Vector2.h src/Structures/Sphere/Sphere.cpp src/Structures/Sphere/Sphere.h src/Structures/Plane/Plane.cpp src/Structures/Plane/Plane.h src/Structures/Structure/Structure.cpp src/Structures/Structure/Structure.h src/point3/Point3.cpp src/point3/Point3.h src/Exceptions/DivisionException.cpp src/Exceptions/DivisionException.h src/Ray/Ray.cpp src/Ray/Ray.h src/Exceptions/InfiniteIntersectionException.cpp src/Exceptions/InfiniteIntersectionException.h src/LightIntensity/LightIntensity.cpp src/LightIntensity/LightIntensity.h)

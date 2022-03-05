cmake_minimum_required(VERSION 3.4)
project(foto)

set(CMAKE_CXX_STANDARD 14)

add_executable(foto src/main.cpp src/vector3/Vector3.cpp src/vector3/Vector3.h src/vector2/Vector2.cpp src/vector2/Vector2.h src/sphere/Sphere.cpp src/sphere/Sphere.h src/surface/Surface.cpp src/surface/Surface.h)

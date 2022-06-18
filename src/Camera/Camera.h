//
// Created by Witek on 27.03.2022.
//

#ifndef FOTO_CAMERA_H
#define FOTO_CAMERA_H


#include "../Vector3/Vector3.h"
#include "../Image/Image.h"
#include "../Scene/Scene.h"

class Camera {
protected:
    Vector3 position;
    Vector3 targetVector;
    Vector3 upVector;

public:

    Camera(const Vector3 &position, const Vector3 &targetVector, const Vector3 &upVector);

    virtual ~Camera();

    const Vector3 &getPosition() const;

    void setPosition(const Vector3 &position);

    const Vector3 getTargetVector() const;

    void setTargetVector(const Vector3 &targetVector);

    const Vector3 &getUpVector() const;

    void setUpVector(const Vector3 &upVector);

    virtual Image renderScene( Scene scene, int width, int height) = 0;

};


#endif //FOTO_CAMERA_H

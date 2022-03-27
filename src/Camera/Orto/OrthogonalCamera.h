//
// Created by Witek on 27.03.2022.
//

#ifndef FOTO_ORTHOGONALCAMERA_H
#define FOTO_ORTHOGONALCAMERA_H


#include "../Camera.h"

class OrthogonalCamera : public Camera {

private:
    float width;
    float height;
public:
    OrthogonalCamera(const Vector3 &position, const Vector3 &targetVector, const Vector3 &upVector, float width,
                     float height);

    Image renderScene(const Scene &scene, int width, int height) override;

    float getWidth() const;

    void setWidth(float width);

    float getHeight() const;

    void setHeight(float height);
};


#endif //FOTO_ORTHOGONALCAMERA_H

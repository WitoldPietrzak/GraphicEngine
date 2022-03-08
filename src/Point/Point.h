//
// Created by Witek on 08.03.2022.
//

#ifndef FOTO_POINT_H
#define FOTO_POINT_H


class Point {
protected:
    float x;
    float y;
    float z;

public:
    Point(float x, float y, float z);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getZ() const;

    void setZ(float z);
};


#endif //FOTO_POINT_H

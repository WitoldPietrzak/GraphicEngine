//
// Created by Witek on 08.03.2022.
//

#ifndef FOTO_POINT3_H
#define FOTO_POINT3_H


class Point3 {
protected:
    float x;
    float y;
    float z;

public:
    Point3(float x, float y, float z);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getZ() const;

    void setZ(float z);

    bool operator == (const Point3& obj);
    bool operator != (const Point3& obj);
};


#endif //FOTO_POINT3_H

//
// Created by Witek on 22.03.2022.
//

#ifndef FOTO_LIGHTINTENSITY_H
#define FOTO_LIGHTINTENSITY_H


#include <cstdint>

class LightIntensity {
private:
    int r, g, b;
public:

    LightIntensity(int r, int g, int b);

    LightIntensity();

    int getR() const;

    void setR(int r);

    int getG() const;

    void setG(int g);

    int getB() const;

    void setB(int b);

    void add(int R, int G, int B);


    void add(LightIntensity li);

    LightIntensity sum(LightIntensity &li);

    LightIntensity sum(int num);

    LightIntensity sub(LightIntensity &li);

    LightIntensity sub(int sum);

    LightIntensity div(float num) const;

    LightIntensity multiply(const float &num) const;

    LightIntensity multiply(LightIntensity &li);

    LightIntensity multiply(const LightIntensity &li);

    bool equals(LightIntensity &li);

    LightIntensity fitInRange();

    static LightIntensity BLACK();

    static LightIntensity WHITE();

    static LightIntensity RED();

    static LightIntensity GREEN();

    static LightIntensity BLUE();

    static LightIntensity YELLOW();

    LightIntensity operator+(LightIntensity &li);

    LightIntensity operator+(int num);

    LightIntensity operator-(LightIntensity &li);

    LightIntensity operator-(int num);

    LightIntensity operator*(float num);

    LightIntensity operator*(LightIntensity &li);
    LightIntensity operator*(const LightIntensity &li);

    void operator+=(LightIntensity li);

    LightIntensity operator-=(LightIntensity &li);

    LightIntensity operator*=(float num);

    LightIntensity operator/=(float num);

    bool operator==(LightIntensity &li);

    bool operator!=(LightIntensity &li);

    friend LightIntensity operator*(float num, LightIntensity &li);

    friend LightIntensity operator*(LightIntensity &li, float num);
};

#endif //FOTO_LIGHTINTENSITY_H

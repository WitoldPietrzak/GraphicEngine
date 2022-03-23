//
// Created by Witek on 22.03.2022.
//

#ifndef FOTO_LIGHTINTENSITY_H
#define FOTO_LIGHTINTENSITY_H


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

    void add(LightIntensity &li);

    LightIntensity sum(LightIntensity &li);

    LightIntensity sum(int num);

    LightIntensity sub(LightIntensity &li);

    LightIntensity sub(int sum);

    LightIntensity div(float num);

    LightIntensity multiply(float num);


    static LightIntensity BLACK();

    static LightIntensity WHITE();

    static LightIntensity RED();

    static LightIntensity GREEN();

    static LightIntensity BLUE();

    LightIntensity operator+(LightIntensity &li);

    LightIntensity operator+(int num);

    LightIntensity operator-(LightIntensity &li);

    LightIntensity operator-(int num);

    LightIntensity operator/(float num);

    void operator+=(LightIntensity &li);

    LightIntensity operator-=(LightIntensity &li);

    LightIntensity operator*=(float num);

    LightIntensity operator/=(float num);

    friend LightIntensity operator*(float num, LightIntensity &li);

    friend LightIntensity operator*(LightIntensity &li, float num);
};

#endif //FOTO_LIGHTINTENSITY_H

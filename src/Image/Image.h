//
// Created by Witek on 27.03.2022.
//

#ifndef FOTO_IMAGE_H
#define FOTO_IMAGE_H


#include "../LightIntensity/LightIntensity.h"
#include <string>

class Image {
private:
    int width;
    int height;
    LightIntensity *pixels;

public:
    Image(int width, int height);

    Image(Image const &image);

    LightIntensity *getPixels() const;

    LightIntensity getPixel(int width, int height);

    LightIntensity getPixel(float u, float v);

    void setPixel(int width, int height, LightIntensity color);

    int getWidth() const;

    int getHeight() const;

    void print(const std::string& filename);

    void save(const std::string& filename);

    static Image load(std::string& filename);

};


#endif //FOTO_IMAGE_H

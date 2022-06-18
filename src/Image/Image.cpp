//
// Created by Witek on 27.03.2022.
//

#include <iostream>
#include <fstream>
#include "Image.h"
#include "../../lib/bitmap/bitmap_image.hpp"


Image::Image(int width, int height) : width(width), height(height), pixels(new LightIntensity[width * height]) {}

Image::Image(Image const &image) {
    this->pixels = image.pixels;
    this->width = image.width;
    this->height = image.height;

}

LightIntensity *Image::getPixels() const {
    return pixels;
}

LightIntensity Image::getPixel(int width, int height) {
    return pixels[height * this->getWidth() + width];
}

void Image::setPixel(int width, int height, LightIntensity color) {
    pixels[height * this->getWidth() + width] = color;
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

void Image::print(const std::string &filename) {
    std::ofstream file;
    file.open(filename);
    for (int i = 0; i < this->getHeight(); i++) {
        for (int j = 0; j < this->getWidth(); j++) {
            auto pixel = this->getPixel(j, i);
            if (pixel.getR() == 0 && pixel.getG() == 0 && pixel.getB() == 0) {
                file << '0';
            } else {
                file << '1';
            }
        }
        file << '\n';
    }
    file.close();
}

void Image::save(const std::string &filename) {
    bitmap_image bmp = bitmap_image(this->getWidth(), this->getHeight());
    for (int i = 0; i < this->getHeight(); i++) {
        for (int j = 0; j < this->getWidth(); j++) {
            auto pixel = this->getPixel(j, i);
            bmp.set_pixel(j, i, pixel.getR(), pixel.getG(), pixel.getB());
        }
        bmp.save_image(filename);
    }

}

Image Image::load(std::string &filename) {
    bitmap_image bmp = bitmap_image(filename);
    Image image = Image(bmp.width(), bmp.height());
    for (int i = 0; i < bmp.height(); i++) {
        for (int j = 0; j < bmp.width(); j++) {

            auto pixel = bmp.get_pixel(j, i);
            image.setPixel(j, i, LightIntensity(pixel.red, pixel.green, pixel.blue));
        }
    }
    return image;
}

LightIntensity Image::getPixel(float u, float v) {
    int x = std::round((width - 1) * u);
    int y = std::round((height - 1) * v);
    return getPixel(x, y);
}

void Image::div(float number){
    for (int i = 0; i < this->getHeight(); i++) {
        for (int j = 0; j < this->getWidth(); j++) {
            auto pixel = this->getPixel(j, i);
            pixel = pixel.div(number);
            this->setPixel(j,i,pixel);
        }
}
}

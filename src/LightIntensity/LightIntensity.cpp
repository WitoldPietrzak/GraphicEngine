//
// Created by Witek on 22.03.2022.
//

#include <algorithm>
#include "LightIntensity.h"

LightIntensity::LightIntensity(int r, int g, int b) : r(r), g(g), b(b) {}

LightIntensity::LightIntensity() : r(0), g(0), b(0) {}

int LightIntensity::getR() const {
    return std::max(0, std::min(this->r, 255));
}

void LightIntensity::setR(int r) {
    this->r = r;
}

int LightIntensity::getG() const {
    return std::max(0, std::min(this->g, 255));;
}

void LightIntensity::setG(int g) {
    this->g = g;
}

int LightIntensity::getB() const {
    return std::max(0, std::min(this->b, 255));;
}

void LightIntensity::setB(int b) {
    this->b = b;
}

void LightIntensity::add(int R, int G, int B) {
    this->setR(this->getR() + R);
    this->setG(this->getG() + G);
    this->setB(this->getB() + B);
}

void LightIntensity::add(LightIntensity &li) {
    this->setR(this->getR() + li.getR());
    this->setG(this->getG() + li.getG());
    this->setB(this->getB() + li.getB());
}

LightIntensity LightIntensity::multiply(const float &num) const {
    return LightIntensity{(int) (r * num), (int) (g * num), (int) (b * num)};
}

LightIntensity LightIntensity::multiply(LightIntensity &li) {
    return {(int) (r * li.r / 255.0f), (int) (g * li.g / 255.0f), (int) (b * li.b / 255.0f)};
}

LightIntensity LightIntensity::multiply(const LightIntensity &li) {
    return {(int) (r * li.r / 255.0f), (int) (g * li.g / 255.0f), (int) (b * li.b / 255.0f)};
}

LightIntensity LightIntensity::div(float num) const {
    return LightIntensity{(int) (r / num), (int) (g / num), (int) (b / num)};
}

LightIntensity LightIntensity::BLACK() {
    return {0, 0, 0};
}

LightIntensity LightIntensity::WHITE() {
    return {255, 255, 255};
}

LightIntensity LightIntensity::RED() {
    return {255, 0, 0};
}

LightIntensity LightIntensity::GREEN() {
    return {0, 255, 0};
}

LightIntensity LightIntensity::BLUE() {
    return {0, 0, 255};
}

LightIntensity LightIntensity::YELLOW() {
    return LightIntensity(255, 255, 0);
}

LightIntensity LightIntensity::sum(LightIntensity &li) {
    return {this->getR() + li.getR(), this->getG() + li.getG(), this->getB() + li.getB()};
}

LightIntensity LightIntensity::sum(int num) {
    return {this->getR() + num, this->getG() + num, this->getB() + num};
}

LightIntensity LightIntensity::sub(LightIntensity &li) {
    return {this->getR() - li.getR(), this->getG() - li.getG(), this->getB() - li.getB()};
}

LightIntensity LightIntensity::sub(int num) {
    return {this->getR() - num, this->getG() - num, this->getB() - num};
}

LightIntensity LightIntensity::operator+(LightIntensity &li) {
    return sum(li);
}

LightIntensity LightIntensity::operator-(LightIntensity &li) {
    return sub(li);
}

LightIntensity LightIntensity::operator+(int num) {
    return sum(num);
}

LightIntensity LightIntensity::operator-(int num) {
    return sub(num);
}

void LightIntensity::operator+=(LightIntensity &li) {
    add(li);
}

bool LightIntensity::equals(LightIntensity &li) {
    return (this->r == li.r && this->g == li.g && this->b == li.b);
}

bool LightIntensity::operator==(LightIntensity &li) {
    return equals(li);
}

bool LightIntensity::operator!=(LightIntensity &li) {
    return !equals(li);
}

LightIntensity LightIntensity::operator*(float num) {
    return multiply(num);
}

LightIntensity LightIntensity::operator*(LightIntensity &li) {
    return multiply(li);
}

LightIntensity LightIntensity::operator*(const LightIntensity &li) {
    return multiply(li);
}



//
// Created by Witek on 22.03.2022.
//

#include "LightIntensity.h"

LightIntensity::LightIntensity(int r, int g, int b) : r(r), g(g), b(b) {}

LightIntensity::LightIntensity():r(0),g(0),b(0) {}

int LightIntensity::getR() const {
    return r;
}

void LightIntensity::setR(int r) {
    LightIntensity::r = r;
}

int LightIntensity::getG() const {
    return g;
}

void LightIntensity::setG(int g) {
    LightIntensity::g = g;
}

int LightIntensity::getB() const {
    return b;
}

void LightIntensity::setB(int b) {
    LightIntensity::b = b;
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



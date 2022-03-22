//
// Created by Witek on 22.03.2022.
//

#ifndef FOTO_INFINITEINTERSECTIONEXCEPTION_H
#define FOTO_INFINITEINTERSECTIONEXCEPTION_H


#include <exception>

class InfiniteIntersectionException : public std::exception {
    const char *what() const noexcept override {
        return "Infinite Intersections";
    }
};


#endif //FOTO_INFINITEINTERSECTIONEXCEPTION_H

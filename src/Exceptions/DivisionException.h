//
// Created by Witek on 08.03.2022.
//

#ifndef FOTO_DIVISIONEXCEPTION_H
#define FOTO_DIVISIONEXCEPTION_H

#include <exception>

class DivisionException : public std::exception {
    const char * what () const noexcept override {
        return "Division by zero";
    }
};


#endif //FOTO_DIVISIONEXCEPTION_H

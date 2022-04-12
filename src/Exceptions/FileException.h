//
// Created by witek on 12.04.2022.
//

#ifndef FOTO_FILEEXCEPTION_H
#define FOTO_FILEEXCEPTION_H


#include <exception>

class FileException : public std::exception {
    const char *what() const noexcept override {
        return "Could not read file";
    }
};


#endif //FOTO_FILEEXCEPTION_H

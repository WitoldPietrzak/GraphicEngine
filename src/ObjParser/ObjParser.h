//
// Created by Witek on 05.04.2022.
//

#ifndef FOTO_OBJPARSER_H
#define FOTO_OBJPARSER_H


#include <string>
#include "../Structures/Mesh/Mesh.h"

class ObjParser {
public:
    Mesh* parse(std::string filename);

};


#endif //FOTO_OBJPARSER_H

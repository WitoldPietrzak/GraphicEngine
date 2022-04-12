//
// Created by Witek on 05.04.2022.
//

#include <fstream>
#include <vector>
#include <sstream>
#include "ObjParser.h"
#include "../vector3/Vector3.h"
#include "../Structures/Mesh/Mesh.h"
#include "../Exceptions/FileException.h"
#include <algorithm>


void split(const std::string &str, char del, std::vector<std::string> &text) {
    std::string temp;
    for (char i: str) {
        if (i != del) {
            temp += i;
        } else {
            text.push_back(temp);
            temp = "";
        }
    }
    if(temp[temp.size()-1]!=del){
        text.push_back(temp);
    }
}

Mesh* ObjParser::parse(std::string filename) {
    std::ifstream in = std::ifstream(filename, std::ios::in);
    if (!in) {
        throw FileException();

    }
    Mesh* mesh = new Mesh();
    std::string line;
    std::vector<Vector3> vertices = std::vector<Vector3>();
    std::vector<Vector3> normals = std::vector<Vector3>();;

    while (std::getline(in, line)) {
        if (line.substr(0, 2) == "v ") {
            std::istringstream v = std::istringstream(line.substr(2));
            float x, y, z;
            v >> x;
            v >> y;
            v >> z;
            auto vertice = Vector3(x, y, z);
            vertices.push_back(vertice);
        } else if (line.substr(0, 2) == "vn") {
            std::istringstream v = std::istringstream(line.substr(2));
            float x, y, z;
            v >> x;
            v >> y;
            v >> z;
            auto normal = Vector3(x, y, z);
            normals.push_back(normal);
        } else if (line.substr(0, 2) == "vt") {
        }
            //check for faces
        else if (line.substr(0, 2) == "f ") {
            std::istringstream v = std::istringstream(line.substr(2));
            std::string x, y, z;
            v >> x;
            v >> y;
            v >> z;
            std::vector<std::string> stringsX;
            split(x, '/', stringsX);
            std::vector<std::string> stringsY;
            split(y, '/', stringsY);
            std::vector<std::string> stringsZ;
            split(z, '/', stringsZ);
            auto triangle  = new Triangle(vertices[std::stoi(stringsX[0]) - 1],
                                     vertices[std::stoi(stringsY[0]) - 1],
                                     vertices[std::stoi(stringsZ[0]) - 1]);
            mesh->addTriangle(triangle);

        }

    }
    return mesh;

}


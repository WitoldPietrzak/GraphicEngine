//
// Created by Witek on 27.03.2022.
//

#ifndef FOTO_SCENE_H
#define FOTO_SCENE_H


#include <vector>
#include "../Structures/Structure/Structure.h"

class Scene {
private:
    std::vector<Structure*> structures;
    LightIntensity backgroundColor;
public:
    Scene();

    explicit Scene(const std::vector<Structure*>& structures);

    explicit Scene(const LightIntensity &backgroundColor);

    Scene(const std::vector<Structure*>& structures, const LightIntensity &backgroundColor);

    const std::vector<Structure *> & getStructures() const;

    void setStructures(const std::vector<Structure*> &structures);

    const LightIntensity &getBackgroundColor() const;

    void setBackgroundColor(const LightIntensity &backgroundColor);

    void addStructure(Structure* structure);

    void removeStructure(Structure* structure);
};


#endif //FOTO_SCENE_H

//
// Created by Witek on 27.03.2022.
//

#ifndef FOTO_SCENE_H
#define FOTO_SCENE_H


#include <vector>
#include "../Structures/Structure/Structure.h"
#include "../Light/Light.h"
#include "../Light/PointLight/PointLight.h"
#include "../Light/SurfaceLight/SurfaceLight.h"

class Scene {
private:
    std::vector<Structure*> structures;
    std::vector<PointLight*> lightSources;
    LightIntensity backgroundColor = LightIntensity(0,0,0);
    LightIntensity ambient = LightIntensity(0,0,0);
public:
    Scene();

    explicit Scene(std::vector<Structure*>  structures);

    explicit Scene(const LightIntensity &backgroundColor);

    explicit Scene(const LightIntensity &backgroundColor, const LightIntensity &ambient);

    Scene(const std::vector<Structure*>& structures, const LightIntensity &backgroundColor);
    Scene(std::vector<Structure*>  structures, const LightIntensity &backgroundColor, const LightIntensity &ambient);

    const std::vector<Structure *> & getStructures() const;

    void setStructures(const std::vector<Structure*> &structures);

    const LightIntensity &getBackgroundColor() const;

    void setBackgroundColor(const LightIntensity &backgroundColor);

    const LightIntensity &getAmbient() const;

    void setAmbient(const LightIntensity &ambient);

    void addStructure(Structure* structure);

    void removeStructure(Structure* structure);

    const std::vector<PointLight *> &getLightSources() const;

    void setLightSources(const std::vector<PointLight *> &lightSources);

    void addLightSource(PointLight *light);

    void addLightSource(SurfaceLight *light);

    void removeLightSource(PointLight *light);

    void removeLightSource(SurfaceLight *light);

    void increaseTime(float time);
};


#endif //FOTO_SCENE_H

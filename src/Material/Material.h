//
// Created by witek on 23.04.2022.
//

#ifndef FOTO_MATERIAL_H
#define FOTO_MATERIAL_H


#include "../Image/Image.h"

enum MaterialType {
    diffuse_color, mirror, refraction, diffuse_texture
};

class Material {
private:
    float ambient, specular, diffuse, smoothness, refractionIndex;
    float distributionIndex = 0.01;
    Image texture = Image(0,0);
    LightIntensity color = LightIntensity::BLACK();
    MaterialType materialType = MaterialType::diffuse_color;
public:

    Material(float ambient, float specular, float diffuse, float smoothness);
    Material(float ambient, float specular, float diffuse, float smoothness, float refractionIndex);



    float getAmbient() const;

    void setAmbient(float ambient);

    float getSpecular() const;

    void setSpecular(float specular);

    float getDiffuse() const;

    void setDiffuse(float diffuse);

    float getSmoothness() const;

    void setSmoothness(float smoothness);

    float getRefractionIndex() const;

    void setRefractionIndex(float refractionIndex);

    MaterialType getMaterialType() const;

    void setMaterialType(MaterialType materialType);

    const Image &getTexture() const;

    void setTexture(const Image &texture);

    const LightIntensity &getColor() const;

    void setColor(const LightIntensity &color);

    float getDistributionIndex() const;

    void setDistributionIndex(float distributionIndex);


};


#endif //FOTO_MATERIAL_H

//
// Created by witek on 23.04.2022.
//

#ifndef FOTO_MATERIAL_H
#define FOTO_MATERIAL_H


class Material {
private:
    float ambient, specular, diffuse, smoothness;
public:

    Material(float ambient, float specular, float diffuse, float smoothness);

    float getAmbient() const;

    void setAmbient(float ambient);

    float getSpecular() const;

    void setSpecular(float specular);

    float getDiffuse() const;

    void setDiffuse(float diffuse);

    float getSmoothness() const;

    void setSmoothness(float smoothness);

};


#endif //FOTO_MATERIAL_H

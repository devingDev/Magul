#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <SDL2/SDL_image.h>

#include "color.h"

class Material{
    public:
        Material(const char* textureFile, double specularIntensity);
        Material(const char* textureFile, const char* normalMapFile, double specularIntensity);
        ~Material();
        Color GetColor(SDL_Surface* texForCol, double u, double v);
        Color GetColorFromSpherePoint(Vector3 point, double radius);
        Vector3 GetNormalFromSpherePoint(Vector3 point, double radius);

    private:
        SDL_Surface* _MainTex;
        SDL_Surface* _NormalTex;
        double specularIntensity;

    public:
        double GetSpecularIntensity();

};




#endif
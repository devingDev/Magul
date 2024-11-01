#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <SDL2/SDL_image.h>

#include "color.h"
#include "vector2.h"
#include "vector3.h"

class Material{
    public:
        Material(const char* mainTextureFile, double specularIntensity);
        Material(const char* mainTextureFile, const char* normalMapFile, double specularIntensity);
        Material(const char* mainTextureFile, const char* normalMapFile, Vector2 tiling, double specularIntensity);
        Material(const char* mainTextureFile, const char* normalMapFile, Vector2 tiling, Vector2 offset, double specularIntensity);
        ~Material();
        Color GetColor(SDL_Surface* texForCol, Vector2 uv);
        Color GetColorFromSpherePoint(Vector3 point, double radius);
        Vector3 GetNormalFromSpherePoint(Vector3 point, double radius);
        Vector2 CalculateUV(Vector3 point, double radius);

    private:
        SDL_Surface* _MainTex;
        SDL_Surface* _NormalTex;
        double specularIntensity;
        Vector2 tiling;
        Vector2 offset;

    public:
        double GetSpecularIntensity();

};




#endif
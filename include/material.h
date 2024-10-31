#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <SDL2/SDL_image.h>

#include "color.h"

class Material{
    public:
        Material(const char* textureFile);
        ~Material();
        Color GetColor(double u, double v);
        Color GetColorFromSpherePoint(Vector3 point, double radius);

    private:
        SDL_Surface* sTexture;

};




#endif
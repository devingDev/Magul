


#include "material.h"



Material::Material(const char *file){
    sTexture = IMG_Load(file);
    


}

Color Material::GetColor(double u, double v){
    double x = u * sTexture->w;
    double y = v * sTexture->h;
    int index =  (((sTexture->h - 1 - y) * sTexture->w) + x);
    //  ((uint32_t*)surf->pixels)[y*img.GetWidth() + x] = image.GetPixelForSDL(x, y);
    uint32_t sdlCol = ((uint32_t*)(sTexture->pixels))[index];
    return Color::SDLToColor(sdlCol);
}


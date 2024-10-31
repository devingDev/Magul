
#include <cmath>
#include <iostream>


#include "material.h"



Material::Material(const char *file){
    std::cout << "Material creation." <<"\n";
    sTexture = IMG_Load(file);
    if(sTexture == nullptr){
        std::cout << "Couldn't create surface from texture : " << file << "\n";
        return;
    }

    if (SDL_MUSTLOCK(sTexture)) {
        SDL_LockSurface(sTexture);
    }

    std::cout << "Material created!" <<"\n";

}

Material::~Material(){
    if (SDL_MUSTLOCK(sTexture)) {
        SDL_UnlockSurface(sTexture);
    }
    if(sTexture != nullptr){
        SDL_FreeSurface(sTexture);
    }
}

Color Material::GetColor(double u, double v){

    int x = u * sTexture->w;
    int y = v * sTexture->h;
    int bpp = sTexture->format->BitsPerPixel;
    uint32_t* pixels = (uint32_t*) sTexture->pixels;

    uint32_t pixel = pixels[y * sTexture->w + x];
    uint8_t r,g,b,a;
    SDL_GetRGBA(pixel, sTexture->format, &r, &g, &b, &a);


    return Color(1.0, r/255.0,g/255.0,b/255.0);
    
    uint32_t* p = (uint32_t*)sTexture->pixels + y * sTexture->pitch + x * bpp;
    switch (bpp)
    {
        case 1:
            return Color::SDLToColor(*p);
            break;

        case 2:
            return Color::SDLToColor( *(Uint16 *)p);
            break;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return Color::SDLToColor(p[0] << 16 | p[1] << 8 | p[2]);
            else
                return Color::SDLToColor(p[0] | p[1] << 8 | p[2] << 16);
                break;

            case 4:
                return Color::SDLToColor( *(Uint32 *)p);
                break;

            default:
                return Color::black;       /* shouldn't happen, but avoids warnings */
    }
    
    return Color::black;
}

Color Material::GetColorFromSpherePoint(Vector3 point, double radius){
    double u=0.5;
    double v=0.5;

    //u = (atan2(point.x,point.z) + M_PI) / (M_PI*2.0);
    u = (atan2(point.z,point.x) + M_PI) / (M_PI*2.0);

    double vACOSPART = acos(point.y/radius);
    v = (M_PI - (vACOSPART)) / (M_PI);
    if(std::isnan(v)){
        v = 0;
    }


    return GetColor(u, v);
}


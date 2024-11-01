
#include <cmath>
#include <iostream>


#include "material.h"



Material::Material(const char *file, double _specularIntensity){
    this->_NormalTex = nullptr;
    this->specularIntensity = _specularIntensity;
    std::cout << "Material creation." <<"\n";
    this->_MainTex = IMG_Load(file);
    if(this->_MainTex == nullptr){
        std::cout << "Couldn't create surface from texture : " << file << "\n";
        return;
    }



    std::cout << "Material created!" <<"\n";

}


Material::Material(const char* textureFile, const char* normalMapFile, double specularIntensity) : Material(textureFile, specularIntensity)
{
    this->_NormalTex  = IMG_Load(normalMapFile);
    if(this->_MainTex == nullptr){
        std::cout << "Couldn't create surface from NORMAL texture : " << normalMapFile << "\n";
        return;
    }
    std::cout << "Material with normal map created!" <<"\n";
}

Material::~Material(){
    std::cout << "Destroying material!" <<"\n";
    if(_MainTex != nullptr){
        SDL_FreeSurface(_MainTex);
    }
}

Color Material::GetColor(SDL_Surface* texForCol, double u, double v){

    if (SDL_MUSTLOCK(texForCol)) {
        SDL_LockSurface(texForCol);
    }
    int x = (u) * texForCol->w;
    int y = v * texForCol->h;
    int bpp = texForCol->format->BitsPerPixel;
    uint32_t* pixels = (uint32_t*) texForCol->pixels;

    //uint32_t pixel = pixels[y * _MainTex->w + x];
    uint32_t pixel = pixels[((texForCol->h - 1 - y) * texForCol->w) + x];
    uint8_t r,g,b,a;
    SDL_GetRGBA(pixel, texForCol->format, &r, &g, &b, &a);

    if (SDL_MUSTLOCK(texForCol)) {
        SDL_UnlockSurface(texForCol);
    }

    return Color(1.0, r/255.0,g/255.0,b/255.0);
    
    uint32_t* p = (uint32_t*)texForCol->pixels + y * texForCol->pitch + x * bpp;
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
    if(_MainTex == nullptr){
        return Color::white;
    }
    double u=0.5;
    double v=0.5;

    //u = (atan2(point.x,point.z) + M_PI) / (M_PI*2.0);
    u = (atan2(point.x,point.z) + M_PI) / (M_PI*2.0);

    double vACOSPART = acos(point.y/radius);
    v = (M_PI - (vACOSPART)) / (M_PI);
    if(std::isnan(v)){
        v = 0;
    }


    return GetColor(_MainTex, u, v);
}


Vector3 Material::GetNormalFromSpherePoint(Vector3 point, double radius){
    if(_NormalTex == nullptr){
        return Vector3(0, 0, 0);
    }
    double u=0.5;
    double v=0.5;

    //u = (atan2(point.x,point.z) + M_PI) / (M_PI*2.0);
    u = (atan2(point.x,point.z) + M_PI) / (M_PI*2.0);

    double vACOSPART = acos(point.y/radius);
    v = (M_PI - (vACOSPART)) / (M_PI);
    if(std::isnan(v)){
        v = 0;
    }

    Color normalColor = GetColor(_NormalTex, u, v);


    return Vector3(normalColor.r, normalColor.g, normalColor.b);
}



double Material::GetSpecularIntensity(){
    return this->specularIntensity;
}


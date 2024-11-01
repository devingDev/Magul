
#include <cmath>
#include <iostream>
#include <unistd.h>
#include "helper.h"

#include "material.h"



// Basic constructors which just call the main constructor with additional inputs
Material::Material(const char *mainTextureFile, double _specularIntensity) : Material(mainTextureFile, nullptr, _specularIntensity) {}
Material::Material(const char* mainTextureFile, const char* normalMapFile, double _specularIntensity) : Material(mainTextureFile, normalMapFile, Vector2(1,1), _specularIntensity) {}
Material::Material(const char* mainTextureFile, const char* normalMapFile, Vector2 _tiling, double _specularIntensity) : Material(mainTextureFile, normalMapFile, _tiling, Vector2(0,0), _specularIntensity){}

Material::Material(const char* mainTextureFile, const char* normalMapFile, Vector2 _tiling, Vector2 _offset, double _specularIntensity){
    std::cout << "Material creation." <<"\n";

    std::string basePath = SDL_GetBasePath();

    // Load main texture
    this->_MainTex = nullptr;
    if(mainTextureFile != nullptr){
        std::string pathMainTex = basePath + mainTextureFile;
        this->_MainTex = IMG_Load(pathMainTex.c_str());
        if(this->_MainTex == nullptr){
            std::cout << "Couldn't create surface from MAIN texture : " << pathMainTex << " Error: " << IMG_GetError() << "\n";
        }
    }

    // Load normal texture
    this->_NormalTex = nullptr;
    if(normalMapFile != nullptr){
        std::string pathNormalTex = basePath + normalMapFile;
        this->_NormalTex  = IMG_Load(pathNormalTex.c_str());
        if(this->_NormalTex == nullptr){
            std::cout << "Couldn't create surface from MAIN texture : " << pathNormalTex << " Error: " << IMG_GetError() << "\n";
        }
    }

    // Set other attributes
    this->specularIntensity = _specularIntensity;
    this->tiling = _tiling;
    this->offset = _offset;

    std::cout << "Material created!" <<"\n";
}

Material::~Material(){
    std::cout << "Destroying material!" <<"\n";
    if(_MainTex != nullptr){
        SDL_FreeSurface(_MainTex);
    }
    if(_NormalTex != nullptr){
        SDL_FreeSurface(_NormalTex);
    }
}

Color Material::GetColor(SDL_Surface* texForCol, Vector2 uv){
    if (SDL_MUSTLOCK(texForCol)) {
        SDL_LockSurface(texForCol);
    }

    // Tiling and Offsetting
    uv.x /= tiling.x;
    uv.y /= tiling.y;
    uv.x += offset.x;
    uv.y += offset.y;

    // Wrapping around:
    if(uv.x >= 1){
        uv.x = uv.x - (long)uv.x;
    }
    if(uv.x < 0){
        uv.x = uv.x + (long)uv.x;;
    }
    if(uv.y >= 1){
        uv.y = uv.y - (long)uv.y;
    }
    if(uv.y < 0){
        uv.y = uv.x + (long)uv.y;;
    }

    // Find correct index for on SDL surface
    int x = (uv.x) * texForCol->w;
    int y = uv.y * texForCol->h;
    int bpp = texForCol->format->BitsPerPixel;
    uint32_t* pixels = (uint32_t*) texForCol->pixels;
    //uint32_t pixel = pixels[y * _MainTex->w + x];
    uint32_t pixel = pixels[((texForCol->h - 1 - y) * texForCol->w) + x];
    uint8_t r,g,b,a;
    // Get the RGBA colors from the surface
    SDL_GetRGBA(pixel, texForCol->format, &r, &g, &b, &a);

    if (SDL_MUSTLOCK(texForCol)) {
        SDL_UnlockSurface(texForCol);
    }

    return Color(1.0, r/255.0,g/255.0,b/255.0);
}

Vector2 Material::CalculateUV(Vector3 point, double radius){
    double u=0.5;
    double v=0.5;

    //u = (atan2(point.x,point.z) + M_PI) / (M_PI*2.0);
    u = (atan2(point.x,point.z) + M_PI) / (M_PI*2.0);
    if(std::isnan(v)){
        u = 0;
    }

    double vACOSPART = acos(point.y/radius);
    v = (M_PI - (vACOSPART)) / (M_PI);
    if(std::isnan(v)){
        v = 0;
    }

    return Vector2(u,v);
}

Color Material::GetColorFromSpherePoint(Vector3 point, double radius){
    if(_MainTex == nullptr){
        return Color::white;
    }
    return GetColor(_MainTex, CalculateUV(point, radius));
}


Vector3 Material::GetNormalFromSpherePoint(Vector3 point, double radius){
    if(_NormalTex == nullptr){
        return Vector3(0, 0, 0);
    }
    Color normalColor = GetColor(_NormalTex, CalculateUV(point, radius));
    return Vector3(normalColor.r, normalColor.g, normalColor.b);
}



double Material::GetSpecularIntensity(){
    return this->specularIntensity;
}


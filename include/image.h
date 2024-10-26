#ifndef _IMAGE_H
#define _IMAGE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include "color.h"

class Image {
    private:
        double* pixelsColors;
        int width;
        int height;

    public:
        Image(int width, int height);
        ~Image();
        void SetPixel(int x, int y, Color col);
        void SetPixelForSDL(int x, int y, uint32_t col);
        double* GetPixels();
        Color GetPixel(int x, int y);
        uint32_t GetPixelForSDL(int x, int y);
        int GetPixelIndex(int x, int y);
        int GetWidth();
        int GetHeight();

};




#endif
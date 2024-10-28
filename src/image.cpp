#include "image.h"


Image::Image(int width, int height){
  this->width = width;
  this->height = height;
  pixelsColors = new double[4 * this->width * this->height];
}

Image::~Image(){
    delete(pixelsColors);
}


void Image::SetPixelByIndex(int startIndex, Color* col){
    if(col->a > 1) col->a = 1;
    if(col->r > 1) col->r = 1;
    if(col->g > 1) col->g = 1;
    if(col->b > 1) col->b = 1;

    pixelsColors[startIndex+0] = col->a;
    pixelsColors[startIndex+1] = col->r;
    pixelsColors[startIndex+2] = col->g;
    pixelsColors[startIndex+3] = col->b;
}


void Image::SetPixel(int x, int y, Color* col){
    int startIndex = GetPixelIndex(x,y);

    //if(col->a > 1) col->a = 1;
    //if(col->r > 1) col->r = 1;
    //if(col->g > 1) col->g = 1;
    //if(col->b > 1) col->b = 1;

    pixelsColors[startIndex+0] = col->a;
    pixelsColors[startIndex+1] = col->r;
    pixelsColors[startIndex+2] = col->g;
    pixelsColors[startIndex+3] = col->b;
}

void Image::SetPixelForSDL(int x, int y, uint32_t col){
    int startIndex = GetPixelIndex(x,y);
    double a = (double)((col >> 24) & 0xFF) / 255.0;
    double r = (double)((col >> 16) & 0xFF) / 255.0;
    double g = (double)((col >>  8) & 0xFF) / 255.0;
    double b = (double)((col >>  0) & 0xFF) / 255.0;

    //if(a > 1) a = 1;
    //if(r > 1) r = 1;
    //if(g > 1) g = 1;
    //if(b > 1) b = 1;

    pixelsColors[startIndex+0] = a;
    pixelsColors[startIndex+1] = r;
    pixelsColors[startIndex+2] = g;
    pixelsColors[startIndex+3] = b;
}

int Image::GetPixelIndex(int x, int y){
    return 4 * ((y * this->width) + x);
}

double* Image::GetPixels(){
    return pixelsColors;
}

Color Image::GetPixel(int x , int y){
    int startIndex = GetPixelIndex(x,y);
    Color color(pixelsColors[startIndex+0], pixelsColors[startIndex+1], pixelsColors[startIndex+2], pixelsColors[startIndex+3]);
    return color;
}

uint32_t Image::GetPixelForSDL(int x , int y){
    int startIndex = GetPixelIndex(x,y);
    uint32_t color =    (((uint32_t)(pixelsColors[startIndex+0] * 255) & 0xFF) << 24) +
                        (((uint32_t)(pixelsColors[startIndex+1] * 255) & 0xFF) << 16) +
                        (((uint32_t)(pixelsColors[startIndex+2] * 255) & 0xFF) <<  8) +
                        (((uint32_t)(pixelsColors[startIndex+3] * 255) & 0xFF) <<  0);
    return color;
}

int Image::GetWidth(){
    return width;
}

int Image::GetHeight(){
    return height;
}

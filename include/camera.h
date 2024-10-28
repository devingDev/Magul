#ifndef _CAMERA_H
#define CAMERA_H

#include "vector2.h"


class Camera{
    private:
        float angle;
        Vector2 pictureSize;
    
    public:
        Camera(float angle, int width, int height);
};



#endif
#ifndef _CAMERA_H
#define CAMERA_H

#include "vector2.h"
#include "vector3.h"
#include "ray.h"


class Camera{
    private:
        double angleDegree;
        double angleRadian;
        Vector2 pictureSize;
        Vector2 pictureSizeHalf;
    
    public:
        Camera(double angleDeg, int width, int height);
        Ray generateRay(Vector2 pos);
};



#endif
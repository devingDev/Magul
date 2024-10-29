#ifndef _CAMERA_H
#define _CAMERA_H

#include "vector2.h"
#include "vector3.h"
#include "ray.h"



class Camera{
    private:
        double angleDegree;
        double angleRadian;
        Vector2 pictureSize;
        Vector2 pictureSizeHalf;
        double dirZ;
    
    public:
        Camera() {}
        Camera(double angleDeg, int width, int height);
        Ray generateRay(int x, int y);
        Ray generateRay(Vector2 pos);
        void SetAngle(double newAngleDeg);
        void SetSize(int newWidth, int newHeight);
        Vector2 GetSize();

    private:
        void SetCaches();
};



#endif
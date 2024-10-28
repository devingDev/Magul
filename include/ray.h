#ifndef _RAY_H
#define _RAY_H

#include "vector3.h"

class Ray{
    public:
        Vector3 origin;
        Vector3 direction;
        float tMin;
        float tMax;

    public:
        Ray();
        Ray(Vector3 origin, Vector3 dir);
        Ray(Vector3 origin, Vector3 dir, float tMin, float tMax);
        Vector3 scaleRayBy(float t);
        bool withinLimits(float t);


};




#endif
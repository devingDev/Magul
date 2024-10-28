#ifndef _RAY_H
#define _RAY_H

#include "vector3.h"
#include <iostream>

class Ray{
    public:
        Vector3 origin;
        Vector3 direction;
        double tMin;
        double tMax;

    public:
        Ray();
        Ray(Vector3 origin, Vector3 dir);
        Ray(Vector3 origin, Vector3 dir, double tMin, double tMax);
        Vector3 scaleRayBy(double t);
        bool withinLimits(double t);
        friend std::ostream& operator<<(std::ostream &strm, const Ray &a);


};




#endif
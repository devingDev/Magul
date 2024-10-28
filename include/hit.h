#ifndef _RAY_H
#define _RAY_H

#include "vector3.h"
#include "color.h"

class Hit{
    public:
        double t;
        Vector3 point;
        Vector3 normal;
        Color color;

    public:
        Hit();
        Hit(double t, Vector3 point, Vector3 normal, Color color);


};




#endif
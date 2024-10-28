#ifndef _RAY_H
#define _RAY_H

#include "vector3.h"
#include "color.h"

class Hit{
    public:
        float t;
        Vector3 point;
        Vector3 normal;
        Color color;

    public:
        Hit();
        Hit(float t, Vector3 point, Vector3 normal, Color color);


};




#endif
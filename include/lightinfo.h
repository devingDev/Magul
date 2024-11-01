#ifndef _LIGHTINFO_H
#define _LIGHTINFO_H

#include <cstdint>
#include <limits>

#include "vector3.h"
#include "color.h"


class LightInfo{
    public:
        enum LightType { directional, point };
        Vector3 direction;
        Color incomingColor; 
        LightType lightType;
        double tMax;

    public:
        LightInfo(Vector3 direction, Color color, LightType lightType, double tMax);
};





#endif
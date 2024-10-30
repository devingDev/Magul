#ifndef _LIGHTINFO_H
#define _LIGHTINFO_H

#include "vector3.h"
#include "color.h"

class LightInfo{
    public:
        Vector3 direction;
        Color incomingColor;
    
    public:
        LightInfo(Vector3 direction, Color color);
};





#endif
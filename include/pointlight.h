#ifndef _POINTLIGHT_H
#define _POINTLIGHT_H


#include "ilight.h"

class PointLight : public ILight{
    public:
        PointLight(Vector3 position, Color color);
        virtual LightInfo GetInfo(Vector3 p) override;
    
    public:
        Vector3 position;
        Color color;
};


#endif
#ifndef _DIRECTIONALLIGHT_H
#define _DIRECTIONALLIGHT_H


#include "ilight.h"

class DirectionalLight : public ILight{
    public:
        DirectionalLight(Vector3 direction, Color color);
        virtual LightInfo GetInfo(Vector3 p) override;
    
    public:
        Vector3 direction;
        Color color;
};


#endif
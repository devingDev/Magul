#ifndef _ILIGHT_H
#define _ILIGHT_H

#include "vector3.h"
#include "lightinfo.h"

class ILight{
    //protected:
    //    LightInfo lightInfo;
    public:
        virtual ~ILight() {}

    public:
        virtual LightInfo GetInfo(Vector3 point) = 0; 

};




#endif
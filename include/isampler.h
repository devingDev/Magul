#ifndef _ISAMPLER_H
#define _ISAMPLER_H

#include "vector2.h"
#include "color.h"

class ISampler{
    public:
        virtual ~ISampler() {}
        
    private:
        virtual Color getColor(Vector2 pos) = 0;
        virtual Color getColor(int x, int y) = 0;

};



#endif
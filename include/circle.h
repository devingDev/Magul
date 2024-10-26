#ifndef _CIRCLE_H
#define _CIRCLE_H
#include <stdint.h>
#include "vector2.h"
#include "color.h"

class Circle{
    private:
        float radius;
        Color color;
        Vector2 position;

    public:
        Circle(float radius, Color color, float x, float y);
        bool coversPoint(Vector2 pos);


};



#endif
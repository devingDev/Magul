#ifndef _CIRCLE_H
#define _CIRCLE_H
#include <stdint.h>
#include "vector2.h"
#include "color.h"

class Circle final{
    private:
        double radius;
        double powRadius;
        Color color;
        Vector2 position;

    private:
        Circle();

    public:
        Circle(double radius, Color color, double x, double y);
        bool coversPoint(Vector2 pos);
        bool coversPoint(double x, double y);
        bool possiblyInPoint(double x, double y);
        Color& GetColor();


};



#endif
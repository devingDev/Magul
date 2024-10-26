#include <stdio.h>
#include "circle.h"



Circle::Circle(float radius, Color color, float x, float y){
    this->radius = radius;
    this->color = color;
    this->position = Vector2(x,y);
}


bool Circle::coversPoint(Vector2 pos){
    Vector2 circleToPoint = pos - this->position;
    printf("%f %f\n", circleToPoint.x,  circleToPoint.y);

    double dist = circleToPoint.length();
    printf("%f\n", dist);

    return false;
}

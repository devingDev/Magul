#include <stdio.h>
#include "circle.h"



Circle::Circle(float radius, Color color, float x, float y){
    this->radius = radius;
    this->powRadius =  radius*radius;
    this->color = color;
    this->position = Vector2(x,y);
}


bool Circle::coversPoint(Vector2 pos){
    Vector2 circleToPoint = pos - this->position;

    //double dist = circleToPoint.length();

    //return dist < radius;
    return (circleToPoint.x*circleToPoint.x + circleToPoint.y*circleToPoint.y) < powRadius;
}

bool Circle::coversPoint(float x, float y){
    Vector2 circleToPoint = Vector2(x,y) - this->position;

    //double dist = circleToPoint.length();

    //return dist < radius;
    return (circleToPoint.x*circleToPoint.x + circleToPoint.y*circleToPoint.y) < powRadius;
}

bool Circle::possiblyInPoint(float x, float y){
    return x >= (this->position.x - radius) && x <= (this->position.x + radius)
            && y >= (this->position.y - radius) && y <= (this->position.y + radius);
}

Color* Circle::GetColor(){
    return &color;
}

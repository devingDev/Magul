#include <cmath>
#include "vector2.h"


Vector2::Vector2(){
    x = y = 0;
}

Vector2::Vector2(double x, double y){
    this->x = x;
    this->y = y;
}

double Vector2::length(){
    return sqrt(x*x+y*y);
}

Vector2& Vector2::operator-=(Vector2 const& rhs){
    this->x = this->x - rhs.x;
    this->y = this->y - rhs.y;
    return *this;
}

Vector2 Vector2::operator-(Vector2 const& rhs){
    Vector2 vec(*this);
    return vec-=rhs;
}



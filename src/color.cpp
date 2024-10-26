#include "color.h"



Color::Color(){
    a=r=g=b=1.0;
}

Color::Color(double a, double r, double g, double b){
    this->a = a;
    this->r = r;
    this->g = g;
    this->b = b;
}
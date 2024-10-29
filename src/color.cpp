#include "color.h"


const Color Color::white = Color(1.0, 1.0, 1.0, 1.0);
const Color Color::black = Color(1.0, 0.0, 0.0, 0.0);
const Color Color::red(1.0, 1.0, 0.0, 0.0);
const Color Color::green = Color(1.0, 0.0, 1.0, 0.0);
const Color Color::blue = Color(1.0, 0.0, 0.0, 1.0);


Color::Color(){
    a=r=g=b=1.0;
}

Color::Color(double a, double r, double g, double b){
    this->a = a;
    this->r = r;
    this->g = g;
    this->b = b;
}

std::ostream& operator<<(std::ostream &strm, const Color &a){
    return strm << "(Color R=" << a.r << ", G=" << a.g << ", B=" << a.b  << ", A=" << a.a << ")";
}


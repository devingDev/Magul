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

Color::Color(Vector3 rgb){
    this->a = 1.0;
    this->r = rgb.x;
    this->g = rgb.y;
    this->b = rgb.z;
}

Color Color::operator+=(Color const& rhs){
    this->a += rhs.a;
    this->r += rhs.r;
    this->g += rhs.g;
    this->b += rhs.b;
    return *this;
}

Color Color::operator+(Color const& rhs){
    Color col(*this);
    return col+=rhs;
}

Color Color::operator*=(Color const& rhs){
    this->a *= rhs.a;
    this->r *= rhs.r;
    this->g *= rhs.g;
    this->b *= rhs.b;
    return *this;
}

Color Color::operator*(Color const& rhs){
    Color col(*this);
    return col*=rhs;
}

Color Color::operator*=(double const& rhs){
    this->a *= rhs;
    this->r *= rhs;
    this->g *= rhs;
    this->b *= rhs;
    return *this;
}

Color Color::operator*(double const& rhs){
    Color col(*this);
    return col*=rhs;
}

Color Color::operator/=(double const& rhs){
    this->a /= rhs;
    this->r /= rhs;
    this->g /= rhs;
    this->b /= rhs;
    return *this;
}

Color Color::operator/(double const& rhs){
    Color col(*this);
    return col/=rhs;
}

void Color::clamp(){
    if(this->a > 1.0) this->a = 1;
    if(this->r > 1.0) this->r = 1;
    if(this->g > 1.0) this->g = 1;
    if(this->b > 1.0) this->b = 1;
}

std::ostream& operator<<(std::ostream &strm, const Color &a){
    return strm << "(Color R=" << a.r << ", G=" << a.g << ", B=" << a.b  << ", A=" << a.a << ")";
}


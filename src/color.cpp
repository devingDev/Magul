#include "color.h"


const Color Color::white = Color(1.0, 1.0, 1.0, 1.0);
const Color Color::black = Color(1.0, 0.0, 0.0, 0.0);
const Color Color::gray = Color(1.0, 0.5, 0.5, 0.5);
const Color Color::red(1.0, 1.0, 0.0, 0.0);
const Color Color::green = Color(1.0, 0.0, 1.0, 0.0);
const Color Color::blue = Color(1.0, 0.0, 0.0, 1.0);
const Color Color::magenta = Color(1.0, 1.0, 0.0, 1.0);


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

void Color::normalize(){
    this->a = 1; 
    Vector3 vec(this->r, this->g, this->b);
    double len = vec.length();
    if(len > 1){
        this->r /= len;
        this->g /= len;
        this->b /= len;
    }
}


Color Color::SDLToColor(uint8_t r, uint8_t g, uint8_t b){
    Color ret;
    ret.a = 1.0;
    ret.r = (double)((r >> 16) & 0xFF) / 255.0;
    ret.g = (double)((g >>  8) & 0xFF) / 255.0;
    ret.b = (double)((b >>  0) & 0xFF) / 255.0;
    return ret;
}


Color Color::SDLToColor(uint32_t color){
    Color ret;
    ret.a = (double)((color >> 24) & 0xFF) / 255.0;
    ret.r = (double)((color >> 16) & 0xFF) / 255.0;
    ret.g = (double)((color >>  8) & 0xFF) / 255.0;
    ret.b = (double)((color >>  0) & 0xFF) / 255.0;
    return ret;
}

uint32_t Color::ColorToSDL(Color color){
    uint32_t ret =    (((uint32_t)(color.a * 255) & 0xFF) << 24) +
                        (((uint32_t)(color.r * 255) & 0xFF) << 16) +
                        (((uint32_t)(color.g * 255) & 0xFF) <<  8) +
                        (((uint32_t)(color.b * 255) & 0xFF) <<  0);
    return ret;
}

std::ostream& operator<<(std::ostream &strm, const Color &a){
    return strm << "(Color R=" << a.r << ", G=" << a.g << ", B=" << a.b  << ", A=" << a.a << ")";
}


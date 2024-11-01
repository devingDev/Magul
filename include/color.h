#ifndef _COLOR_H
#define _COLOR_H

#include <ostream>
#include <cstdint>
#include "vector3.h"

//ARGB
class Color{
    public:
        double a;
        double r;
        double g;
        double b;

    public:
        static const Color white;
        static const Color black;
        static const Color gray;
        static const Color red;
        static const Color green;
        static const Color blue;
        static const Color magenta;


    public:
        Color();
        Color(double a, double r, double g, double b);
        Color(Vector3 rgb);
        Color operator+=(Color const& rhs);
        Color operator+(Color const& rhs);

        Color operator*=(Color const& rhs);
        Color operator*(Color const& rhs);
        
        Color operator*=(double const& rhs);
        Color operator*(double const& rhs);

        Color operator/=(double const& rhs);
        Color operator/(double const& rhs);

        void clamp();
        void normalize();

        static Color SDLToColor(uint8_t r, uint8_t g, uint8_t b);
        static Color SDLToColor(uint32_t color);
        static uint32_t ColorToSDL(Color color);

        friend std::ostream& operator<<(std::ostream &strm, const Color &a);



};



#endif
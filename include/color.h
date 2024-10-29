#ifndef _COLOR_H
#define _COLOR_H

#include <ostream>

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
        static const Color red;
        static const Color green;
        static const Color blue;


    public:
        Color();
        Color(double a, double r, double g, double b);
        friend std::ostream& operator<<(std::ostream &strm, const Color &a);



};



#endif
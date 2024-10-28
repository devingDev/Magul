#ifndef _VECTOR2_H
#define _VECTOR2_H

class Vector2 final{
    public:
        double x;
        double y;

    public:
        Vector2();
        Vector2(double x, double y);
        double length();
        Vector2& operator-=(Vector2 const& rhs);
        Vector2 operator-(Vector2 const& rhs);

};


#endif
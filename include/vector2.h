#ifndef _VECTOR2_H
#define _VECTOR2_H

class Vector2 final{
    public:
        float x;
        float y;

    public:
        Vector2();
        Vector2(float x, float y);
        double length();
        Vector2& operator-=(Vector2 const& rhs);
        Vector2 operator-(Vector2 const& rhs);

};


#endif
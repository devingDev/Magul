#ifndef _VECTOR3_H
#define _VECTOR3_H

class Vector3 final{
    public:
        float x;
        float y;
        float z;

    public:
        Vector3();
        Vector3(float x, float y, float z);
        double length();
        Vector3& operator-=(Vector3 const& rhs);
        Vector3 operator-(Vector3 const& rhs);

};


#endif
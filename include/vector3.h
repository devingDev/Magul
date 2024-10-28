#ifndef _VECTOR3_H
#define _VECTOR3_H

#include <iostream>

class Vector3 final{
    public:
        double x;
        double y;
        double z;

    public:
        Vector3();
        Vector3(double x, double y, double z);
        double length();
        void normalize();
        Vector3& operator-=(Vector3 const& rhs);
        Vector3 operator-(Vector3 const& rhs);
        friend std::ostream& operator<<(std::ostream &strm, const Vector3 &a);

};


#endif
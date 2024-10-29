#ifndef _VECTOR3_H
#define _VECTOR3_H

#include <ostream>

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

        //static Vector3 cross(Vector3 a, Vector3 b);

        Vector3 cross(const Vector3& other) const;
        double dot(const Vector3& other) const;
        Vector3 multiply(const Vector3& other) const;
        
        Vector3& operator+=(Vector3 const& rhs);
        Vector3 operator+(Vector3 const& rhs);
        Vector3& operator-=(Vector3 const& rhs);
        Vector3 operator-(Vector3 const& rhs);
        Vector3 operator*=(double const& rhs);
        Vector3 operator*(double const& rhs);
        double operator*(Vector3 const& rhs);
        Vector3 operator/(double const& rhs);
        Vector3 operator/=(double const& rhs);


        friend std::ostream& operator<<(std::ostream &strm, const Vector3 &a);

};


#endif
#include <cmath>
#include "vector3.h"


Vector3::Vector3(){
    x = y = z = 0;
}

Vector3::Vector3(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

double Vector3::length(){
    return sqrt(x*x+y*y+z*z);
}

void Vector3::normalize(){
    double len = length();
    this->x = this->x / len;
    this->y = this->y / len;
    this->z = this->z / len;
}

Vector3& Vector3::operator-=(Vector3 const& rhs){
    this->x = this->x - rhs.x;
    this->y = this->y - rhs.y;
    this->z = this->z - rhs.z;
    return *this;
}
Vector3 Vector3::operator-(Vector3 const& rhs){
    Vector3 vec;
    vec.x = this->x - rhs.x;
    vec.y = this->y - rhs.y;
    vec.z = this->z - rhs.z;
    return vec;
}

std::ostream& operator<<(std::ostream &strm, const Vector3 &a){
    return strm << "(" << a.x << ", " << a.y << ", " << a.z  << ")";
}

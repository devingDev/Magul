#include <cmath>
#include "vector3.h"


Vector3::Vector3(){
    x = y = 0;
}

Vector3::Vector3(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

double Vector3::length(){
    return sqrt(x*x+y*y);
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

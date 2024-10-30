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


/*
Vector3 Vector3::cross(Vector3 a, Vector3 b){
    return Vector3(
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    );
}
*/

Vector3 Vector3::cross(const Vector3& b) const{
    return Vector3(
        this->y*b.z - this->z*b.y,
        this->z*b.x - this->x*b.z,
        this->x*b.y - this->y*b.x
    );
}

double Vector3::dot(const Vector3& other) const{
    return this->x * other.x + this->y * other.y + this->z * other.z;
}

Vector3 Vector3::multiply(const Vector3& other) const{
    return Vector3(
      this->x * other.x,  
      this->y * other.y,  
      this->z * other.z
    );
}

Vector3& Vector3::operator+=(Vector3 const& rhs){
    this->x = this->x + rhs.x;
    this->y = this->y + rhs.y;
    this->z = this->z + rhs.z;
    return *this;
}

Vector3 Vector3::operator+(Vector3 const& rhs){
    Vector3 vec(*this);
    return vec+=rhs;
}

Vector3& Vector3::operator-=(Vector3 const& rhs){
    this->x = this->x - rhs.x;
    this->y = this->y - rhs.y;
    this->z = this->z - rhs.z;
    return *this;
}

Vector3 Vector3::operator-(Vector3 const& rhs){
    Vector3 vec(*this);
    return vec-=rhs;
}


Vector3 Vector3::operator*=(double const& rhs){
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    return *this;
}

Vector3 Vector3::operator*(double const& rhs){
    Vector3 vec(*this);
    return vec*=rhs;
}

Vector3 Vector3::operator/=(double const& rhs){
    this->x /= rhs;
    this->y /= rhs;
    this->z /= rhs;
    return *this;
}

Vector3 Vector3::operator/(double const& rhs){
    Vector3 vec(*this);
    return vec/=rhs;
}

double Vector3::operator*(Vector3 const& rhs){
    return (this->x * rhs.x + this->y * rhs.y + this->z * rhs.z);
}

Vector3 Vector3::operator-(){
    Vector3 v;
    v.x = -x;
    v.y = -y;
    v.z = -z;
    return v;
}


std::ostream& operator<<(std::ostream &strm, const Vector3 &a){
    return strm << "(Vec3: " << a.x << ", " << a.y << ", " << a.z  << ")";
}

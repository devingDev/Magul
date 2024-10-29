#include <limits>

#include "hit.h"


Hit::Hit(){
    this->t = 0;
    this->point = Vector3();
    this->normal = Vector3();
    this->color = Color();
}

Hit::Hit(double t, Vector3 point, Vector3 normal, Color color){
    this->t = t;
    this->point = point;
    this->normal = normal;
    this->color = color;
}

std::ostream& operator<<(std::ostream &strm, const Hit &a){
    return strm << "Hit[t=" << a.t << ", point=" << a.point << ", normal=" << a.normal  << ", color=" << a.color << ")";
}

std::ostream& operator<<(std::ostream &strm, const std::optional<Hit> &a){
    if(a){
        return strm << *a;
    }
    return strm << "null";
}

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

#include <limits>

#include "ray.h"



Ray::Ray(){
    origin = Vector3(0,0,0);
    direction = Vector3(0,0,0);
    tMin = 0;
    tMax = std::numeric_limits<double>::infinity();
}

Ray::Ray(Vector3 origin, Vector3 dir){
    this->origin = origin;
    this->direction = dir;
    tMin = 0;
    tMax = std::numeric_limits<double>::infinity();
}

Ray::Ray(Vector3 origin, Vector3 dir, double tMin, double tMax){
    this->origin = origin;
    this->direction = dir;
    this->tMin = tMin;
    this->tMax = tMax;
}

Vector3 Ray::scaleRayBy(double t){
    Vector3 m;

    m.x = origin.x + direction.x * t;
    m.y = origin.y + direction.y * t;
    m.z = origin.z + direction.z * t;

    return m;
}

bool Ray::withinLimits(double t){
    return (t >= tMin && t <= tMax);
}

std::ostream& operator<<(std::ostream &strm, const Ray &a) {
  return strm << "Ray[origin=" << a.origin << ", direction=" << a.direction << "]";
}


#ifndef _HIT_H
#define _HIT_H

#include <ostream>
#include <optional>
#include "vector3.h"
#include "color.h"
#include "ray.h"

class Hit{
    public:
        double t;
        Vector3 point;
        Vector3 normal;
        Color color;
        Ray ray;
        int index;

    public:
        Hit();
        Hit(double t, Vector3 point, Vector3 normal, Color color, Ray ray, int index);
        friend std::ostream& operator<<(std::ostream &strm, const Hit &a);
        friend std::ostream& operator<<(std::ostream &strm, const std::optional<Hit> &a);


};




#endif
#ifndef _SPHERE_H
#define _SPHERE_H

#include <optional>

#include "vector3.h"
#include "hit.h"
#include "ray.h"

class Sphere{
    public:
        Vector3 position;
        double radius;
        Color color;
        Material* material;

    public:
        Sphere(Vector3 position, double radius, Color color, Material* mat);
        std::optional<Hit> intersect(Ray ray, int index);

};


#endif
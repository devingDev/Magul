

#include <cmath>
#include "sphere.h"

Sphere::Sphere(Vector3 position, double radius, Color color, Material* mat){
    this->position = position;
    this->radius = radius;
    this->color = color;
    this->material = mat;
}

std::optional<Hit> Sphere::intersect(Ray ray, int index){
    Hit hit = Hit();

    // Move ray back (-) by sphere position so its like the sphere is at the origin
    Vector3 adjustedRayOrigin = ray.origin - this->position;

    // quadratic formula
    double a = ray.direction * ray.direction;
    double b = 2 * (adjustedRayOrigin * ray.direction);
    double c = (adjustedRayOrigin*adjustedRayOrigin) - (this->radius*this->radius);
    
    double discriminant = (b*b) - (4*a*c);

    if(discriminant < 0){
        return std::nullopt;
    }


    double discriminantSqrt = sqrt(discriminant);
    if(discriminant > 0){
        double solution1 = (-b + discriminantSqrt) / (2*a);
        double solution2 = (-b - discriminantSqrt) / (2*a);
        bool foundAny = false;
        if(ray.withinLimits(solution1)){
            hit.t = solution1;
            foundAny = true;
        }
        if(solution2 < solution1 && ray.withinLimits(solution2)){
            hit.t = solution2;
            foundAny = true;
        }
        if(!foundAny){
            return std::nullopt;
        }
        
    }else{
        double solution = (-b - discriminantSqrt) / (2*a);
        if(ray.withinLimits(solution)){
            hit.t = solution;
        }else{
            return std::nullopt;
        }
    }

    

    hit.point = ray.origin + (ray.direction * hit.t);

    // calculate normal
    hit.normal = (hit.point - this->position)/this->radius;
    hit.normal.normalize();


    hit.color = this->color;
    hit.ray = ray;
    hit.index  = index;

    return hit;
}

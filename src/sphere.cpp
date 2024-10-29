

#include <cmath>
#include "sphere.h"

Sphere::Sphere(Vector3 position, double radius, Color color){
    this->position = position;
    this->radius = radius;
    std::cout << "Assigned color : " << color << "\n";
    this->color = color;
}

std::optional<Hit> Sphere::intersect(Ray r){
    Hit hit = Hit();

    // Move ray back (-) by sphere position so its like the sphere is at the origin
    Vector3 adjustedRayOrigin = r.origin - this->position;

    // quadratic formula
    double a = r.direction * r.direction;
    double b = 2 * (adjustedRayOrigin * r.direction);
    double c = (adjustedRayOrigin*adjustedRayOrigin) - (this->radius*this->radius);
    
    double discriminant = (b*b) - (4*a*c);

    if(discriminant < 0){
        return std::nullopt;
    }


    double discriminantSqrt = sqrt(discriminant);
    if(discriminant > 0){
        double solution1 = (-b + discriminantSqrt) / (2*a);
        double solution2 = (-b - discriminantSqrt) / (2*a);
        if(r.withinLimits(solution1)){
            hit.t = solution1;
        }
        if(solution2 < solution1 && r.withinLimits(solution2)){
            hit.t = solution2;
        }
        
    }else{
        hit.t = (-b - discriminantSqrt) / (2*a);
    }

    

    hit.point = r.origin + (r.direction * hit.t);

    // calculate normal
    hit.normal = (hit.point - this->position)/this->radius;


    hit.color = this->color;

    return hit;
}

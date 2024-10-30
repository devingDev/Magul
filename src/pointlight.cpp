

#include "pointlight.h"




PointLight::PointLight(Vector3 position, Color color){
    this->position = position;
    this->color = color;
}

LightInfo PointLight::GetInfo(Vector3 point){
    Vector3 direction = Vector3(this->position - point);

    Vector3 normalized = direction;
    normalized.normalize();

    double dirLength = direction.length();
    double intensityDivider = dirLength*dirLength;

    return LightInfo(normalized, 
        (this->color / intensityDivider)
    );
}
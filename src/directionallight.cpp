

#include "directionallight.h"

DirectionalLight::DirectionalLight(Vector3 direction, Color color){
    this->direction = direction;
    this->direction.normalize();
    this->color = color;
}

LightInfo DirectionalLight::GetInfo(Vector3 p){
    return LightInfo(Vector3(this->direction), this->color);
}


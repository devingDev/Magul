

#include "directionallight.h"

DirectionalLight::DirectionalLight(Vector3 direction, Color color,  double _intensity){
    this->direction = direction;
    this->direction.normalize();
    this->color = color;
    this->intensity = _intensity;
}

LightInfo DirectionalLight::GetInfo(Vector3 p){
    return LightInfo(Vector3(this->direction), this->color*this->intensity, LightInfo::LightType::directional,
        std::numeric_limits<double>::infinity());
}


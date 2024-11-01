


#include "pointlight.h"




PointLight::PointLight(Vector3 pos, Color col, double _intensity){
    this->position = pos;
    this->color = col;
    this->intensity = _intensity;
}

LightInfo PointLight::GetInfo(Vector3 point){
    // Get normalized direction to light
    Vector3 direction = Vector3(this->position - point);
    double dirLength = direction.length();
    Vector3 normalized = direction;
    normalized.normalize();
    
    // Get outColor
    double intensityDivider = dirLength*dirLength;
    Color outColor = (this->color / intensityDivider) * this->intensity;

    return LightInfo(normalized, 
        outColor,
        LightInfo::LightType::point,
        dirLength
    );
}




#include "pointlight.h"




PointLight::PointLight(Vector3 pos, Color col){
    this->position = pos;
    this->color = col;
}

LightInfo PointLight::GetInfo(Vector3 point){
    Vector3 direction = Vector3(this->position - point);
    double dirLength = direction.length();
    Vector3 normalized = direction;
    normalized.normalize();



    // Get color
    double intensityDivider = dirLength*dirLength;
    Color outColor = (this->color / intensityDivider);



    return LightInfo(normalized, 
        outColor,
        LightInfo::LightType::point,
        dirLength
    );
}

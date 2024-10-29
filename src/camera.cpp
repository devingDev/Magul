
#include <cmath>

#include "camera.h"


Camera::Camera(double angleDeg, int width, int height){
    SetAngle(angleDeg);
    SetSize(width, height);
    SetCaches();
}

Ray Camera::generateRay(Vector2 pos){
    return generateRay(pos.x, pos.y);
}

Ray Camera::generateRay(int x, int y){
    Vector3 direction(
        x - (this->pictureSizeHalf.x),
        y - (this->pictureSizeHalf.y),
        this->dirZ
    );

    direction.normalize();
    
    return Ray(Vector3(0,0,0), direction);
}


void Camera::SetAngle(double newAngleDeg){
    this->angleDegree = newAngleDeg;
    SetCaches();
}

void Camera::SetSize(int newWidth, int newHeight){
    this->pictureSize = Vector2(newWidth, newHeight);
    SetCaches();
}

void Camera::SetCaches(){
    this->angleRadian = this->angleDegree * M_PI / 180.0;
    this->pictureSizeHalf = Vector2(this->pictureSize.x/2, this->pictureSize.y/2);

    // Precache the dirZ since this won't change unless cam size or angle change
    double angleCalc = tan(this->angleRadian/2);
    this->dirZ = -(this->pictureSizeHalf.x / angleCalc); 
}

Vector2 Camera::GetSize(){
    return pictureSize;
}


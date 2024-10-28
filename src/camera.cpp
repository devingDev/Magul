
#include <cmath>

#include "camera.h"


Camera::Camera(double angleDeg, int width, int height){
    this->angleDegree = angleDeg;
    this->angleRadian = angleDeg * M_PI / 180.0;
    this->pictureSize = Vector2(width, height);
    this->pictureSizeHalf = Vector2(width/2, height/2);
}

Ray Camera::generateRay(Vector2 pos){
    Vector3 origin(0,0,0);
    Vector3 direction;
    //std::cout << pos.x << pos.y << "\n";
    direction.x = pos.x - (this->pictureSizeHalf.x);
    direction.y = pos.y - (this->pictureSizeHalf.y);
    double angleCalc = tan(angleRadian/2);
    //std::cout << "A:" << angle << "   " << angleCalc << "\n";
    direction.z =  -(this->pictureSizeHalf.x / angleCalc);
    direction.normalize();
    //std::cout << "D:" << direction << "\n";
    Ray ray(origin, direction);
    return ray;
}




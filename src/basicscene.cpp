
#include <limits>
#include <algorithm>

#include "basicscene.h"
#include "constants.h"




BasicScene::BasicScene(){
    std::cout << "Initializing scene" << "\n";
    cam = Camera(90, WIDTH, HEIGHT);

    Color colors[] = {Color::white, Color::red, Color::green, Color::blue}; 

    
    sceneObjects.push_back(Sphere(Vector3(0,8,-15), 1, Color::white));
    sceneObjects.push_back(Sphere(Vector3(0,0,-15), 1, Color::white));
    sceneObjects.push_back(Sphere(Vector3(0,-8,-15), 1, Color::white));
    sceneObjects.push_back(Sphere(Vector3(-8,0,-15), 1, Color::white));
    sceneObjects.push_back(Sphere(Vector3(8,0,-15), 1, Color::white));
    sceneObjects.push_back(Sphere(Vector3(1,1,-15), 1.0, Color::red));
    sceneObjects.push_back(Sphere(Vector3(5,5,-15), 1.0, Color::green));
    sceneObjects.push_back(Sphere(Vector3(4,8,-15), 1.0, Color::blue));

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
           sceneObjects.push_back(Sphere(Vector3(-10+(j*2 * (rand()%3)),-5+(i*2 * (rand()%3)),-15), 1.0, colors[j%4]));
        }
    }
}


Color BasicScene::getColor(Vector2 pos){
    return getColor(pos.x, pos.y);
}

Color BasicScene::getColor(int x, int y){
    double smallestT = std::numeric_limits<double>::infinity();
    std::optional<Hit> smallestHit = std::nullopt;

    for(int i = 0; i < sceneObjects.size(); i++){
        std::optional<Hit> hit = sceneObjects[i].intersect(cam.generateRay(x,y));
        if(hit){
            if((*hit).t < smallestT){
                smallestHit = hit;
                smallestT = (*hit).t;
            }
        }
    }

    if(smallestHit){
        return shade((*smallestHit));
        //return Color((*smallestHit).normal);
    }

    return Color::black;
}

Color BasicScene::shade(Hit& hit){
    Vector3 lightDir(1,1,0.7);
    lightDir.normalize();
    Color ambient = hit.color * 0.1;
    //Color diffuse = multiply(0.9 * Math.max(0, dot(lightDir, hitnormal) ) , hit.color());
    Color diffuse = hit.color * 0.9 * std::max(0.0, lightDir * hit.normal);
    return ambient + diffuse;
    //return diffuse;
}


void BasicScene::render(Image& img){
    int width = cam.GetSize().x;
    int height = cam.GetSize().y;
    int currentIndex = 0;
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            img.SetPixelByIndex(currentIndex, getColor(x, y));
            currentIndex+=4;
        }
    }
    
}



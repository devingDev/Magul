
#include <limits>

#include "basicscene.h"
#include "constants.h"



BasicScene::BasicScene(){
    cam = Camera(90, WIDTH, HEIGHT);

    Color colors[] = {Color::white, Color::red, Color::green, Color::blue}; 

    
    std::cout << "COLTEST " << Color::white << "\n";
    std::cout << "COLTEST " << Color::red << "\n";
    sceneObjects.push_back(Sphere(Vector3(0,0,-5), 1.25, Color::white));
    sceneObjects.push_back(Sphere(Vector3(2,2,-5), 1.0, Color::red));
    sceneObjects.push_back(Sphere(Vector3(5,5,-5), 1.0, Color::green));
    sceneObjects.push_back(Sphere(Vector3(4,8,-5), 1.0, Color::blue));

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            sceneObjects.push_back(Sphere(Vector3(5+j*2,5+i*2,-5), 1.0, colors[j%4]));
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
        return (*smallestHit).color;
    }

    return Color::black;
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



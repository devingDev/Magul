
#include <limits>
#include <algorithm>

#include "basicscene.h"
#include "constants.h"





BasicScene::BasicScene(){
    std::cout << "Initializing scene" << "\n";
    cam = Camera(90, WIDTH, HEIGHT);

    Color colors[] = {Color::white, Color::red, Color::green, Color::blue}; 

    double radius = 2.0;
    sceneObjects.push_back(Sphere(Vector3(0,0,-15), radius, Color::white));
    sceneObjects.push_back(Sphere(Vector3(0,5,-15), radius, Color::red));

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
           sceneObjects.push_back(Sphere(Vector3(-10+(j*4 * (rand()%3)),-5+(i*3 * (rand()%3)),-15), radius, colors[j%4]));
        }
    }


    //directionalLights.push_back(DirectionalLight(Vector3(-2,-5,-0.5), Color(1.0,1.0,1.0,1.0)* 0.5));
    directionalLights.push_back(DirectionalLight(Vector3(-2,-5,0.5), Color::white));
    //sceneLights.push_back(&directionalLights[0]);

    directionalLights.push_back(DirectionalLight(Vector3(2,2,-0.5), Color::white));
    //sceneLights.push_back(&directionalLights[1]);


    pointLights.push_back(PointLight(Vector3(-3,-3, -13), Color(1.0,0.0,0.0, 1.0) * 15));
    //sceneLights.push_back(&pointLights[0]);

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
    //Vector3 lightDir(1,1,0.7);
    //lightDir.normalize();
    //Color ambient = hit.color * 0.1;
    Color ambient(1.0,0.5,0.5,0.5);
    //Color diffuse = multiply(0.9 * Math.max(0, dot(lightDir, hitnormal) ) , hit.color());
    Color diffuse = Color::black;
    Color specular = Color::black;
    for (int i = 0; i < directionalLights.size(); i++)
    {
        LightInfo lInfo = directionalLights[i].GetInfo(hit.point);
        //double dotProduct = hit.normal.dot(lInfo.direction);
        //double diffuseFactor = std::max(0.0, dotProduct);
        //diffuse +=  lInfo.incomingColor * diffuseFactor;
        double diffuseStr = std::max(0.0, lInfo.direction.dot(hit.normal));
        diffuse += lInfo.incomingColor * diffuseStr;
    }
    for (int i = 0; i < pointLights.size(); i++)
    {
        LightInfo lInfo = pointLights[i].GetInfo(hit.point);
        //diffuse += (hit.color * lInfo.incomingColor) * 0.9 * std::max(0.0, lInfo.direction * hit.normal);
        double diffuseStr = std::max(0.0, lInfo.direction.dot(hit.normal));
        diffuse += lInfo.incomingColor * diffuseStr;
    }
    
    
    //diffuse.clamp();

    Color phong = hit.color*(ambient + diffuse);
    phong.clamp();
    
    return phong;
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



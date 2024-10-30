
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


    directionalLights.push_back(DirectionalLight(Vector3(-1,-1,-1), Color(1.0,1.0,1.0,1.0)* 3));
    //directionalLights.push_back(DirectionalLight(Vector3(-1,-1,-0.7), Color::white));
    //directionalLights.push_back(DirectionalLight(Vector3(-1,-1,-0.7), Color(1.0, 1.0, 0.0, 0.0) * 1));
    //directionalLights.push_back(DirectionalLight(Vector3(1,-1,-0.7), Color::blue));
    //directionalLights.push_back(DirectionalLight(Vector3(-1,1,-0.7), Color::green));
    //sceneLights.push_back(&directionalLights[0]);

    //directionalLights.push_back(DirectionalLight(Vector3(-1,1,-0.3), Color::white));
    //sceneLights.push_back(&directionalLights[1]);


    //pointLights.push_back(PointLight(Vector3(-2,-2, -12), Color(1.0, 0.0, 0.0, 1.0) * 55));
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
    Color phongTotal = Color::black;

    // Ambient
    Color ambient = Color::gray;
    
    std::vector<LightInfo> lightInfos;

    // For directional lights
    for(int i = 0; i < directionalLights.size(); i++) {
        LightInfo lightInfo = (directionalLights[i]).GetInfo(hit.point);
        lightInfos.push_back(lightInfo);
    }
    // For point lights
    for(int i = 0; i < pointLights.size(); i++) {
        LightInfo lightInfo = (pointLights[i]).GetInfo(hit.point);
        lightInfos.push_back(lightInfo);
    }

    // Calculate each lightinfo for phong
    for(int i = 0; i < lightInfos.size(); i++) {
        Color diffuse = Color::black;
        Color specular = Color::black;

        // Diffuse
        double diffuseStrength = std::max(0.0, lightInfos[i].direction.dot(hit.normal));
        diffuse += lightInfos[i].incomingColor * diffuseStrength;

        // Specular
        double dotSurfaceNormalLightDir = hit.normal.dot(-lightInfos[i].direction);
        Vector3 reflected = (hit.normal * (2.0 * dotSurfaceNormalLightDir)) + lightInfos[i].direction;
        reflected.normalize();

        double dotReflectionView = std::max(0.0, reflected.dot(hit.ray.direction));
        double specularIntensivity = pow(dotReflectionView, 70);

        specular = lightInfos[i].incomingColor * specularIntensivity * 0.5 ;


        Color phong =  (ambient * 0.5 + diffuse + specular);
        //phong.normalize();


        phongTotal += phong;
    }

    phongTotal = hit.color * phongTotal;

    phongTotal.clamp();
    
    return phongTotal;
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



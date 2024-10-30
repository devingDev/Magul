
#include <limits>
#include <algorithm>

#include "basicscene.h"
#include "constants.h"





BasicScene::BasicScene(){
    std::cout << "Initializing scene" << "\n";
    cam = Camera(90, WIDTH, HEIGHT);

    Color colors[] = {Color::white, Color::red, Color::green, Color::blue}; 

    // Huge sphere just for casting a shadow on
    //sceneObjects.push_back(Sphere(Vector3(0,-29994,0), -30000, Color(1.0, 0.8, 0.8, 0.8)));
    sceneObjects.push_back(Sphere(Vector3(0,-29994,-800), 30000, Color(1.0, 0.8, 0.8, 0.8)));
    //sceneObjects.push_back(Sphere(Vector3(-17,17,-15), 3, Color::white));

    double radius = 2.0;
    //sceneObjects.push_back(Sphere(Vector3(0,0,-15), radius, Color::white));
    //sceneObjects.push_back(Sphere(Vector3(0,5,-15), radius, Color::red));

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
           //sceneObjects.push_back(Sphere(Vector3(-10+(j*4 * (rand()%3)),-5+(i*3 * (rand()%3)),-15), radius, colors[j%4]));
        }
    }
    /*sceneObjects.push_back(Sphere(Vector3(4, 0, -25), 4, Color::white));
    sceneObjects.push_back(Sphere(Vector3(-4, 0, -25), 4, Color::white));
    sceneObjects.push_back(Sphere(Vector3(5, -1, -20), 3, Color::red));
    sceneObjects.push_back(Sphere(Vector3(-5, -1, -20), 3, Color::red));
    sceneObjects.push_back(Sphere(Vector3(6, -2, -15), 2, Color::blue));
    sceneObjects.push_back(Sphere(Vector3(-6, -2, -15), 2, Color::blue));
    sceneObjects.push_back(Sphere(Vector3(7, -3, -12), 1, Color::green));
    sceneObjects.push_back(Sphere(Vector3(-7, -3, -12), 1, Color::green));
*/


    directionalLights.push_back(DirectionalLight(Vector3(1,1,0.7), Color::red));
    directionalLights.push_back(DirectionalLight(Vector3(-1,1,0.7), Color::green));
    directionalLights.push_back(DirectionalLight(Vector3(0,1,0), Color::blue));
    sceneObjects.push_back(Sphere(Vector3(0, 0, -10), 4, Color(1.0, 0.8, 0.8, 0.8)));

    //directionalLights.push_back(DirectionalLight(Vector3(11,10,0.7), Color::white));
    //directionalLights.push_back(DirectionalLight(Vector3(-1,-1,-1), Color(1.0,1.0,1.0,1.0)* 1));
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
        std::optional<Hit> hit = sceneObjects[i].intersect(cam.generateRay(x,y), i);
        if(hit){
            if((*hit).t < smallestT){
                smallestHit = hit;
                smallestT = (*hit).t;
            }
        }
    }

    if(smallestHit){
        return shade((*smallestHit));
        //return Color((*smallestHit).color);
    }

    return Color::black;
}

Color BasicScene::shade(Hit& hit){
    double ambBoost = 0.3;
    double epsilon = 0.0001;//std::numeric_limits<double>::epsilon()
    Color phongTotal = Color::black;

    std::vector<LightInfo> lightInfos;

    // Get infos for directional lights
    for(int i = 0; i < directionalLights.size(); i++) {
        LightInfo lightInfo = (directionalLights[i]).GetInfo(hit.point);
        lightInfos.push_back(lightInfo);
    }
    // Get infos for point lights
    for(int i = 0; i < pointLights.size(); i++) {
        LightInfo lightInfo = (pointLights[i]).GetInfo(hit.point);
        lightInfos.push_back(lightInfo);
    }



    // Calculate each lightinfo for phong
    for(int i = 0; i < lightInfos.size(); i++) {
        // check for shadowing
        bool isInShadow = false;
        for(int s = 0; s < sceneObjects.size(); s++){
            if(s == hit.index){
                continue;
            }
            Vector3 offsetPos = hit.point + (hit.normal * epsilon);
            Ray sRay(offsetPos, lightInfos[i].direction);
            std::optional<Hit> sHit = sceneObjects[s].intersect(sRay, i);
            if(sHit){
                if((*sHit).t > epsilon && (*sHit).t < sRay.tMax){
                    phongTotal = (phongTotal + hit.color * (lightInfos[i].incomingColor * ambBoost));
                    isInShadow = true;
                    s = sceneObjects.size()+1;
                    break;
                }else{
                    
                }
            }
        }

        if(!isInShadow){
            Color ambient = Color::black;
            Color diffuse = Color::black;
            Color specular = Color::black;

            // Ambient
            ambient = (hit.color * lightInfos[i].incomingColor) * ambBoost;

            // Diffuse
            double dotNS = lightInfos[i].direction.dot(hit.normal);
            double diffuseStrength = std::max(0.0, dotNS);
            diffuse = hit.color * lightInfos[i].incomingColor * diffuseStrength;

            // Specular
            if(dotNS == 0){
                specular = Color::black;
            }else{
                double dotSurfaceNormalLightDir = hit.normal.dot(-lightInfos[i].direction);
                Vector3 reflected = (hit.normal * (2.0 * dotSurfaceNormalLightDir)) + lightInfos[i].direction;
                //reflected.normalize();

                double dotReflectionView = std::max(0.0, reflected.dot(hit.ray.direction));
                double specularIntensivity = pow(dotReflectionView, 1000);

                specular = Color(1.0, 1.0, 1.0, 1.0) * lightInfos[i].incomingColor * specularIntensivity;
            }


            


            phongTotal = (phongTotal + ambient + diffuse + specular);
            phongTotal.clamp();
        }

    }
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



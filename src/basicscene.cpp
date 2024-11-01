
#include <limits>
#include <algorithm>
#include <cmath>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <chrono>

#include "basicscene.h"
#include "constants.h"



Material* BasicScene::getRandomMaterial(){
    return this->materials[std::rand() % this->materials.size()];
}

void BasicScene::InitializeSampleScene(){
    std::cout << "Initializing scene" << "\n";
    cam = Camera(90, WIDTH, HEIGHT);
    this->myImage = nullptr;

    Color colors[] = {Color::white, Color::red, Color::green, Color::blue}; 

    this->materials.push_back(new Material("../resources/textures/CustomUVChecker_byValle_8K.png", nullptr, Vector2(1,1), Vector2(0.0,-0.0), 1.0));
    this->materials.push_back(new Material("../resources/textures/CustomUVChecker_byValle_8K.png", nullptr, Vector2(0.25,0.25), Vector2(0.0,-0.0), 1.0));
    //this->materials.push_back(new Material("../resources/textures/test2.png", 0.0));
    //this->materials.push_back(new Material("../resources/textures/8ball.png", 1.0));
    //this->materials.push_back(new Material("../resources/textures/flushed.png", "../resources/textures/flushed_normal.png", 0.0));
    //this->materials.push_back(new Material("../resources/textures/flushed.png", nullptr, Vector2(0.25,0.25), Vector2(0.0,0.0), 0.2));

    sceneObjects.push_back(Sphere(Vector3(0, -1, -9), 2, Color::white, getRandomMaterial()));


    sceneObjects.push_back(Sphere(Vector3(4, 0, -25), 4, Color::white, getRandomMaterial()));
    sceneObjects.push_back(Sphere(Vector3(-4, 0, -25), 4, Color::white, getRandomMaterial()));
    sceneObjects.push_back(Sphere(Vector3(5, -1, -20), 3, Color::white, getRandomMaterial()));
    sceneObjects.push_back(Sphere(Vector3(-5, -1, -20), 3, Color::white, getRandomMaterial()));
    sceneObjects.push_back(Sphere(Vector3(6, -2, -15), 2, Color::white, getRandomMaterial()));
    sceneObjects.push_back(Sphere(Vector3(-6, -2, -15), 2, Color::white, getRandomMaterial()));
    sceneObjects.push_back(Sphere(Vector3(7, -3, -12), 1, Color::white, getRandomMaterial()));
    sceneObjects.push_back(Sphere(Vector3(-7, -3, -12), 1, Color::white, new Material("../resources/textures/flushed.png", nullptr, Vector2(0.25,0.25), Vector2(0.0,0.0), 0.2)));

    sceneObjects.push_back(Sphere(Vector3(0,-29994,-800), 30000, Color(1.0, 1.0, 1.0, 1.0), this->materials[0]));

    //sceneLights.push_back(new DirectionalLight(Vector3(11,10,0.7), Color::white, 0.7));
    sceneLights.push_back(new DirectionalLight(Vector3(11,10,11), Color::white, 0.7));
    sceneLights.push_back(new PointLight(Vector3(0,2, -30), Color::blue, 20));
    sceneLights.push_back(new PointLight(Vector3(0,2, 1), Color::red, 10));
}

BasicScene::BasicScene(){
    this->InitializeSampleScene();

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
            (*hit).mat = sceneObjects[i].material;
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
    double ambBoost = 0.5;
    double epsilon = 0.00001;//std::numeric_limits<double>::epsilon()
    Color phongTotal = Color::black;

    std::vector<LightInfo> lightInfos;

    // Get infos
    for(int i = 0; i < sceneLights.size(); i++) {
        LightInfo lightInfo = (*sceneLights[i]).GetInfo(hit.point);
        lightInfos.push_back(lightInfo);
    }

    // Calculate each lightinfo for phong
    for(int i = 0; i < lightInfos.size(); i++) {
        LightInfo& currLightInfo = lightInfos[i];
        Vector3 moveoriginSpherePoint = hit.point - sceneObjects[hit.index].position;
        Color matCol = Color::black;
        Vector3 normalOffset = Vector3(0,0,0);
        if(hit.mat != nullptr){
            matCol = hit.mat->GetColorFromSpherePoint(moveoriginSpherePoint, sceneObjects[hit.index].radius);
            normalOffset = hit.mat->GetNormalFromSpherePoint(moveoriginSpherePoint, sceneObjects[hit.index].radius);
        }
        // check for shadowing
        bool isInShadow = false;
        for(int s = 0; s < sceneObjects.size(); s++){
            if(s == hit.index){
                continue;
            }
            Vector3 offsetPos = hit.point + (hit.normal * epsilon);
            Ray sRay(offsetPos, currLightInfo.direction);
            std::optional<Hit> sHit = sceneObjects[s].intersect(sRay, i);
            if(sHit){
                Hit& shadowHit = *sHit; 
                if(shadowHit.t > epsilon && shadowHit.t < currLightInfo.tMax){
                    isInShadow = true;
                    //Color inShadowColor = hit.color * (currLightInfo.incomingColor * ambBoost);
                    Color inShadowColor = (hit.color * currLightInfo.incomingColor * ambBoost);
                    if(hit.mat != nullptr){
                        inShadowColor *= matCol;
                    }
                    phongTotal = (phongTotal + inShadowColor);
                    break;
                }else{
                    
                }
            }
        }

        if(!isInShadow){
            Color ambient = Color::black;
            Color diffuse = Color::black;
            Color specular = Color::black;

            if(currLightInfo.lightType == LightInfo::LightType::point){
                //currLightInfo.incomingColor *= 20;
            }

            // Ambient
            //ambient = (hit.color * currLightInfo.incomingColor);
            ambient = (hit.color * currLightInfo.incomingColor);
            if(hit.mat != nullptr){
                ambient *= matCol;
            }

            // Diffuse
            double dotNS = currLightInfo.direction.dot(hit.normal);
            double diffuseStrength = std::max(0.0, dotNS);
            //diffuse = hit.color * currLightInfo.incomingColor * diffuseStrength;
            diffuse = hit.color * currLightInfo.incomingColor * diffuseStrength;
            if(hit.mat != nullptr){
                diffuse *= matCol ;
            }

            // Specular
            if(dotNS < 0){
                specular = Color::black;
            }else{
                // calculate reflected
                double dotSurfaceNormalLightDir = hit.normal.dot(-currLightInfo.direction);
                Vector3 reflected = (hit.normal * (2.0 * dotSurfaceNormalLightDir)) + currLightInfo.direction;
                reflected.normalize();

                double dotReflectionView = std::max(0.0, reflected.dot(hit.ray.direction));
                double specularIntensivity = pow(dotReflectionView, 1000);

                specular = Color(1.0, 1.0, 1.0, 1.0) * currLightInfo.incomingColor * specularIntensivity;
                if(hit.mat != nullptr){
                    specular *= hit.mat->GetSpecularIntensity();
                }
            }


            phongTotal = (phongTotal + ambient * ambBoost + diffuse + specular);
        }
        phongTotal.clamp();

    }
    return phongTotal;
}

void BasicScene::expensive_task(int x, int y, Image* img, int currentIndex, int amount, int width){
    // Simulate an expensive task

    int maxY = y + amount;
    for(; y < maxY; y++){
        for(int x = 0; x < width; x++){
            img->SetPixelByIndex(currentIndex, getColor(x, y));
            currentIndex += 4;
        }
    }
    //std::cout << "thread info : " << x << " " << y << " " << currentIndex << " "
    //<< amount << " " << width << "\n";
}

void BasicScene::render(Image* img){
    this->myImage = img;
    int width = cam.GetSize().x;
    int height = cam.GetSize().y;
    int currentIndex = 0;
    int x = 0;
    int y = 0;
    bool doneStartingAll = false;

    const int numThreads = 100; // Number of threads
    const int rowsPerThread = height / numThreads;
    std::vector<std::future<void>> futures;
    // Start threads using std::async
    for (int i = 0; i < numThreads; ++i) {
        int currentY = y;
        int yourIndex = currentIndex;
        futures.push_back(std::async(

            std::launch::async, [this,i,currentY,img,yourIndex,rowsPerThread,width](){
                return this->expensive_task(0,currentY,this->myImage,yourIndex, rowsPerThread, width); // Ofcourse make foo public in your snippet
            }
        ));
        y += rowsPerThread;
        currentIndex += (4*width) * rowsPerThread;
    }

    if(y <= height){
        expensive_task(0, y, this->myImage, currentIndex, height-y, width);
    }

    // Wait for at least one thread to complete
    while (!futures.empty()) {
        // Wait for the first future to complete
        for (auto it = futures.begin(); it != futures.end(); ) {
            if (it->wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                it->get(); // Retrieve result (if any)
                it = futures.erase(it); // Remove finished future
                //std::cout << "A thread has completed.\n";
            } else {
                ++it;
            }
        }
        /*
        if(!doneStartingAll && futures.size() < numThreads){
            for (int i = 0; i < numThreads-futures.size(); ++i){
                int currentY = y;
                int yourIndex = currentIndex;
                futures.push_back(std::async(

                    std::launch::async, [this,i,currentY,img,yourIndex,rowsPerThread,width](){
                        return this->expensive_task(0,currentY,this->myImage,yourIndex, rowsPerThread, width); // Ofcourse make foo public in your snippet
                    }
                ));
                y += rowsPerThread;
                currentIndex += (4*width) * rowsPerThread;
                if(y >= height-rowsPerThread){
                    doneStartingAll = true;
                    break;
                }
            }
            
        }*/
    }

    return;
    currentIndex = 0;
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            //img.SetPixelByIndex(currentIndex, getColor(x, y));
            currentIndex+=4;
            if(currentIndex == 417792){
                std::cout << "test";
            }
        }
    }
    
}



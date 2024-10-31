#ifndef _BASIC_SCENE
#define _BASIC_SCENE

#include <vector>

#include "color.h"
#include "vector2.h"
#include "vector3.h"
#include "sphere.h"
#include "image.h"
#include "isampler.h"
#include "camera.h"
#include "ilight.h"
#include "directionallight.h"
#include "pointlight.h"
#include "material.h"

class BasicScene : public ISampler{
    private:
        std::vector<Sphere> sceneObjects;
        std::vector<Material*> materials;
        std::vector<ILight*> sceneLights;
        std::vector<DirectionalLight> directionalLights;
        std::vector<PointLight> pointLights;
        Camera cam;
        Image* myImage;
        void expensive_task(int x, int y, Image* img, int currIndex, int amount, int width);
    
    private:
        virtual Color getColor(Vector2 pos);
        virtual Color getColor(int x, int y);
        Color shade(Hit& hit);

    public:
        BasicScene();
        void render(Image* img);

};


#endif
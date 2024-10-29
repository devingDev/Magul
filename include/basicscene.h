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

class BasicScene : public ISampler{
    private:
        std::vector<Sphere> sceneObjects;
        Camera cam;
    
    private:
        virtual Color getColor(Vector2 pos);
        virtual Color getColor(int x, int y);

    public:
        BasicScene();
        void render(Image& img);

};


#endif
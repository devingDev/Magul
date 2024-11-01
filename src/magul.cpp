#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <unistd.h> 
#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <ctime>



#include "image.h"
#include "circle.h"
#include "color.h"
#include "vector2.h"
#include "vector3.h"
#include "camera.h"
#include "ray.h"
#include "hit.h"
#include "sphere.h"
#include "basicscene.h"
#include "constants.h"

SDL_Window * window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* tex = NULL;
Image* imgPointer;
Image image(WIDTH, HEIGHT);
SDL_Rect rect1;
std::vector<Circle> testCircles;
BasicScene* basicScene;


void printLastError(){
    printf("Last SDL Error: %s\n", SDL_GetError());
}

void FillImage(Image* img){
  basicScene->render(img);
  
  return;

  Color white(1.0, 1.0, 1.0, 1.0);
  int currentIndex = 0;
  for(int y = 0, maxY = img->GetWidth(); y < maxY; y++){
    for (int x = 0, maxX = img->GetHeight(); x < maxX; x++)
    {
      img->SetPixelByIndex(currentIndex, Color::black);

      for (size_t i = 0; i < testCircles.size(); i++)
      {
        if(testCircles[i].possiblyInPoint(x,y) && testCircles[i].coversPoint(x,y)){
          img->SetPixelByIndex(currentIndex, testCircles[i].GetColor());
        }
      }

      
      currentIndex+=4;
    }
  }
}

void CopyToSurface(Image& img, SDL_Surface* surf){
  for(int y = 0; y < surf->w; y++){
    for (int x = 0; x < surf->h; x++)
    {
      ((uint32_t*)surf->pixels)[y*img.GetWidth() + x] = image.GetPixelForSDL(x, y);
    }
  }
}

int main(int argc, char* argv[]){
  std::srand(std::time(nullptr));
  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::duration;
  using std::chrono::milliseconds;
  using std::chrono::nanoseconds;

  printf("Hello world!\n");
  
  int sdlInitResult = SDL_Init(
    SDL_INIT_EVERYTHING
  );
  if(sdlInitResult != 0){
    printLastError();
    return 1;
  }

  SDL_Log("Initialized SDL! %s", SDL_GetRevision());
  
  window = SDL_CreateWindow("Magul", SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


  Color colors[6] = { Color(1.0,0.5,0.0,0.0), Color(1.0,0.0,0.5,0.0) , Color(1.0,0.0,0.0,0.5), Color(1.0,0.5,0.5,0.0), Color(1.0,0.0,0.5,0.5), Color(1.0,0.5,0.0,0.5)};
  const int ROWS = 6, COLS = 6;
  testCircles.reserve(ROWS*COLS);
  for (size_t i = 0; i < COLS; i++)
  {
    for (size_t j = 0; j < ROWS; j++)
    {
      testCircles.push_back(Circle(18 * (j+1), colors[i], 250+100*j,250+100*i));
      colors[i].r += 1.0/COLS;
      colors[i].g += 1.0/COLS;
      colors[i].b += 1.0/COLS;
    }
  }
  
  


  Vector3 test1(5,2,-2);
  Vector3 test2(8,-3, 34);
  Vector3 test3 = test1 - test2;
  std::cout << test1 << "\n";
  std::cout << test3 << "\n";

  Vector3 testM1(2,3,4);
  Vector3 testM2(1,3,5);
  std::cout << "Dot product: " << testM1 * testM2 << "\n";

  Sphere s1(Vector3(0, 0, -2), 1, Color::white, nullptr);
  Sphere s2(Vector3(0, -1, -2), 1, Color::black, nullptr);
  Sphere s3(Vector3(0, 0, 0), 1, Color::green, nullptr);
  Ray r1(Vector3(0, 0, 0), Vector3(0, 0, -1));
  Ray r2(Vector3(0, 0, 0), Vector3(0, 1, -1));
  std::cout << (s1.intersect(r1,0)) << "\n";
  std::cout << (s1.intersect(r2,0)) << "\n";
  std::cout << (s2.intersect(r1,0)) << "\n";
  std::cout << (s3.intersect(r1,0)) << "\n";


    std::cout << "COLTEST " << Color::red << "\n";
  

  basicScene = new BasicScene();
  auto t1 = high_resolution_clock::now();
  imgPointer = &image;
  FillImage(imgPointer); // GENERATE IMAGE
  auto t2 = high_resolution_clock::now();
  auto ms_int = duration_cast<milliseconds>(t2 - t1);
  duration<double, std::milli> ms_double = t2 - t1;
  auto ns_int = duration_cast<nanoseconds>(t2 - t1);
  std::cout << ms_int.count() << "ms\n";
  std::cout << ms_double.count() << "ms\n";
  std::cout << ns_int.count() << "ns\n";

  




  SDL_Surface* surf = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
  CopyToSurface(image, surf);


  tex = SDL_CreateTextureFromSurface(renderer, surf);
  IMG_SavePNG(surf, "./render.png");
  IMG_SaveJPG(surf, "./render.jpg", 5);
  SDL_FreeSurface(surf);


  rect1.x = 8;
  rect1.y = 8;
  rect1.h = 8;
  rect1.w = 8;


  SDL_FlashWindow(window, SDL_FLASH_BRIEFLY);

  SDL_Event currEvent;
  bool isRunning = true;
  while(isRunning){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);


    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderCopy(renderer, tex, NULL, NULL);
    //SDL_RenderFillRect(renderer, &rect1);

    SDL_RenderPresent(renderer);

    while(SDL_PollEvent(&currEvent)!= 0){
      switch (currEvent.type) {
        case SDL_QUIT:
          isRunning = false;
          break;
        case SDL_KEYDOWN:
          switch (currEvent.key.keysym.sym) {
            case SDLK_q:
              isRunning = false;
              break;
          }

      }
    }

    SDL_Delay(1);
  }

  SDL_DestroyTexture(tex);
  SDL_DestroyRenderer(renderer);

  SDL_Quit();

  delete(basicScene);
  
  goto end;
  
  end:
  return 0;
}

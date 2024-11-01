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
Image* sceneImage;
SDL_Rect rect1;
BasicScene* basicScene;


void printLastError(){
    printf("Last SDL Error: %s\n", SDL_GetError());
}

void FillImage(Image* img){
  basicScene->render(img);
}

void CopyToSurface(Image* img, SDL_Surface* surf){
  for(int y = 0; y < surf->w; y++){
    for (int x = 0; x < surf->h; x++)
    {
      ((uint32_t*)surf->pixels)[y*img->GetWidth() + x] = img->GetPixelForSDL(x, y);
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
  

  // Create basic scene
  basicScene = new BasicScene();

  auto t1 = high_resolution_clock::now();
  sceneImage = new Image(WIDTH, HEIGHT);
  FillImage(sceneImage); // GENERATE IMAGE
  auto t2 = high_resolution_clock::now();
  auto ms_int = duration_cast<milliseconds>(t2 - t1);
  duration<double, std::milli> ms_double = t2 - t1;
  auto ns_int = duration_cast<nanoseconds>(t2 - t1);
  std::cout << ms_int.count() << "ms\n";
  std::cout << ms_double.count() << "ms\n";
  std::cout << ns_int.count() << "ns\n";

  
  // Create surface and convert image to surface pixels and copy them 
  SDL_Surface* surf = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
  CopyToSurface(sceneImage, surf);
  tex = SDL_CreateTextureFromSurface(renderer, surf);

  // Save to file as well
  std::string savePath = std::string(SDL_GetBasePath()) + "./render.png";
  IMG_SavePNG(surf, savePath.c_str());

  // free the surface
  SDL_FreeSurface(surf);


  rect1.x = 8;
  rect1.y = 8;
  rect1.h = 8;
  rect1.w = 8;


  //SDL_FlashWindow(window, SDL_FLASH_BRIEFLY);

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

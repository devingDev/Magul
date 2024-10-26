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
#include <vector>

#include "image.h"
#include "circle.h"
#include "color.h"
#include "vector2.h"

SDL_Window * window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* tex = NULL;
Image* image;
SDL_Rect rect1;
std::vector<Circle> testCircles;

Color white(1.0, 1.0, 1.0, 1.0);
Color black(1.0, 0.0, 0.0, 0.0);
Color red(1.0, 1.0, 0.0, 0.0);

const int WIDTH = 1024, HEIGHT = 1024;

void printLastError(){
    printf("Last SDL Error: %s\n", SDL_GetError());
}

void FillImage(Image* img){
  Color white(1.0, 1.0, 1.0, 1.0);
  int currentIndex = 0;
  for(int y = 0, maxY = img->GetWidth(); y < maxY; y++){
    for (int x = 0, maxX = img->GetHeight(); x < maxX; x++)
    {
      img->SetPixelByIndex(currentIndex, &white);
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

void CopyToSurface(Image* img, SDL_Surface* surf){
  for(int y = 0; y < surf->w; y++){
    for (int x = 0; x < surf->h; x++)
    {
      ((uint32_t*)surf->pixels)[y*img->GetWidth() + x] = image->GetPixelForSDL(x, y);
    }
  }
}

int main(int argc, char* argv[]){
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
  image = new Image(WIDTH, HEIGHT);


  Color colors[6] = { Color(1.0,0.5,0.0,0.0), Color(1.0,0.0,0.5,0.0) , Color(1.0,0.0,0.0,0.5), Color(1.0,0.5,0.5,0.0), Color(1.0,0.0,0.5,0.5), Color(1.0,0.5,0.0,0.5)};
  const int ROWS = 6, COLS = 6;
  testCircles.reserve(ROWS*COLS);
  for (size_t i = 0; i < ROWS; i++)
  {
    for (size_t j = 0; j < COLS; j++)
    {
      testCircles.push_back(Circle(12 * (j+1), colors[i], 250+100*j,250+100*i));
      colors[i].r += 1.0/COLS;
      colors[i].g += 1.0/COLS;
      colors[i].b += 1.0/COLS;
    }
  }
  

  auto t1 = high_resolution_clock::now();
  FillImage(image); // TESTING THIS ONE
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
    SDL_RenderFillRect(renderer, &rect1);

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

  delete(image);
  
  goto end;
  
  end:
  return 0;
}

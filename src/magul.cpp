#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <unistd.h> 
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>

#include "image.h"
#include "circle.h"
#include "color.h"
#include "vector2.h"

SDL_Window * window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* tex = NULL;
Image* image;
SDL_Rect rect1;

Color white(1.0, 1.0, 1.0, 1.0);
Color black(1.0, 0.0, 0.0, 0.0);
Color red(1.0, 1.0, 0.0, 0.0);

const int WIDTH = 1024, HEIGHT = 1024;

void printLastError(){
    printf("Last SDL Error: %s\n", SDL_GetError());
}


void FillImage(Image* img){
  Color white(1.0, 1.0, 1.0, 1.0);
  for(int y = 0; y < img->GetWidth(); y++){
    for (int x = 0; x < img->GetHeight(); x++)
    {
      image->SetPixel(x, y, black);
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
  FillImage(image);

  Circle c(2, white, 0, 0);
  Vector2 testPos(4,4);
  c.coversPoint(testPos);


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

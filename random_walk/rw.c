#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Window *window;
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
bool done = false;

void sdl_init() {

  SDL_Init(SDL_INIT_VIDEO); // initialize SDL3

  // TODO: use sdl_window_opengl flag, to create a window with opengl context
  window = SDL_CreateWindow("random_walk", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  if (window == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "sdl window is not created: %s\n",
                 SDL_GetError());
  }
}

int main(int argc, char *argv[]) {
  sdl_init();
  while (!done) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        done = true;
      }
    }
    // TODO: logic
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}

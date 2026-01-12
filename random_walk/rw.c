#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 640
#define HEIGHT 480

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  int width;
  int height;
} SDL_AppState;

SDL_AppResult SDL_AppInit(void **appState, int argc, char *argv[]) {
  SDL_AppState *state = malloc(sizeof(SDL_AppState));
  if (!state) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "malloc: %s\n", SDL_GetError());
    fprintf(stderr, "malloc: %s\n", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  *state = (SDL_AppState){
      .window = NULL,
      .renderer = NULL,
      .width = WIDTH,
      .height = HEIGHT,
  };

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed: %s\n",
                 SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!SDL_CreateWindowAndRenderer("Random Walk", state->width, state->height,
                                   0, &state->window, &state->renderer)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "SDL_CreateWindowAndRenderer failed: %s\n", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  *appState = state; // assign local state -> global state
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appState) {
  SDL_AppState *state = appState;
  SDL_SetRenderDrawColorFloat(state->renderer, 0.4f, 0.6f, 1.0f,
                              SDL_ALPHA_OPAQUE_FLOAT);
  SDL_RenderClear(state->renderer);

  SDL_RenderPresent(state->renderer);
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  SDL_AppState *state = appstate;
  SDL_DestroyWindow(state->window);
  free(state);
}

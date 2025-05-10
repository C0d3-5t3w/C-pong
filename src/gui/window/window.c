#include "window.h"
#include "../../main.h"
#include <SDL2/SDL.h>
#include <stdio.h>

static SDL_Window* window = NULL;
static int window_width = WINDOW_WIDTH;
static int window_height = WINDOW_HEIGHT;

bool window_init(const char* title, int width, int height) {
  window_width = width;
  window_height = height;
  
  // Create SDL window
  window = SDL_CreateWindow(title,
                          SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED,
                          width, height,
                          SDL_WINDOW_SHOWN);
  
  if (!window) {
    fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
    return false;
  }
  
  return true;
}

void window_cleanup(void) {
  if (window) {
    SDL_DestroyWindow(window);
    window = NULL;
  }
}

int window_get_width(void) { 
  return window_width; 
}

int window_get_height(void) { 
  return window_height; 
}

SDL_Window* window_get_sdl_window(void) {
  return window;
}

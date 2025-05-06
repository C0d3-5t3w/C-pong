#include "window.h"
#include "../../main.h"

static SDL_Window *window = NULL;
static int window_width = WINDOW_WIDTH;
static int window_height = WINDOW_HEIGHT;

bool window_init(const char *title, int width, int height) {
  window_width = width;
  window_height = height;

  window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width, height, SDL_WINDOW_SHOWN);

  return (window != NULL);
}

void window_cleanup(void) {
  if (window) {
    SDL_DestroyWindow(window);
    window = NULL;
  }
}

SDL_Window *window_get(void) { return window; }

int window_get_width(void) { return window_width; }

int window_get_height(void) { return window_height; }

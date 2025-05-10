#include "gui.h"
#include "../main.h"
#include "window/window.h"
#include "window/canvas/canvas.h"
#include <SDL2/SDL.h>
#include "../sdl_includes.h"
#include <stdio.h>
#include <stdlib.h>

static TTF_Font* font = NULL;
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

bool gui_init(void) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
    return false;
  }

  // Initialize SDL_ttf
  if (TTF_Init() != 0) {
    fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
    SDL_Quit();
    return false;
  }

  // Create window
  if (!window_init("C-Pong", WINDOW_WIDTH, WINDOW_HEIGHT)) {
    TTF_Quit();
    SDL_Quit();
    return false;
  }
  
  window = window_get_sdl_window();

  // Create renderer and canvas
  if (!canvas_init(window)) {
    window_cleanup();
    TTF_Quit();
    SDL_Quit();
    return false;
  }
  
  renderer = canvas_get_renderer();

  // Load font
  font = TTF_OpenFont("pkg/font.ttf", 16);
  if (!font) {
    // Try a system font if the custom one isn't available
    font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 16);
  }
  
  if (!font) {
    fprintf(stderr, "Font loading error: %s\n", TTF_GetError());
    // Continue without font - text rendering will be disabled but game can run
  }

  return true;
}

void gui_cleanup(void) {
  if (font) {
    TTF_CloseFont(font);
    font = NULL;
  }
  
  canvas_cleanup();
  window_cleanup();
  
  TTF_Quit();
  SDL_Quit();
}

void gui_clear(void) {
  canvas_clear();
}

void gui_present(void) {
  canvas_present();
}

void gui_draw_rectangle(int posX, int posY, int width, int height, bool filled) {
  Color color = {255, 255, 255, 255};
  
  if (filled) {
    canvas_draw_filled_rect(posX, posY, width, height, color);
  } else {
    canvas_draw_rect(posX, posY, width, height, color);
  }
}

void gui_draw_text(const char* text, int posX, int posY, bool centered) {
  Color color = {255, 255, 255, 255};
  canvas_draw_text(text, posX, posY, color, centered);
}

TTF_Font* gui_get_font(void) {
  return font;
}

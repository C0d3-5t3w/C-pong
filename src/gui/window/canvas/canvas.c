#include "canvas.h"
#include "../../../main.h"
#include "../../../gui/gui.h"
#include "../window.h"
#include "draw/draw.h"
#include <math.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../../../sdl_includes.h"

static SDL_Renderer* renderer = NULL;
extern TTF_Font* font; // Defined in gui.c

bool canvas_init(SDL_Window* window) {
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  return (renderer != NULL);
}

void canvas_cleanup(void) {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
  }
}

SDL_Renderer* canvas_get_renderer(void) {
  return renderer;
}

void canvas_clear(void) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void canvas_present(void) {
  SDL_RenderPresent(renderer);
}

void canvas_draw_rect(int x, int y, int width, int height, Color color) {
  SDL_Color sdlColor = {color.r, color.g, color.b, color.a};
  draw_rect(renderer, x, y, width, height, sdlColor);
}

void canvas_draw_filled_rect(int x, int y, int width, int height, Color color) {
  SDL_Color sdlColor = {color.r, color.g, color.b, color.a};
  draw_filled_rect(renderer, x, y, width, height, sdlColor);
}

void canvas_draw_circle(int x, int y, int radius, Color color) {
  SDL_Color sdlColor = {color.r, color.g, color.b, color.a};
  draw_circle(renderer, x, y, radius, sdlColor);
}

void canvas_draw_filled_circle(int x, int y, int radius, Color color) {
  SDL_Color sdlColor = {color.r, color.g, color.b, color.a};
  draw_filled_circle(renderer, x, y, radius, sdlColor);
}

void canvas_draw_text(const char* text, int x, int y, Color color, bool centered) {
  SDL_Color sdlColor = {color.r, color.g, color.b, color.a};
  TTF_Font* font = gui_get_font();
  if (font) {
    draw_text(renderer, font, text, x, y, sdlColor, centered);
  }
}

void canvas_draw_line(int x1, int y1, int x2, int y2, Color color) {
  SDL_Color sdlColor = {color.r, color.g, color.b, color.a};
  draw_line(renderer, x1, y1, x2, y2, sdlColor);
}

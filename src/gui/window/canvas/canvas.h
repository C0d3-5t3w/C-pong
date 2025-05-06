#ifndef CANVAS_H
#define CANVAS_H

#include "../window.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

// Function prototypes
bool canvas_init(SDL_Window *window);
void canvas_cleanup(void);
SDL_Renderer *canvas_get_renderer(void);
void canvas_clear(void);
void canvas_present(void);

// Drawing functions
void canvas_draw_rect(int x, int y, int width, int height, SDL_Color color);
void canvas_draw_filled_rect(int x, int y, int width, int height,
                             SDL_Color color);
void canvas_draw_circle(int x, int y, int radius, SDL_Color color);
void canvas_draw_filled_circle(int x, int y, int radius, SDL_Color color);
void canvas_draw_text(const char *text, int x, int y, SDL_Color color,
                      bool centered);
void canvas_draw_line(int x1, int y1, int x2, int y2, SDL_Color color);

#endif // CANVAS_H

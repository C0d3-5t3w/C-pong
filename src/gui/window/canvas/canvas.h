#ifndef CANVAS_H
#define CANVAS_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../../../main.h"

// Canvas initialization/cleanup
bool canvas_init(SDL_Window* window);
void canvas_cleanup(void);

// Basic canvas operations
void canvas_clear(void);
void canvas_present(void);
SDL_Renderer* canvas_get_renderer(void);

// Drawing primitives
void canvas_draw_rect(int x, int y, int width, int height, Color color);
void canvas_draw_filled_rect(int x, int y, int width, int height, Color color);
void canvas_draw_circle(int x, int y, int radius, Color color);
void canvas_draw_filled_circle(int x, int y, int radius, Color color);
void canvas_draw_text(const char *text, int x, int y, Color color, bool centered);
void canvas_draw_line(int x1, int y1, int x2, int y2, Color color);

#endif // CANVAS_H

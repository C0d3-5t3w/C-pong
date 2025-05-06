#ifndef DRAW_H
#define DRAW_H

#include "../canvas.h"
#include <stdbool.h>

// Drawing primitives - these just forward to canvas functions
void draw_rect(void* renderer, int x, int y, int width, int height, Color color);
void draw_filled_rect(void* renderer, int x, int y, int width, int height, Color color);
void draw_circle(void* renderer, int x, int y, int radius, Color color);
void draw_filled_circle(void* renderer, int x, int y, int radius, Color color);
void draw_line(void* renderer, int x1, int y1, int x2, int y2, Color color);
void draw_text(void* renderer, void* font, const char *text, int x, int y, Color color, bool centered);

#endif // DRAW_H

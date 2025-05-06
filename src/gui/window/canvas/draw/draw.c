#include "draw.h"
#include <math.h>

void draw_rect(void* renderer, int x, int y, int width, int height, Color color) {
  (void)renderer; // Unused in terminal mode
  canvas_draw_rect(x, y, width, height, color);
}

void draw_filled_rect(void* renderer, int x, int y, int width, int height, Color color) {
  (void)renderer; // Unused in terminal mode
  canvas_draw_filled_rect(x, y, width, height, color);
}

void draw_circle(void* renderer, int x, int y, int radius, Color color) {
  (void)renderer; // Unused in terminal mode
  canvas_draw_circle(x, y, radius, color);
}

void draw_filled_circle(void* renderer, int x, int y, int radius, Color color) {
  (void)renderer; // Unused in terminal mode
  canvas_draw_filled_circle(x, y, radius, color);
}

void draw_line(void* renderer, int x1, int y1, int x2, int y2, Color color) {
  (void)renderer; // Unused in terminal mode
  canvas_draw_line(x1, y1, x2, y2, color);
}

void draw_text(void* renderer, void* font, const char *text, int x, int y, Color color, bool centered) {
  (void)renderer; // Unused in terminal mode
  (void)font;     // Unused in terminal mode
  canvas_draw_text(text, x, y, color, centered);
}

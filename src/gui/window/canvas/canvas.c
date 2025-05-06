#include "canvas.h"
#include "../../../main.h"
#include "../../../gui/gui.h"
#include "../window.h"
#include <math.h>
#include <stdlib.h>

// Initialize canvas
bool canvas_init(void) {
  return true; // No additional initialization needed for terminal mode
}

void canvas_cleanup(void) {
  // No additional cleanup needed
}

void canvas_clear(void) {
  gui_clear();
}

void canvas_present(void) {
  gui_present();
}

void canvas_draw_rect(int x, int y, int width, int height, Color color) {
  (void)color; // Color not used in terminal mode
  
  // Constrain dimensions
  if (width <= 0 || height <= 0) return;
  width = width > 40 ? 40 : width;
  height = height > 20 ? 20 : height;
  
  // Draw rectangle using gui function
  gui_draw_rectangle(x, y, width, height, false);
}

void canvas_draw_filled_rect(int x, int y, int width, int height, Color color) {
  (void)color; // Color not used in terminal mode
  
  // Constrain dimensions
  if (width <= 0 || height <= 0) return;
  width = width > 40 ? 40 : width;
  height = height > 20 ? 20 : height;
  
  // Draw filled rectangle using gui function
  gui_draw_rectangle(x, y, width, height, true);
}

void canvas_draw_circle(int x, int y, int radius, Color color) {
  (void)color; // Color not used in terminal mode
  
  // Constrain radius
  if (radius <= 0) return;
  radius = radius > 20 ? 20 : radius;
  
  // Account for terminal character aspect ratio (approximately 2:1 height:width)
  // Use fewer points for a cleaner look
  for (double angle = 0; angle < 2 * M_PI; angle += 0.3) {
    int dx = (int)(radius * cos(angle) * 0.5);
    int dy = (int)(radius * sin(angle));
    int drawX = x + dx;
    int drawY = y + dy;
    
    if (drawX >= 0 && drawY >= 0 && drawX < window_get_width() && drawY < window_get_height()) {
      gui_draw_text("o", drawX, drawY, false);
    }
  }
}

void canvas_draw_filled_circle(int x, int y, int radius, Color color) {
  (void)color; // Color not used in terminal mode
  
  // Constrain radius
  if (radius <= 0) return;
  radius = radius > 20 ? 20 : radius;
  
  // Account for terminal character aspect ratio (approximately 2:1 height:width)
  for (int i = -radius; i <= radius; i++) {
    for (int j = -radius; j <= radius; j++) {
      // Scale the x coordinates to account for terminal aspect ratio
      if ((i*i*4 + j*j) <= radius*radius) {
        int drawX = x + (i/2);  // Scale x coordinate
        int drawY = y + j;
        
        if (drawX >= 0 && drawY >= 0 && drawX < window_get_width() && drawY < window_get_height()) {
          gui_draw_text("o", drawX, drawY, false);
        }
      }
    }
  }
}

void canvas_draw_text(const char *text, int x, int y, Color color, bool centered) {
  (void)color; // Color not used in terminal mode
  gui_draw_text(text, x, y, centered);
}

void canvas_draw_line(int x1, int y1, int x2, int y2, Color color) {
  (void)color; // Color not used in terminal mode
  
  // Use Bresenham's line algorithm for smooth lines
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int sx = x1 < x2 ? 1 : -1;
  int sy = y1 < y2 ? 1 : -1;
  int err = dx - dy;
  
  while (1) {
    if (x1 >= 0 && y1 >= 0 && x1 < window_get_width() && y1 < window_get_height()) {
      gui_draw_text("*", x1, y1, false);
    }
    
    if (x1 == x2 && y1 == y2) {
      break;
    }
    
    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x1 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y1 += sy;
    }
  }
}

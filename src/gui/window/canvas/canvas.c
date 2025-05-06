#include "canvas.h"
#include "../../../main.h"
#include "../../../gui/gui.h"
#include "../window.h"  // Add this include for window_get_width and window_get_height
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
  
  // Draw top and bottom horizontal lines
  for (int i = 0; i < width; i++) {
    gui_draw_text("-", x + i, y, false);
    gui_draw_text("-", x + i, y + height - 1, false);
  }
  
  // Draw left and right vertical lines
  for (int i = 0; i < height; i++) {
    gui_draw_text("|", x, y + i, false);
    gui_draw_text("|", x + width - 1, y + i, false);
  }
  
  // Draw corners
  gui_draw_text("+", x, y, false);
  gui_draw_text("+", x + width - 1, y, false);
  gui_draw_text("+", x, y + height - 1, false);
  gui_draw_text("+", x + width - 1, y + height - 1, false);
}

void canvas_draw_filled_rect(int x, int y, int width, int height, Color color) {
  (void)color; // Color not used in terminal mode
  
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      gui_draw_text("#", x + i, y + j, false);
    }
  }
}

void canvas_draw_circle(int x, int y, int radius, Color color) {
  (void)color; // Color not used in terminal mode
  
  for (int i = -radius; i <= radius; i++) {
    for (int j = -radius; j <= radius; j++) {
      int distance = (int)sqrt(i*i + j*j);
      if (abs(distance - radius) < 1) {
        int drawX = x + i;
        int drawY = y + j;
        
        if (drawX >= 0 && drawY >= 0 && drawX < window_get_width() && drawY < window_get_height()) {
          gui_draw_text("o", drawX, drawY, false);
        }
      }
    }
  }
}

void canvas_draw_filled_circle(int x, int y, int radius, Color color) {
  (void)color; // Color not used in terminal mode
  
  for (int i = -radius; i <= radius; i++) {
    for (int j = -radius; j <= radius; j++) {
      if ((i*i + j*j) <= radius*radius) {
        int drawX = x + i;
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
  
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int sx = x1 < x2 ? 1 : -1;
  int sy = y1 < y2 ? 1 : -1;
  int err = dx - dy;
  int e2;
  
  while (1) {
    if (x1 >= 0 && y1 >= 0 && x1 < window_get_width() && y1 < window_get_height()) {
      gui_draw_text("*", x1, y1, false);
    }
    
    if (x1 == x2 && y1 == y2) {
      break;
    }
    
    e2 = 2 * err;
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

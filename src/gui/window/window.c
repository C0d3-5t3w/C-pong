#include "window.h"
#include "../../main.h"
#include <stdio.h>

static int window_width = WINDOW_WIDTH;
static int window_height = WINDOW_HEIGHT;

bool window_init(const char *title, int width, int height) {
  (void)title; // Unused in terminal mode
  
  window_width = width;
  window_height = height;
  
  // Clear the terminal screen
  printf("\033[2J\033[H");
  
  return true;
}

void window_cleanup(void) {
  // Reset cursor position
  printf("\033[H");
}

int window_get_width(void) { return window_width; }

int window_get_height(void) { return window_height; }

void window_clear(void) {
  // Clear the terminal screen
  printf("\033[2J\033[H");
}

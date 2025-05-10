#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <stdbool.h>

// Window functions
bool window_init(const char* title, int width, int height);
void window_cleanup(void);
int window_get_width(void);
int window_get_height(void);
SDL_Window* window_get_sdl_window(void);

#endif // WINDOW_H

#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

// Drawing primitives
void draw_rect(SDL_Renderer *renderer, int x, int y, int width, int height,
               SDL_Color color);
void draw_filled_rect(SDL_Renderer *renderer, int x, int y, int width,
                      int height, SDL_Color color);
void draw_circle(SDL_Renderer *renderer, int x, int y, int radius,
                 SDL_Color color);
void draw_filled_circle(SDL_Renderer *renderer, int x, int y, int radius,
                        SDL_Color color);
void draw_line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2,
               SDL_Color color);
void draw_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x,
               int y, SDL_Color color, bool centered);

#endif // DRAW_H

#include "draw.h"
#include <math.h>
#include "../../../../sdl_includes.h"

void draw_rect(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_Rect rect = {x, y, width, height};
  SDL_RenderDrawRect(renderer, &rect);
}

void draw_filled_rect(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_Rect rect = {x, y, width, height};
  SDL_RenderFillRect(renderer, &rect);
}

void draw_circle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w;
      int dy = radius - h;
      if ((dx*dx + dy*dy) >= (radius*radius - radius) && 
          (dx*dx + dy*dy) <= (radius*radius + radius)) {
        SDL_RenderDrawPoint(renderer, x + dx, y + dy);
      }
    }
  }
}

void draw_filled_circle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w;
      int dy = radius - h;
      if ((dx*dx + dy*dy) <= (radius*radius)) {
        SDL_RenderDrawPoint(renderer, x + dx, y + dy);
      }
    }
  }
}

void draw_line(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void draw_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color, bool centered) {
  SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
  if (!surface) {
    return;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (!texture) {
    SDL_FreeSurface(surface);
    return;
  }

  SDL_Rect rect;
  rect.w = surface->w;
  rect.h = surface->h;

  if (centered) {
    rect.x = x - rect.w / 2;
    rect.y = y - rect.h / 2;
  } else {
    rect.x = x;
    rect.y = y;
  }

  SDL_RenderCopy(renderer, texture, NULL, &rect);

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

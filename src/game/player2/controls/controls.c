#include "controls.h"

static bool moveUp = false;
static bool moveDown = false;

void player2_controls_init(void) {
  moveUp = false;
  moveDown = false;
}

void player2_controls_handle_event(SDL_Event *event) {
  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
    case SDLK_UP:
      moveUp = true;
      break;
    case SDLK_DOWN:
      moveDown = true;
      break;
    }
  } else if (event->type == SDL_KEYUP) {
    switch (event->key.keysym.sym) {
    case SDLK_UP:
      moveUp = false;
      break;
    case SDLK_DOWN:
      moveDown = false;
      break;
    }
  }
}

bool player2_controls_is_moving_up(void) { return moveUp; }

bool player2_controls_is_moving_down(void) { return moveDown; }

#include "controls.h"
#include "../../../main.h"

static bool moveUp = false;
static bool moveDown = false;

void player2_controls_init(void) {
  moveUp = false;
  moveDown = false;
}

void player2_controls_handle_event(Event *event) {
  if (event->type == EVENT_KEYDOWN) {
    switch (event->key.sym) {
    case KEY_UP:
      moveUp = true;
      break;
    case KEY_DOWN:
      moveDown = true;
      break;
    }
  } else if (event->type == EVENT_KEYUP) {
    switch (event->key.sym) {
    case KEY_UP:
      moveUp = false;
      break;
    case KEY_DOWN:
      moveDown = false;
      break;
    }
  }
}

bool player2_controls_is_moving_up(void) { return moveUp; }

bool player2_controls_is_moving_down(void) { return moveDown; }

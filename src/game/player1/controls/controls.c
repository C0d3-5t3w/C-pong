#include "controls.h"
#include "../../../main.h"

static bool moveUp = false;
static bool moveDown = false;

void player1_controls_init(void) {
  moveUp = false;
  moveDown = false;
}

void player1_controls_handle_event(Event *event) {
  if (event->type == EVENT_KEYDOWN) {
    switch (event->key.sym) {
    case KEY_W:
      moveUp = true;
      break;
    case KEY_S:
      moveDown = true;
      break;
    }
  } else if (event->type == EVENT_KEYUP) {
    switch (event->key.sym) {
    case KEY_W:
      moveUp = false;
      break;
    case KEY_S:
      moveDown = false;
      break;
    }
  }
}

bool player1_controls_is_moving_up(void) { return moveUp; }

bool player1_controls_is_moving_down(void) { return moveDown; }

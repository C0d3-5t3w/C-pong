#include "controls.h"
#include "../../../main.h"

static bool moveUp = false;
static bool moveDown = false;

void player1_controls_init(void) {
  moveUp = false;
  moveDown = false;
}

void player1_controls_handle_event(Event *event) {
  // Check current key states for continuous movement
  moveUp = is_key_pressed(KEY_W);
  moveDown = is_key_pressed(KEY_S);
}

bool player1_controls_is_moving_up(void) { 
  // Check direct key state for more responsive controls
  return is_key_pressed(KEY_W) || moveUp;
}

bool player1_controls_is_moving_down(void) { 
  // Check direct key state for more responsive controls
  return is_key_pressed(KEY_S) || moveDown;
}

#include "controls.h"
#include "../../../main.h"

static bool moveUp = false;
static bool moveDown = false;

void player2_controls_init(void) {
  moveUp = false;
  moveDown = false;
}

void player2_controls_handle_event(Event *event) {
  // Check current key states for continuous movement
  moveUp = is_key_pressed(KEY_UP);
  moveDown = is_key_pressed(KEY_DOWN);
}

bool player2_controls_is_moving_up(void) { 
  // Check direct key state for more responsive controls
  return is_key_pressed(KEY_UP) || moveUp;
}

bool player2_controls_is_moving_down(void) { 
  // Check direct key state for more responsive controls
  return is_key_pressed(KEY_DOWN) || moveDown;
}

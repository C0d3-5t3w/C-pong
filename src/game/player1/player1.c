#include "player1.h"
#include "../../gui/gui.h"
#include "../../main.h"
#include "controls/controls.h"

// Default color for player1
static Color playerColor = {255, 0, 0, 255}; // Red

void player1_init(Player *player) {
  player->width = 1;
  player->height = 4;
  player->x = 2;
  player->y = (WINDOW_HEIGHT - player->height) / 2;
  player->speed = 1;
  player->color = playerColor;
  
  player1_controls_init();
}

void player1_update(Player *player) {
  // Move paddle based on keyboard input
  if (player1_controls_is_moving_up() && player->y > 0) {
    player->y -= player->speed;
  }

  if (player1_controls_is_moving_down() && player->y < WINDOW_HEIGHT - player->height) {
    player->y += player->speed;
  }
}

void player1_render(Player *player) {
  // Draw the paddle as a vertical line of characters
  for (int i = 0; i < player->height; i++) {
    gui_draw_text("#", player->x, player->y + i, false);
  }
}

void player1_handle_event(Event *event, Player *player) {
  (void)player; // Unused parameter
  player1_controls_handle_event(event);
}

void player1_set_color(Color color) { playerColor = color; }

Color player1_get_color(void) { return playerColor; }

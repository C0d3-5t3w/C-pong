#include "player2.h"
#include "../../gui/gui.h"
#include "../../main.h"
#include "controls/controls.h"

// Default color for player2
static Color playerColor = {0, 0, 255, 255}; // Blue

void player2_init(Player *player) {
  player->width = 1;
  player->height = 4;
  player->x = WINDOW_WIDTH - 3;
  player->y = (WINDOW_HEIGHT - player->height) / 2;
  player->speed = 1;
  player->color = playerColor;
  
  player2_controls_init();
}

void player2_update(Player *player) {
  // Move paddle based on keyboard input
  if (player2_controls_is_moving_up() && player->y > 0) {
    player->y -= player->speed;
  }

  if (player2_controls_is_moving_down() && player->y < WINDOW_HEIGHT - player->height) {
    player->y += player->speed;
  }
}

void player2_render(Player *player) {
  // Draw the paddle as a vertical line of characters
  for (int i = 0; i < player->height; i++) {
    gui_draw_text("#", player->x, player->y + i, false);
  }
}

void player2_handle_event(Event *event, Player *player) {
  (void)player; // Unused parameter
  player2_controls_handle_event(event);
}

void player2_set_color(Color color) { playerColor = color; }

Color player2_get_color(void) { return playerColor; }

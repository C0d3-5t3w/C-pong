#include "player2.h"
#include "../../gui/gui.h"
#include "../../main.h"
#include "controls/controls.h"

// Movement flags
static SDL_Color playerColor = {0, 0, 255, 255}; // Default: Blue

void player2_init(Player *player) {
  player->width = 20;
  player->height = 100;
  player->x = WINDOW_WIDTH - 40;
  player->y = (WINDOW_HEIGHT - player->height) / 2;
  player->speed = 5;
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
  SDL_Rect paddleRect = {player->x, player->y, player->width, player->height};
  SDL_SetRenderDrawColor(gui_get_renderer(), player->color.r, player->color.g,
                         player->color.b, player->color.a);
  SDL_RenderFillRect(gui_get_renderer(), &paddleRect);
}

void player2_handle_event(SDL_Event *event, Player *player) {
  (void)player; // Unused parameter
  player2_controls_handle_event(event);
}

void player2_set_color(SDL_Color color) { playerColor = color; }

SDL_Color player2_get_color(void) { return playerColor; }

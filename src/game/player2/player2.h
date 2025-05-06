#ifndef PLAYER2_H
#define PLAYER2_H

#include "../player1/player1.h" // For Player structure
#include <SDL2/SDL.h>

void player2_init(Player *player);
void player2_update(Player *player);
void player2_render(Player *player);
void player2_handle_event(SDL_Event *event, Player *player);
void player2_set_color(SDL_Color color);
SDL_Color player2_get_color(void);

#endif // PLAYER2_H

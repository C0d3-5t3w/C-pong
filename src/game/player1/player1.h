#ifndef PLAYER1_H
#define PLAYER1_H

#include "../../main.h"
#include "../game.h"

// Function prototypes
void player1_init(Player *player);
void player1_update(Player *player);
void player1_render(Player *player);
void player1_handle_event(Event *event, Player *player);
void player1_set_color(Color color);
Color player1_get_color(void);

#endif // PLAYER1_H

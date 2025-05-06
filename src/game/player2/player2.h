#ifndef PLAYER2_H
#define PLAYER2_H

#include "../game.h"
#include "../../main.h"

// Function prototypes
void player2_init(Player *player);
void player2_update(Player *player);
void player2_render(Player *player);
void player2_handle_event(Event *event, Player *player);
void player2_set_color(Color color);
Color player2_get_color(void);

#endif // PLAYER2_H

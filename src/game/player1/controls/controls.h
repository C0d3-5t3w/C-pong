#ifndef PLAYER1_CONTROLS_H
#define PLAYER1_CONTROLS_H

#include "../../../main.h"
#include <stdbool.h>

// Function prototypes
void player1_controls_init(void);
void player1_controls_handle_event(Event *event);
bool player1_controls_is_moving_up(void);
bool player1_controls_is_moving_down(void);

#endif // PLAYER1_CONTROLS_H

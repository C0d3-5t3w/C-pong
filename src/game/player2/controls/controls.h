#ifndef PLAYER2_CONTROLS_H
#define PLAYER2_CONTROLS_H

#include <SDL2/SDL.h>
#include <stdbool.h>

// Function prototypes
void player2_controls_init(void);
void player2_controls_handle_event(SDL_Event *event);
bool player2_controls_is_moving_up(void);
bool player2_controls_is_moving_down(void);

#endif // PLAYER2_CONTROLS_H

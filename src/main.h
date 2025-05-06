#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h> // for usleep

#include "config/config.h"
#include "game/game.h"
#include "gui/gui.h"

#define WINDOW_WIDTH 80
#define WINDOW_HEIGHT 24
#define FPS 10
#define FRAME_DELAY (1000 / FPS)

// Custom color structure to replace SDL_Color
typedef struct {
    unsigned char r, g, b, a;
} Color;

// Custom rectangle structure to replace SDL_Rect
typedef struct {
    int x, y, w, h;
} Rectangle;

// Custom event structure to replace SDL_Event
typedef struct {
    int type;
    struct {
        int sym;
    } key;
} Event;

// Event types
#define EVENT_KEYDOWN 1
#define EVENT_KEYUP 2
#define EVENT_QUIT 3

// Key codes
#define KEY_UP     1
#define KEY_DOWN   2
#define KEY_LEFT   3
#define KEY_RIGHT  4
#define KEY_W      5
#define KEY_S      6
#define KEY_P      7
#define KEY_ESCAPE 8
#define KEY_RETURN 9

// Game states
typedef enum { STATE_MENU, STATE_GAME, STATE_SETTINGS, STATE_EXIT } GameState;

extern GameState currentState;

// Function prototypes for core functionality
bool poll_event(Event* event);
void delay_ms(int ms);
unsigned int get_ticks(void);

#endif // MAIN_H

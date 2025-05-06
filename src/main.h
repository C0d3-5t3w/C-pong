#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h> // for usleep

// Use a smaller, fixed window size for better stability
#define WINDOW_WIDTH 80
#define WINDOW_HEIGHT 25
#define FPS 10
#define FRAME_DELAY (1000 / FPS)

// Custom color structure 
typedef struct {
    unsigned char r, g, b, a;
} Color;

// Custom rectangle structure
typedef struct {
    int x, y, w, h;
} Rectangle;

// Custom event structure
typedef struct {
    int type;
    struct {
        int sym;
    } key;
} Event;

// Event types
#define EVENT_NONE    0
#define EVENT_KEYDOWN 1
#define EVENT_KEYUP   2
#define EVENT_QUIT    3

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

// Function prototypes
bool poll_event(Event* event);
bool is_key_pressed(int key); // Add this function declaration
void delay_milliseconds(int milliseconds);
unsigned int get_ticks(void);

// Forward declarations for menu functions
void menu_init(void);
void menu_handle_event(Event* event);
void menu_update(void);
void menu_render(void);

// Forward declarations for settings functions
void settings_init(void);
void settings_handle_event(Event* event);
void settings_update(void);
void settings_render(void);

// Forward declarations for scores functions
bool scores_save(void);

#endif // MAIN_H

#ifndef GAME_H
#define GAME_H

#include "../main.h"
#include <stdbool.h>

// Ball structure
typedef struct {
  float x;
  float y;
  float velocityX;
  float velocityY;
  int size;
  Color color;
} Ball;

// Player structure definition (moved from player1.h)
typedef struct {
  int x;
  int y;
  int width;
  int height;
  int speed;
  Color color;
} Player;

// CPU structure definition (moved from cpu.h)
typedef struct {
  int x;
  int y;
  int width;
  int height;
  int speed;
  Color color;
  int difficulty; // 1=Easy, 2=Medium, 3=Hard
} CPU;

// Game mode enum
typedef enum { MODE_PLAYER_VS_CPU, MODE_PLAYER_VS_PLAYER } GameMode;

// Function prototypes
void game_init(void);
void game_cleanup(void);
void game_reset(void);
void game_update(void);
void game_render(void);
void game_handle_event(Event *event);
void game_set_mode(GameMode mode);
GameMode game_get_mode(void);
Ball *game_get_ball(void);

#endif // GAME_H

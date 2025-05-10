#include "game.h"
#include "../gui/gui.h"
#include "../main.h"
#include "player1/player1.h"
#include "player2/player2.h"
#include "cpu/cpu.h"
#include "scores/scores.h"
#include <math.h>
#include <SDL2/SDL_ttf.h>

// Game objects
static Ball ball;
static Player player1;
static Player player2;
static CPU cpu;
static GameMode gameMode = MODE_PLAYER_VS_CPU;
static bool gamePaused = false;

void game_init(void) {
  // Initialize ball
  ball.size = 1;
  game_reset();
  ball.color = (Color){255, 255, 255, 255}; // White

  // Initialize players
  player1_init(&player1);
  player2_init(&player2);
  cpu_init(&cpu);

  // Initialize scores
  scores_init();
}

void game_cleanup(void) { scores_save(); }

void game_reset(void) {
  // Reset ball position
  ball.x = WINDOW_WIDTH / 2.0F;
  ball.y = WINDOW_HEIGHT / 2.0F;

  // Set random initial velocity
  float angle = (((float)rand() / RAND_MAX) * M_PI / 2) - M_PI / 4;
  if (rand() % 2) {
    angle += M_PI;
  }

  float speed = 1.0F;
  ball.velocityX = speed * (float)cos((double)angle);
  ball.velocityY = speed * (float)sin((double)angle) * 0.5F; // Adjust for console aspect ratio
}

// Check if two rectangles intersect
static bool rectangles_intersect(Rectangle rect1, Rectangle rect2) {
    return (rect1.x < rect2.x + rect2.w &&
            rect1.x + rect1.w > rect2.x &&
            rect1.y < rect2.y + rect2.h &&
            rect1.y + rect1.h > rect2.y);
}

void game_update(void) {
  if (gamePaused) {
    return;
  }

  // Update player paddles
  player1_update(&player1);

  if (gameMode == MODE_PLAYER_VS_CPU) {
    cpu_update(&cpu, &ball);
  } else {
    player2_update(&player2);
  }

  // Move ball
  ball.x += ball.velocityX;
  ball.y += ball.velocityY;

  // Ball collision with top and bottom of screen
  if (ball.y <= 0 || ball.y >= WINDOW_HEIGHT - ball.size) {
    ball.velocityY = -ball.velocityY;
  }

  // Ball collision with paddles
  Rectangle ballRect = {(int)ball.x, (int)ball.y, ball.size, ball.size};
  Rectangle p1Rect = {player1.x, player1.y, player1.width, player1.height};
  Rectangle p2Rect;

  if (gameMode == MODE_PLAYER_VS_CPU) {
    p2Rect = (Rectangle){cpu.x, cpu.y, cpu.width, cpu.height};
  } else {
    p2Rect = (Rectangle){player2.x, player2.y, player2.width, player2.height};
  }

  if (rectangles_intersect(ballRect, p1Rect)) {
    if (ball.velocityX < 0) {
      ball.velocityX = -ball.velocityX;
      // Add some variation based on where the ball hit the paddle
      float hitPosition = (ball.y - player1.y) / player1.height;
      ball.velocityY = (hitPosition - 0.5F) * 2.0F;
    }
  }

  if (rectangles_intersect(ballRect, p2Rect)) {
    if (ball.velocityX > 0) {
      ball.velocityX = -ball.velocityX;
      // Add some variation based on where the ball hit the paddle
      float hitPosition;
      if (gameMode == MODE_PLAYER_VS_CPU) {
        hitPosition = (ball.y - cpu.y) / cpu.height;
      } else {
        hitPosition = (ball.y - player2.y) / player2.height;
      }
      ball.velocityY = (hitPosition - 0.5F) * 2.0F;
    }
  }

  // Ball out of bounds (scoring)
  if (ball.x < 0) {
    // Player 2 or CPU scores
    if (gameMode == MODE_PLAYER_VS_CPU) {
      scores_add_cpu_score();
    } else {
      scores_add_p2_score();
    }
    game_reset();
  } else if (ball.x > WINDOW_WIDTH) {
    // Player 1 scores
    scores_add_p1_score();
    game_reset();
  }
}

void game_render(void) {
  // Draw middle line
  for (int row = 2; row < WINDOW_HEIGHT - 2; row += 2) {
    gui_draw_text("|", WINDOW_WIDTH / 2 - 1, row, false);
  }

  // Draw ball
  gui_draw_text("O", (int)ball.x, (int)ball.y, false);

  // Draw players
  player1_render(&player1);

  if (gameMode == MODE_PLAYER_VS_CPU) {
    cpu_render(&cpu);
  } else {
    player2_render(&player2);
  }

  // Draw scores
  scores_render();

  // Draw pause information if paused
  if (gamePaused) {
    gui_draw_text("PAUSED - Press P to continue", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, true);
  }
}

void game_handle_event(Event *event) {
  // Handle pause toggle
  if (event->type == EVENT_KEYDOWN && event->key.sym == KEY_P) {
    gamePaused = !gamePaused;
  }

  // Handle escape to return to menu
  if (event->type == EVENT_KEYDOWN && event->key.sym == KEY_ESCAPE) {
    currentState = STATE_MENU;
  }

  // Pass events to players for control handling
  player1_handle_event(event, &player1);

  if (gameMode == MODE_PLAYER_VS_PLAYER) {
    player2_handle_event(event, &player2);
  }
}

void game_set_mode(GameMode mode) { gameMode = mode; }

GameMode game_get_mode(void) { return gameMode; }

Ball *game_get_ball(void) { return &ball; }

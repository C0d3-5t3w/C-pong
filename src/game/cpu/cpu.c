#include "cpu.h"
#include "../../gui/gui.h"
#include "../../main.h"
#include "ai/ai.h"

static int difficulty = 2;                    // Default: Medium
static SDL_Color cpuColor = {0, 255, 0, 255}; // Default: Green

void cpu_init(CPU *cpu) {
  cpu->width = 20;
  cpu->height = 100;
  cpu->x = WINDOW_WIDTH - 40;
  cpu->y = (WINDOW_HEIGHT - cpu->height) / 2;
  cpu->speed = 3; // Base speed, will be adjusted by difficulty
  cpu->color = cpuColor;
  cpu->difficulty = difficulty;
}

void cpu_update(CPU *cpu, Ball *ball) {
  // Adjust CPU speed based on difficulty
  switch (cpu->difficulty) {
  case 1: // Easy
    cpu->speed = 3;
    break;
  case 2: // Medium
    cpu->speed = 5;
    break;
  case 3: // Hard
    cpu->speed = 7;
    break;
  }

  // Call AI to determine movement
  float targetY = ai_calculate_target_y(ball, cpu->difficulty);

  // Add some "reaction delay" based on difficulty
  if (cpu->difficulty < 3) {
    // Only move if the ball is moving towards the CPU
    if (ball->velocityX > 0) {
      // Move towards the predicted position
      if (targetY < (float)(cpu->y + cpu->height / 2) - 10.0f) {
        cpu->y -= cpu->speed;
      } else if (targetY > (float)(cpu->y + cpu->height / 2) + 10.0f) {
        cpu->y += cpu->speed;
      }
    }
  } else {
    // Hard difficulty: better prediction, faster movement
    if (targetY < (float)(cpu->y + cpu->height / 2) - 5.0f) {
      cpu->y -= cpu->speed;
    } else if (targetY > (float)(cpu->y + cpu->height / 2) + 5.0f) {
      cpu->y += cpu->speed;
    }
  }

  // Ensure CPU paddle stays within screen boundaries
  if (cpu->y < 0) {
    cpu->y = 0;
  } else if (cpu->y > WINDOW_HEIGHT - cpu->height) {
    cpu->y = WINDOW_HEIGHT - cpu->height;
  }
}

void cpu_render(CPU *cpu) {
  SDL_Rect paddleRect = {cpu->x, cpu->y, cpu->width, cpu->height};
  SDL_SetRenderDrawColor(gui_get_renderer(), cpu->color.r, cpu->color.g,
                         cpu->color.b, cpu->color.a);
  SDL_RenderFillRect(gui_get_renderer(), &paddleRect);
}

void cpu_set_difficulty(int newDifficulty) { difficulty = newDifficulty; }

int cpu_get_difficulty(void) { return difficulty; }

void cpu_set_color(SDL_Color color) { cpuColor = color; }

SDL_Color cpu_get_color(void) { return cpuColor; }

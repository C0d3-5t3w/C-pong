#include "cpu.h"
#include "../../gui/gui.h"
#include "../../main.h"
#include "ai/ai.h"

static int difficulty = 2;                   // Default: Medium
static Color cpuColor = {0, 255, 0, 255};    // Default: Green

void cpu_init(CPU *cpu) {
  cpu->width = 1;
  cpu->height = 4;
  cpu->x = WINDOW_WIDTH - 3;
  cpu->y = (WINDOW_HEIGHT - cpu->height) / 2;
  cpu->speed = 1; // Base speed, will be adjusted by difficulty
  cpu->color = cpuColor;
  cpu->difficulty = difficulty;
}

void cpu_update(CPU *cpu, Ball *ball) {
  // Adjust CPU speed based on difficulty
  switch (cpu->difficulty) {
  case 1: // Easy
    cpu->speed = 1;
    break;
  case 2: // Medium
    cpu->speed = 1;
    break;
  case 3: // Hard
    cpu->speed = 2;
    break;
  }

  // Call AI to determine movement
  float targetY = ai_calculate_target_y(ball, cpu->difficulty);

  // Add some "reaction delay" based on difficulty
  if (cpu->difficulty < 3) {
    // Only move if the ball is moving towards the CPU
    if (ball->velocityX > 0) {
      // Move towards the predicted position
      float paddleCenterY = (float)cpu->y + (float)cpu->height / 2.0F; // Fixed integer division
      if (targetY < paddleCenterY - 1.0F) {
        cpu->y -= cpu->speed;
      } else if (targetY > paddleCenterY + 1.0F) {
        cpu->y += cpu->speed;
      }
    }
  } else {
    // Hard difficulty: better prediction, faster movement
    float paddleCenterY = (float)cpu->y + (float)cpu->height / 2.0F; // Fixed integer division
    if (targetY < paddleCenterY - 0.5F) {
      cpu->y -= cpu->speed;
    } else if (targetY > paddleCenterY + 0.5F) {
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
  // Draw the paddle as a vertical line of characters
  for (int i = 0; i < cpu->height; i++) {
    gui_draw_text("#", cpu->x, cpu->y + i, false);
  }
}

void cpu_set_difficulty(int newDifficulty) { difficulty = newDifficulty; }

int cpu_get_difficulty(void) { return difficulty; }

void cpu_set_color(Color color) { cpuColor = color; }

Color cpu_get_color(void) { return cpuColor; }

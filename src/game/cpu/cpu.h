#ifndef CPU_H
#define CPU_H

#include "../game.h"            // For Ball structure
#include "../player1/player1.h" // For Player structure
#include <SDL2/SDL.h>

typedef struct {
  int x;
  int y;
  int width;
  int height;
  int speed;
  SDL_Color color;
  int difficulty; // 1=Easy, 2=Medium, 3=Hard
} CPU;

void cpu_init(CPU *cpu);
void cpu_update(CPU *cpu, Ball *ball);
void cpu_render(CPU *cpu);
void cpu_set_difficulty(int difficulty);
int cpu_get_difficulty(void);
void cpu_set_color(SDL_Color color);
SDL_Color cpu_get_color(void);

#endif // CPU_H

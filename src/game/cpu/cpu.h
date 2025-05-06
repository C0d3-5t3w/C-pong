#ifndef CPU_H
#define CPU_H

#include "../../main.h"
#include "../game.h"

// Function prototypes
void cpu_init(CPU *cpu);
void cpu_update(CPU *cpu, Ball *ball);
void cpu_render(CPU *cpu);
void cpu_set_difficulty(int difficulty);
int cpu_get_difficulty(void);
void cpu_set_color(Color color);
Color cpu_get_color(void);

#endif // CPU_H

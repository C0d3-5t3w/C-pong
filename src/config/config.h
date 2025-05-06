#ifndef CONFIG_H
#define CONFIG_H

#include "../game/menu/settings/settings.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

// Function prototypes
bool config_init(void);
bool config_save(void);
bool config_load(void);

// Getters and setters
int config_get_difficulty(void);
void config_set_difficulty(int difficulty);

void config_get_colors(ColorOption *p1Color, ColorOption *p2Color,
                       ColorOption *cpuColor, ColorOption *ballColor);
void config_set_colors(ColorOption p1Color, ColorOption p2Color,
                       ColorOption cpuColor, ColorOption ballColor);

bool config_get_sound_enabled(void);
void config_set_sound_enabled(bool enabled);

float config_get_sound_volume(void);
void config_set_sound_volume(float volume);

#endif // CONFIG_H

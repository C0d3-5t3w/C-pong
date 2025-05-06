#ifndef CONFIG_H
#define CONFIG_H

#include "../main.h"  // Added include for Color definition
#include <stdbool.h>

// Color options (moved from settings.h)
typedef enum {
  COLOR_RED,
  COLOR_GREEN,
  COLOR_BLUE,
  COLOR_YELLOW,
  COLOR_CYAN,
  COLOR_MAGENTA,
  COLOR_WHITE,
  COLOR_COUNT
} ColorOption;

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

// Get actual color from color option
void config_get_real_color(ColorOption option, Color* outColor);

#endif // CONFIG_H

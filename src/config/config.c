#include "config.h"
#include "../main.h" // Include this for Color definition
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Default configuration
typedef struct {
  int difficulty;
  ColorOption p1Color;
  ColorOption p2Color;
  ColorOption cpuColor;
  ColorOption ballColor;
  bool soundEnabled;
  float soundVolume;
} GameConfig;

static GameConfig config = {
    .difficulty = 2,        // Medium
    .p1Color = COLOR_RED,
    .p2Color = COLOR_BLUE,
    .cpuColor = COLOR_GREEN,
    .ballColor = COLOR_WHITE,
    .soundEnabled = true,
    .soundVolume = 0.7F
};

// Define color values
static const Color colorValues[] = {
    {255, 0, 0, 255},    // Red
    {0, 255, 0, 255},    // Green
    {0, 0, 255, 255},    // Blue
    {255, 255, 0, 255},  // Yellow
    {0, 255, 255, 255},  // Cyan
    {255, 0, 255, 255},  // Magenta
    {255, 255, 255, 255} // White
};

bool config_init(void) {
  // Try to load config, if fails, use defaults and create config file
  if (!config_load()) {
    return config_save();
  }
  return true;
}

bool config_save(void) {
  FILE *file = fopen("pkg/config.txt", "w");
  if (!file) {
    return false;
  }

  // Write configuration in simple format
  fprintf(file, "difficulty %d\n", config.difficulty);
  fprintf(file, "player1_color %d\n", config.p1Color);
  fprintf(file, "player2_color %d\n", config.p2Color);
  fprintf(file, "cpu_color %d\n", config.cpuColor);
  fprintf(file, "ball_color %d\n", config.ballColor);
  fprintf(file, "sound_enabled %d\n", config.soundEnabled ? 1 : 0);
  fprintf(file, "sound_volume %.1f\n", config.soundVolume);

  fclose(file);
  return true;
}

bool config_load(void) {
  FILE *file = fopen("pkg/config.txt", "r");
  if (!file) {
    // Try to open YAML file as fallback (for compatibility)
    file = fopen("pkg/config.yaml", "r");
    if (!file) {
      return false;
    }
    // If it's a YAML file, just close it and use default config
    fclose(file);
    return false;
  }

  char line[100];
  char key[50];
  char value[50];

  while (fgets(line, sizeof(line), file)) {
    // Skip comments and empty lines
    if (line[0] == '#' || line[0] == '\n') {
      continue;
    }

    if (sscanf(line, "%49s %49s", key, value) == 2) {
      if (strcmp(key, "difficulty") == 0) {
        config.difficulty = atoi(value);
      } else if (strcmp(key, "player1_color") == 0) {
        config.p1Color = (ColorOption)atoi(value);
      } else if (strcmp(key, "player2_color") == 0) {
        config.p2Color = (ColorOption)atoi(value);
      } else if (strcmp(key, "cpu_color") == 0) {
        config.cpuColor = (ColorOption)atoi(value);
      } else if (strcmp(key, "ball_color") == 0) {
        config.ballColor = (ColorOption)atoi(value);
      } else if (strcmp(key, "sound_enabled") == 0) {
        config.soundEnabled = (atoi(value) != 0);
      } else if (strcmp(key, "sound_volume") == 0) {
        config.soundVolume = atof(value);
      }
    }
  }

  fclose(file);
  return true;
}

int config_get_difficulty(void) { return config.difficulty; }

void config_set_difficulty(int difficulty) {
  if (difficulty >= 1 && difficulty <= 3) {
    config.difficulty = difficulty;
  }
}

void config_get_colors(ColorOption *p1Color, ColorOption *p2Color,
                       ColorOption *cpuColor, ColorOption *ballColor) {
  if (p1Color)
    *p1Color = config.p1Color;
  if (p2Color)
    *p2Color = config.p2Color;
  if (cpuColor)
    *cpuColor = config.cpuColor;
  if (ballColor)
    *ballColor = config.ballColor;
}

void config_set_colors(ColorOption p1Color, ColorOption p2Color,
                       ColorOption cpuColor, ColorOption ballColor) {
  if (p1Color >= 0 && p1Color < COLOR_COUNT)
    config.p1Color = p1Color;
  if (p2Color >= 0 && p2Color < COLOR_COUNT)
    config.p2Color = p2Color;
  if (cpuColor >= 0 && cpuColor < COLOR_COUNT)
    config.cpuColor = cpuColor;
  if (ballColor >= 0 && ballColor < COLOR_COUNT)
    config.ballColor = ballColor;
}

bool config_get_sound_enabled(void) { return config.soundEnabled; }

void config_set_sound_enabled(bool enabled) { config.soundEnabled = enabled; }

float config_get_sound_volume(void) { return config.soundVolume; }

void config_set_sound_volume(float volume) {
  if (volume >= 0.0F && volume <= 1.0F) {
    config.soundVolume = volume;
  }
}

void config_get_real_color(ColorOption option, Color* outColor) {
  if (option >= 0 && option < COLOR_COUNT && outColor != NULL) {
    *outColor = colorValues[option];
  } else if (outColor != NULL) {
    *outColor = colorValues[COLOR_WHITE]; // Default to white
  }
}

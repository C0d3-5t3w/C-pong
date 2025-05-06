#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

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

static GameConfig config = {.difficulty = 2, // Medium
                            .p1Color = COLOR_RED,
                            .p2Color = COLOR_BLUE,
                            .cpuColor = COLOR_GREEN,
                            .ballColor = COLOR_WHITE,
                            .soundEnabled = true,
                            .soundVolume = 0.7f};

bool config_init(void) {
  // Try to load config, if fails, use defaults and create config file
  if (!config_load()) {
    return config_save();
  }
  return true;
}

bool config_save(void) {
  FILE *file = fopen("pkg/config.yaml", "w");
  if (!file) {
    return false;
  }

  // Write configuration in YAML format
  fprintf(file, "# C-Pong Configuration\n\n");
  fprintf(file, "difficulty: %d\n", config.difficulty);
  fprintf(file, "player1_color: %d\n", config.p1Color);
  fprintf(file, "player2_color: %d\n", config.p2Color);
  fprintf(file, "cpu_color: %d\n", config.cpuColor);
  fprintf(file, "ball_color: %d\n", config.ballColor);
  fprintf(file, "sound_enabled: %s\n", config.soundEnabled ? "true" : "false");
  fprintf(file, "sound_volume: %.1f\n", config.soundVolume);

  fclose(file);
  return true;
}

bool config_load(void) {
  FILE *file = fopen("pkg/config.yaml", "r");
  if (!file) {
    return false;
  }

  yaml_parser_t parser;
  yaml_token_t token;
  char key[64] = {0};
  bool inKey = false;

  // Initialize parser
  if (!yaml_parser_initialize(&parser)) {
    fclose(file);
    return false;
  }

  yaml_parser_set_input_file(&parser, file);

  do {
    yaml_parser_scan(&parser, &token);

    switch (token.type) {
    case YAML_KEY_TOKEN:
      inKey = true;
      memset(key, 0, sizeof(key));
      break;

    case YAML_VALUE_TOKEN:
      inKey = false;
      break;

    case YAML_SCALAR_TOKEN: {
      char *value = (char *)token.data.scalar.value;

      if (inKey) {
        strncpy(key, value, sizeof(key) - 1);
      } else {
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
          config.soundEnabled = (strcmp(value, "true") == 0);
        } else if (strcmp(key, "sound_volume") == 0) {
          config.soundVolume = atof(value);
        }
      }
      break;
    }

    default:
      break;
    }

    if (token.type != YAML_STREAM_END_TOKEN)
      yaml_token_delete(&token);

  } while (token.type != YAML_STREAM_END_TOKEN);

  yaml_token_delete(&token);
  yaml_parser_delete(&parser);
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
  if (volume >= 0.0f && volume <= 1.0f) {
    config.soundVolume = volume;
  }
}

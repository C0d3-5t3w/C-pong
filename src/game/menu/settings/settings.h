#ifndef SETTINGS_H
#define SETTINGS_H

#include "../../../main.h"
#include "../../../config/config.h"
#include <stdbool.h>

// Settings options
typedef enum {
  SETTING_DIFFICULTY,
  SETTING_PLAYER1_COLOR,
  SETTING_PLAYER2_COLOR,
  SETTING_CPU_COLOR,
  SETTING_BALL_COLOR,
  SETTING_BACK,
  SETTING_OPTION_COUNT
} SettingOption;

// Settings functions (only keep non-redundant declarations)
bool settings_save(void);
bool settings_load(void);

#endif // SETTINGS_H

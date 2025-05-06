#ifndef SETTINGS_H
#define SETTINGS_H

#include <SDL2/SDL.h>
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

// Color options
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

// Settings functions
void settings_init(void);
void settings_update(void);
void settings_render(void);
void settings_handle_event(SDL_Event *event);
bool settings_save(void);
bool settings_load(void);
SDL_Color settings_get_color(ColorOption color);

#endif // SETTINGS_H

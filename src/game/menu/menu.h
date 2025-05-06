#ifndef MENU_H
#define MENU_H

#include "../../main.h"
#include <stdbool.h>

// Menu options
typedef enum {
  MENU_PLAY_VS_CPU,
  MENU_PLAY_VS_PLAYER,
  MENU_SETTINGS,
  MENU_EXIT,
  MENU_OPTION_COUNT
} MenuOption;

// Menu functions (only keep non-redundant declarations)
MenuOption menu_get_selected(void);
void menu_set_selected(MenuOption option);

#endif // MENU_H

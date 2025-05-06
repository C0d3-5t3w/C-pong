#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <stdbool.h>

// Menu options
typedef enum {
  MENU_PLAY_VS_CPU,
  MENU_PLAY_VS_PLAYER,
  MENU_SETTINGS,
  MENU_EXIT,
  MENU_OPTION_COUNT
} MenuOption;

// Menu functions
void menu_init(void);
void menu_update(void);
void menu_render(void);
void menu_handle_event(SDL_Event *event);
MenuOption menu_get_selected(void);
void menu_set_selected(MenuOption option);

#endif // MENU_H

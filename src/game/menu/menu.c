#include "menu.h"
#include "../../gui/gui.h"
#include "../../main.h"
#include "../game.h"

static MenuOption selectedOption = MENU_PLAY_VS_CPU;
static const char *menuOptionTexts[MENU_OPTION_COUNT] = {
    "Play vs CPU", "Play vs Player", "Settings", "Exit"};

void menu_init(void) { selectedOption = MENU_PLAY_VS_CPU; }

void menu_update(void) {
  // Nothing to update in the menu
}

void menu_render(void) {
  // Draw title
  gui_draw_text("C PONG", WINDOW_WIDTH / 2, 5, true);

  // Draw menu options
  int yPos = 10;
  for (int i = 0; i < MENU_OPTION_COUNT; i++) {
    // Use > character to indicate selected item
    if (i == (int)selectedOption) {
      gui_draw_text(">", WINDOW_WIDTH / 2 - 10, yPos, false);
    }
    gui_draw_text(menuOptionTexts[i], WINDOW_WIDTH / 2, yPos, true);
    yPos += 3;
  }

  // Draw controls help
  gui_draw_text("Use UP/DOWN arrows to select, ENTER to confirm",
                WINDOW_WIDTH / 2, WINDOW_HEIGHT - 2, true);
}

void menu_handle_event(Event *event) {
  if (event->type == EVENT_KEYDOWN) {
    switch (event->key.sym) {
    case KEY_UP:
      if (selectedOption > 0) {
        selectedOption = (MenuOption)(selectedOption - 1);
      } else {
        selectedOption = MENU_EXIT;
      }
      break;

    case KEY_DOWN:
      if (selectedOption < MENU_EXIT) {
        selectedOption = (MenuOption)(selectedOption + 1);
      } else {
        selectedOption = MENU_PLAY_VS_CPU;
      }
      break;

    case KEY_RETURN:
      // Handle selection
      switch (selectedOption) {
      case MENU_PLAY_VS_CPU:
        game_set_mode(MODE_PLAYER_VS_CPU);
        game_reset();
        currentState = STATE_GAME;
        break;

      case MENU_PLAY_VS_PLAYER:
        game_set_mode(MODE_PLAYER_VS_PLAYER);
        game_reset();
        currentState = STATE_GAME;
        break;

      case MENU_SETTINGS:
        currentState = STATE_SETTINGS;
        break;

      case MENU_EXIT:
        currentState = STATE_EXIT;
        break;

      default:
        break;
      }
      break;

    default:
      break;
    }
  }
}

MenuOption menu_get_selected(void) { return selectedOption; }

void menu_set_selected(MenuOption option) {
  if (option >= 0 && option < MENU_OPTION_COUNT) {
    selectedOption = option;
  }
}

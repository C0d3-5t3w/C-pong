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
  SDL_Color white = {255, 255, 255, 255};
  SDL_Color highlighted = {255, 255, 0, 255};

  // Draw title
  canvas_draw_text("C PONG", WINDOW_WIDTH / 2, 100, white, true);

  // Draw menu options
  int yPos = 200;
  for (int i = 0; i < MENU_OPTION_COUNT; i++) {
    SDL_Color color = (i == selectedOption) ? highlighted : white;
    canvas_draw_text(menuOptionTexts[i], WINDOW_WIDTH / 2, yPos, color, true);
    yPos += 50;
  }

  // Draw controls help
  canvas_draw_text("Use UP/DOWN arrows to select, ENTER to confirm",
                   WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50, white, true);
}

void menu_handle_event(SDL_Event *event) {
  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
    case SDLK_UP:
      if (selectedOption > 0) {
        selectedOption = (MenuOption)(selectedOption - 1);
      } else {
        selectedOption = MENU_EXIT;
      }
      break;

    case SDLK_DOWN:
      if (selectedOption < MENU_EXIT) {
        selectedOption = (MenuOption)(selectedOption + 1);
      } else {
        selectedOption = MENU_PLAY_VS_CPU;
      }
      break;

    case SDLK_RETURN:
    case SDLK_KP_ENTER:
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

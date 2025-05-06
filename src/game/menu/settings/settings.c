#include "settings.h"
#include "../../../config/config.h"
#include "../../../gui/gui.h"
#include "../../../main.h"
#include "../../cpu/cpu.h"
#include "../../game.h"
#include "../../player1/player1.h"
#include "../../player2/player2.h"

static SettingOption selectedOption = SETTING_DIFFICULTY;
static int cpuDifficulty = 2; // Default: Medium
static ColorOption p1ColorOption = COLOR_RED;
static ColorOption p2ColorOption = COLOR_BLUE;
static ColorOption cpuColorOption = COLOR_GREEN;
static ColorOption ballColorOption = COLOR_WHITE;

static const char *settingOptionTexts[SETTING_OPTION_COUNT] = {
    "CPU Difficulty", "Player 1 Color", "Player 2 Color",
    "CPU Color",      "Ball Color",     "Back to Menu"};

static const char *difficultyTexts[] = {"Easy", "Medium", "Hard"};

static const char *colorTexts[] = {"Red",  "Green",   "Blue", "Yellow",
                                   "Cyan", "Magenta", "White"};

static const SDL_Color colorValues[] = {
    {255, 0, 0, 255},    // Red
    {0, 255, 0, 255},    // Green
    {0, 0, 255, 255},    // Blue
    {255, 255, 0, 255},  // Yellow
    {0, 255, 255, 255},  // Cyan
    {255, 0, 255, 255},  // Magenta
    {255, 255, 255, 255} // White
};

void settings_init(void) {
  cpuDifficulty = cpu_get_difficulty();

  // Load color settings
  config_get_colors(&p1ColorOption, &p2ColorOption, &cpuColorOption,
                    &ballColorOption);

  // Apply colors
  player1_set_color(settings_get_color(p1ColorOption));
  player2_set_color(settings_get_color(p2ColorOption));
  cpu_set_color(settings_get_color(cpuColorOption));

  Ball *ball = game_get_ball();
  if (ball) {
    ball->color = settings_get_color(ballColorOption);
  }

  selectedOption = SETTING_DIFFICULTY;
}

void settings_update(void) {
  // Nothing to update continuously
}

void settings_render(void) {
  SDL_Color white = {255, 255, 255, 255};
  SDL_Color highlighted = {255, 255, 0, 255};

  // Draw title
  canvas_draw_text("SETTINGS", WINDOW_WIDTH / 2, 60, white, true);

  int yPos = 150;
  int yStep = 60;

  // Draw setting options
  for (int i = 0; i < SETTING_OPTION_COUNT; i++) {
    SDL_Color color = (i == selectedOption) ? highlighted : white;
    canvas_draw_text(settingOptionTexts[i], WINDOW_WIDTH / 3, yPos, color,
                     false);

    // Draw current value
    switch (i) {
    case SETTING_DIFFICULTY:
      canvas_draw_text(difficultyTexts[cpuDifficulty - 1], 2 * WINDOW_WIDTH / 3,
                       yPos, color, false);
      break;

    case SETTING_PLAYER1_COLOR:
      canvas_draw_text(colorTexts[p1ColorOption], 2 * WINDOW_WIDTH / 3, yPos,
                       settings_get_color(p1ColorOption), false);
      break;

    case SETTING_PLAYER2_COLOR:
      canvas_draw_text(colorTexts[p2ColorOption], 2 * WINDOW_WIDTH / 3, yPos,
                       settings_get_color(p2ColorOption), false);
      break;

    case SETTING_CPU_COLOR:
      canvas_draw_text(colorTexts[cpuColorOption], 2 * WINDOW_WIDTH / 3, yPos,
                       settings_get_color(cpuColorOption), false);
      break;

    case SETTING_BALL_COLOR:
      canvas_draw_text(colorTexts[ballColorOption], 2 * WINDOW_WIDTH / 3, yPos,
                       settings_get_color(ballColorOption), false);
      break;

    case SETTING_BACK:
      // No value to display
      break;
    }

    yPos += yStep;
  }

  // Draw controls help
  canvas_draw_text("UP/DOWN to select, LEFT/RIGHT to change, ENTER to confirm",
                   WINDOW_WIDTH / 2, WINDOW_HEIGHT - 30, white, true);
}

void settings_handle_event(SDL_Event *event) {
  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
    case SDLK_UP:
      if (selectedOption > 0) {
        selectedOption = (SettingOption)(selectedOption - 1);
      } else {
        selectedOption = SETTING_BACK;
      }
      break;

    case SDLK_DOWN:
      if (selectedOption < SETTING_BACK) {
        selectedOption = (SettingOption)(selectedOption + 1);
      } else {
        selectedOption = SETTING_DIFFICULTY;
      }
      break;

    case SDLK_LEFT:
      // Change selected option value
      switch (selectedOption) {
      case SETTING_DIFFICULTY:
        if (cpuDifficulty > 1)
          cpuDifficulty--;
        else
          cpuDifficulty = 3;
        cpu_set_difficulty(cpuDifficulty);
        break;

      case SETTING_PLAYER1_COLOR:
        if (p1ColorOption > 0)
          p1ColorOption--;
        else
          p1ColorOption = COLOR_COUNT - 1;
        player1_set_color(settings_get_color(p1ColorOption));
        break;

      case SETTING_PLAYER2_COLOR:
        if (p2ColorOption > 0)
          p2ColorOption--;
        else
          p2ColorOption = COLOR_COUNT - 1;
        player2_set_color(settings_get_color(p2ColorOption));
        break;

      case SETTING_CPU_COLOR:
        if (cpuColorOption > 0)
          cpuColorOption--;
        else
          cpuColorOption = COLOR_COUNT - 1;
        cpu_set_color(settings_get_color(cpuColorOption));
        break;

      case SETTING_BALL_COLOR:
        if (ballColorOption > 0)
          ballColorOption--;
        else
          ballColorOption = COLOR_COUNT - 1;
        Ball *ball = game_get_ball();
        if (ball) {
          ball->color = settings_get_color(ballColorOption);
        }
        break;

      default:
        break;
      }
      break;

    case SDLK_RIGHT:
      // Change selected option value
      switch (selectedOption) {
      case SETTING_DIFFICULTY:
        if (cpuDifficulty < 3)
          cpuDifficulty++;
        else
          cpuDifficulty = 1;
        cpu_set_difficulty(cpuDifficulty);
        break;

      case SETTING_PLAYER1_COLOR:
        if (p1ColorOption < COLOR_COUNT - 1)
          p1ColorOption++;
        else
          p1ColorOption = 0;
        player1_set_color(settings_get_color(p1ColorOption));
        break;

      case SETTING_PLAYER2_COLOR:
        if (p2ColorOption < COLOR_COUNT - 1)
          p2ColorOption++;
        else
          p2ColorOption = 0;
        player2_set_color(settings_get_color(p2ColorOption));
        break;

      case SETTING_CPU_COLOR:
        if (cpuColorOption < COLOR_COUNT - 1)
          cpuColorOption++;
        else
          cpuColorOption = 0;
        cpu_set_color(settings_get_color(cpuColorOption));
        break;

      case SETTING_BALL_COLOR:
        if (ballColorOption < COLOR_COUNT - 1)
          ballColorOption++;
        else
          ballColorOption = 0;
        Ball *ball = game_get_ball();
        if (ball) {
          ball->color = settings_get_color(ballColorOption);
        }
        break;

      default:
        break;
      }
      break;

    case SDLK_RETURN:
    case SDLK_KP_ENTER:
      if (selectedOption == SETTING_BACK) {
        // Save settings
        settings_save();

        // Return to menu
        currentState = STATE_MENU;
      }
      break;

    case SDLK_ESCAPE:
      // Save settings
      settings_save();

      // Return to menu
      currentState = STATE_MENU;
      break;

    default:
      break;
    }
  }
}

bool settings_save(void) {
  // Save settings to config
  config_set_colors(p1ColorOption, p2ColorOption, cpuColorOption,
                    ballColorOption);
  config_set_difficulty(cpuDifficulty);
  return config_save();
}

bool settings_load(void) {
  if (!config_load()) {
    return false;
  }

  // Apply settings
  config_get_colors(&p1ColorOption, &p2ColorOption, &cpuColorOption,
                    &ballColorOption);
  cpuDifficulty = config_get_difficulty();

  return true;
}

SDL_Color settings_get_color(ColorOption color) {
  if (color >= 0 && color < COLOR_COUNT) {
    return colorValues[color];
  }
  return (SDL_Color){255, 255, 255, 255};
}

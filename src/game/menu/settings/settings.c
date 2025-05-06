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

void settings_init(void) {
  cpuDifficulty = config_get_difficulty();

  // Load color settings
  config_get_colors(&p1ColorOption, &p2ColorOption, &cpuColorOption,
                    &ballColorOption);

  // Apply colors
  Color color;
  
  config_get_real_color(p1ColorOption, &color);
  player1_set_color(color);
  
  config_get_real_color(p2ColorOption, &color);
  player2_set_color(color);
  
  config_get_real_color(cpuColorOption, &color);
  cpu_set_color(color);

  Ball *ball = game_get_ball();
  if (ball) {
    config_get_real_color(ballColorOption, &ball->color);
  }

  selectedOption = SETTING_DIFFICULTY;
}

void settings_update(void) {
  // Nothing to update continuously
}

void settings_render(void) {
  // Draw title
  gui_draw_text("SETTINGS", WINDOW_WIDTH / 2, 2, true);

  int yPos = 5;
  int yStep = 3;

  // Draw setting options
  for (int i = 0; i < SETTING_OPTION_COUNT; i++) {
    // Use > character to indicate selected item
    if (i == (int)selectedOption) {
      gui_draw_text(">", 5, yPos, false);
    }
    
    gui_draw_text(settingOptionTexts[i], 8, yPos, false);

    // Draw current value
    switch (i) {
    case SETTING_DIFFICULTY:
      gui_draw_text(difficultyTexts[cpuDifficulty - 1], 30, yPos, false);
      break;

    case SETTING_PLAYER1_COLOR:
      gui_draw_text(colorTexts[p1ColorOption], 30, yPos, false);
      break;

    case SETTING_PLAYER2_COLOR:
      gui_draw_text(colorTexts[p2ColorOption], 30, yPos, false);
      break;

    case SETTING_CPU_COLOR:
      gui_draw_text(colorTexts[cpuColorOption], 30, yPos, false);
      break;

    case SETTING_BALL_COLOR:
      gui_draw_text(colorTexts[ballColorOption], 30, yPos, false);
      break;

    case SETTING_BACK:
      // No value to display
      break;
    }

    yPos += yStep;
  }

  // Draw controls help
  gui_draw_text("UP/DOWN to select, LEFT/RIGHT to change, ENTER to confirm",
                WINDOW_WIDTH / 2, WINDOW_HEIGHT - 1, true);
}

void settings_handle_event(Event *event) {
  if (event->type == EVENT_KEYDOWN) {
    switch (event->key.sym) {
    case KEY_UP:
      if (selectedOption > 0) {
        selectedOption = (SettingOption)(selectedOption - 1);
      } else {
        selectedOption = SETTING_BACK;
      }
      break;

    case KEY_DOWN:
      if (selectedOption < SETTING_BACK) {
        selectedOption = (SettingOption)(selectedOption + 1);
      } else {
        selectedOption = SETTING_DIFFICULTY;
      }
      break;

    case KEY_LEFT:
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
        {
          Color color;
          config_get_real_color(p1ColorOption, &color);
          player1_set_color(color);
        }
        break;

      case SETTING_PLAYER2_COLOR:
        if (p2ColorOption > 0)
          p2ColorOption--;
        else
          p2ColorOption = COLOR_COUNT - 1;
        {
          Color color;
          config_get_real_color(p2ColorOption, &color);
          player2_set_color(color);
        }
        break;

      case SETTING_CPU_COLOR:
        if (cpuColorOption > 0)
          cpuColorOption--;
        else
          cpuColorOption = COLOR_COUNT - 1;
        {  
          Color color;
          config_get_real_color(cpuColorOption, &color);
          cpu_set_color(color);
        }
        break;

      case SETTING_BALL_COLOR:
        if (ballColorOption > 0)
          ballColorOption--;
        else
          ballColorOption = COLOR_COUNT - 1;
        {
          Ball *ball = game_get_ball();
          if (ball) {
            config_get_real_color(ballColorOption, &ball->color);
          }
        }
        break;

      default:
        break;
      }
      break;

    case KEY_RIGHT:
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
        {
          Color color;
          config_get_real_color(p1ColorOption, &color);
          player1_set_color(color);
        }
        break;

      case SETTING_PLAYER2_COLOR:
        if (p2ColorOption < COLOR_COUNT - 1)
          p2ColorOption++;
        else
          p2ColorOption = 0;
        {
          Color color;
          config_get_real_color(p2ColorOption, &color);
          player2_set_color(color);
        }
        break;

      case SETTING_CPU_COLOR:
        if (cpuColorOption < COLOR_COUNT - 1)
          cpuColorOption++;
        else
          cpuColorOption = 0;
        {
          Color color;
          config_get_real_color(cpuColorOption, &color);
          cpu_set_color(color);
        }
        break;

      case SETTING_BALL_COLOR:
        if (ballColorOption < COLOR_COUNT - 1)
          ballColorOption++;
        else
          ballColorOption = 0;
        {
          Ball *ball = game_get_ball();
          if (ball) {
            config_get_real_color(ballColorOption, &ball->color);
          }
        }
        break;

      default:
        break;
      }
      break;

    case KEY_RETURN:
      if (selectedOption == SETTING_BACK) {
        // Save settings
        settings_save();

        // Return to menu
        currentState = STATE_MENU;
      }
      break;

    case KEY_ESCAPE:
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

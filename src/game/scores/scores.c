#include "scores.h"
#include "../../gui/gui.h"
#include "../../main.h"
#include "../game.h"
#include <stdio.h>

static int p1Score = 0;
static int p2Score = 0;
static int cpuScore = 0;
static HighScoreEntry highScores[5];

void scores_init(void) {
  p1Score = 0;
  p2Score = 0;
  cpuScore = 0;

  // Initialize high scores
  for (int i = 0; i < 5; i++) {
    highScores[i].highScore = 0;
    sprintf(highScores[i].playerName, "Player%d", i + 1);
  }

  // Try to load scores from file
  scores_load();
}

void scores_cleanup(void) { scores_save(); }

void scores_reset(void) {
  p1Score = 0;
  p2Score = 0;
  cpuScore = 0;
}

int scores_get_p1(void) { return p1Score; }

int scores_get_p2(void) { return p2Score; }

int scores_get_cpu(void) { return cpuScore; }

void scores_add_p1_score(void) { p1Score++; }

void scores_add_p2_score(void) { p2Score++; }

void scores_add_cpu_score(void) { cpuScore++; }

void scores_render(void) {
  char scoreText[32];

  if (game_get_mode() == MODE_PLAYER_VS_CPU) {
    sprintf(scoreText, "%d - %d", p1Score, cpuScore);
  } else {
    sprintf(scoreText, "%d - %d", p1Score, p2Score);
  }

  gui_draw_text(scoreText, WINDOW_WIDTH / 2, 2, true);
}

bool scores_save(void) {
  // Create a simple text file to store scores
  FILE *file = fopen("pkg/scores.txt", "w");
  if (!file) {
    return false;
  }

  // Write current high scores
  for (int i = 0; i < 5; i++) {
    fprintf(file, "%d %s\n", highScores[i].highScore, highScores[i].playerName);
  }

  fclose(file);
  return true;
}

bool scores_load(void) {
  // Open scores file
  FILE *file = fopen("pkg/scores.txt", "r");
  if (!file) {
    // Try to open the JSON file as fallback (for compatibility)
    file = fopen("pkg/scores.json", "r");
    if (!file) {
      return false;
    }
    
    // If it's a JSON file, just close it and use default scores
    fclose(file);
    return false;
  }

  // Read high scores
  for (int i = 0; i < 5; i++) {
    if (fscanf(file, "%d %63s", &highScores[i].highScore, highScores[i].playerName) != 2) {
      break;
    }
  }

  fclose(file);
  return true;
}

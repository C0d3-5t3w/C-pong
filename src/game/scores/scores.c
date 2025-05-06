#include "scores.h"
#include "../../gui/gui.h"
#include "../../main.h"
#include <json-c/json.h>
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
  SDL_Color white = {255, 255, 255, 255};
  char scoreText[32];

  if (game_get_mode() == MODE_PLAYER_VS_CPU) {
    sprintf(scoreText, "%d - %d", p1Score, cpuScore);
  } else {
    sprintf(scoreText, "%d - %d", p1Score, p2Score);
  }

  canvas_draw_text(scoreText, WINDOW_WIDTH / 2, 30, white, true);
}

bool scores_save(void) {
  // Create a JSON object to store scores
  json_object *root = json_object_new_object();
  json_object *highScoresArray = json_object_new_array();

  // Add current high scores to array
  for (int i = 0; i < 5; i++) {
    json_object *entry = json_object_new_object();
    json_object_object_add(entry, "score",
                           json_object_new_int(highScores[i].highScore));
    json_object_object_add(entry, "name",
                           json_object_new_string(highScores[i].playerName));
    json_object_array_add(highScoresArray, entry);
  }

  // Add array to root object
  json_object_object_add(root, "highScores", highScoresArray);

  // Write JSON to file
  FILE *file = fopen("pkg/scores.json", "w");
  if (!file) {
    return false;
  }

  fprintf(file, "%s",
          json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));
  fclose(file);

  // Free JSON object
  json_object_put(root);

  return true;
}

bool scores_load(void) {
  // Open scores file
  FILE *file = fopen("pkg/scores.json", "r");
  if (!file) {
    return false;
  }

  // Get file size
  fseek(file, 0, SEEK_END);
  long fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  // Read file content
  char *buffer = (char *)malloc(fileSize + 1);
  if (!buffer) {
    fclose(file);
    return false;
  }

  size_t read = fread(buffer, 1, fileSize, file);
  buffer[read] = '\0';
  fclose(file);

  // Parse JSON
  json_object *root = json_tokener_parse(buffer);
  free(buffer);

  if (!root) {
    return false;
  }

  // Extract high scores
  json_object *highScoresArray;
  if (json_object_object_get_ex(root, "highScores", &highScoresArray)) {
    int numScores = json_object_array_length(highScoresArray);
    for (int i = 0; i < numScores && i < 5; i++) {
      json_object *entry = json_object_array_get_idx(highScoresArray, i);
      json_object *scoreObj, *nameObj;

      if (json_object_object_get_ex(entry, "score", &scoreObj)) {
        highScores[i].highScore = json_object_get_int(scoreObj);
      }

      if (json_object_object_get_ex(entry, "name", &nameObj)) {
        strncpy(highScores[i].playerName, json_object_get_string(nameObj), 63);
        highScores[i].playerName[63] = '\0';
      }
    }
  }

  // Free JSON object
  json_object_put(root);

  return true;
}

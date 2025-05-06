#ifndef SCORES_H
#define SCORES_H

#include <stdbool.h>

// Function prototypes
void scores_init(void);
void scores_cleanup(void);
void scores_reset(void);
int scores_get_p1(void);
int scores_get_p2(void);
int scores_get_cpu(void);
void scores_add_p1_score(void);
void scores_add_p2_score(void);
void scores_add_cpu_score(void);
void scores_render(void);
bool scores_save(void);
bool scores_load(void);

typedef struct {
  int highScore;
  char playerName[64];
} HighScoreEntry;

#endif // SCORES_H

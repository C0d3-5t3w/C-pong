#ifndef AI_H
#define AI_H

#include "../../game.h" // For Ball structure

float ai_calculate_target_y(Ball *ball, int difficulty);
float ai_predict_ball_y_position(Ball *ball);

#endif // AI_H

#include "ai.h"
#include "../../../main.h"
#include <stdlib.h>

float ai_calculate_target_y(Ball *ball, int difficulty) {
  // If ball is moving away from CPU, just return middle position
  if (ball->velocityX < 0) {
    return WINDOW_HEIGHT / 2.0f;
  }

  // Calculate where the ball will intersect with the CPU's x position
  float cpuX = WINDOW_WIDTH - 40.0f;
  float timeToIntercept = (cpuX - ball->x) / ball->velocityX;

  // Calculate predicted y position
  float predictedY = ball->y + (ball->velocityY * timeToIntercept);

  // Account for bounces off top/bottom walls
  while (predictedY < 0 || predictedY > WINDOW_HEIGHT) {
    if (predictedY < 0) {
      predictedY = -predictedY;
    } else if (predictedY > WINDOW_HEIGHT) {
      predictedY = 2.0f * WINDOW_HEIGHT - predictedY;
    }
  }

  // Based on difficulty, add some randomness to the prediction
  switch (difficulty) {
  case 1: // Easy
    predictedY += ((float)rand() / RAND_MAX - 0.5f) * 100.0f;
    break;
  case 2: // Medium
    predictedY += ((float)rand() / RAND_MAX - 0.5f) * 50.0f;
    break;
  case 3: // Hard
    // Perfect prediction with minimal error
    predictedY += ((float)rand() / RAND_MAX - 0.5f) * 10.0f;
    break;
  }

  return predictedY;
}

float ai_predict_ball_y_position(Ball *ball) {
  // This is a simpler prediction function that doesn't account for bounces
  float cpuX = WINDOW_WIDTH - 40.0f;
  float timeToIntercept = (cpuX - ball->x) / ball->velocityX;
  return ball->y + (ball->velocityY * timeToIntercept);
}

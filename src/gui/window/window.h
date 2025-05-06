#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

// Console window functions
bool window_init(const char* title, int width, int height);
void window_cleanup(void);
int window_get_width(void);
int window_get_height(void);

#endif // WINDOW_H

#ifndef GUI_H
#define GUI_H

#include "../sdl_includes.h"
#include <stdbool.h>

// Function prototypes
bool gui_init(void);
void gui_cleanup(void);
void gui_clear(void);
void gui_present(void);
void gui_draw_rectangle(int posX, int posY, int width, int height, bool filled);
void gui_draw_text(const char* text, int posX, int posY, bool centered);
TTF_Font* gui_get_font(void);  // Add font accessor

#endif // GUI_H

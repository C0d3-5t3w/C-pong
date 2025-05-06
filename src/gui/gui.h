#ifndef GUI_H
#define GUI_H

#include <stdbool.h>

// Function prototypes
bool gui_init(void);
void gui_cleanup(void);
void gui_clear(void);
void gui_present(void);
void gui_draw_rectangle(int x, int y, int w, int h, bool filled);
void gui_draw_text(const char* text, int x, int y, bool centered);

#endif // GUI_H

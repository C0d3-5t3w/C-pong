#include "gui.h"
#include "../main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Console buffer to store the current frame
static char buffer[WINDOW_HEIGHT][WINDOW_WIDTH + 1];

bool gui_init(void) {
    // Initialize terminal for non-blocking input
    system("stty raw -echo");
    
    // Set up terminal for clearing and positioning
    printf("\033[2J"); // Clear screen
    
    // Initialize buffer
    memset(buffer, ' ', WINDOW_HEIGHT * (WINDOW_WIDTH + 1));
    for (int i = 0; i < WINDOW_HEIGHT; i++) {
        buffer[i][WINDOW_WIDTH] = '\0';
    }
    
    return true;
}

void gui_cleanup(void) {
    // Restore terminal settings
    system("stty cooked echo");
    printf("\033[2J\033[H"); // Clear screen and move cursor to home
}

void gui_clear(void) {
    // Clear the buffer
    for (int i = 0; i < WINDOW_HEIGHT; i++) {
        memset(buffer[i], ' ', WINDOW_WIDTH);
        buffer[i][WINDOW_WIDTH] = '\0';
    }
}

void gui_present(void) {
    // Move cursor to home position
    printf("\033[H");
    
    // Print the buffer
    for (int i = 0; i < WINDOW_HEIGHT; i++) {
        printf("%s\n", buffer[i]);
    }
    
    // Flush output
    fflush(stdout);
}

void gui_draw_rectangle(int x, int y, int w, int h, bool filled) {
    // Ensure coordinates are within bounds
    if (x < 0 || y < 0 || x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT) {
        return;
    }
    
    char fillChar = filled ? '#' : '+';
    
    // Draw the rectangle
    for (int i = y; i < y + h && i < WINDOW_HEIGHT; i++) {
        for (int j = x; j < x + w && j < WINDOW_WIDTH; j++) {
            if (filled || i == y || i == y + h - 1 || j == x || j == x + w - 1) {
                buffer[i][j] = fillChar;
            }
        }
    }
}

void gui_draw_text(const char* text, int x, int y, bool centered) {
    if (y < 0 || y >= WINDOW_HEIGHT) {
        return;
    }
    
    int len = strlen(text);
    if (centered) {
        x = x - len / 2;
    }
    
    for (int i = 0; i < len; i++) {
        if (x + i >= 0 && x + i < WINDOW_WIDTH) {
            buffer[y][x + i] = text[i];
        }
    }
}

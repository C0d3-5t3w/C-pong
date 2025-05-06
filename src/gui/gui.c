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

void gui_draw_rectangle(int posX, int posY, int width, int height, bool filled) {
    // Ensure coordinates are within bounds
    if (posX < 0 || posY < 0 || posX >= WINDOW_WIDTH || posY >= WINDOW_HEIGHT) {
        return;
    }
    
    char fillChar = filled ? '#' : '+';
    
    // Draw the rectangle
    for (int i = posY; i < posY + height && i < WINDOW_HEIGHT; i++) {
        for (int j = posX; j < posX + width && j < WINDOW_WIDTH; j++) {
            if (filled || i == posY || i == posY + height - 1 || j == posX || j == posX + width - 1) {
                buffer[i][j] = fillChar;
            }
        }
    }
}

void gui_draw_text(const char* text, int posX, int posY, bool centered) {
    if (posY < 0 || posY >= WINDOW_HEIGHT) {
        return;
    }
    
    int len = strlen(text);
    if (centered) {
        posX = posX - len / 2;
    }
    
    for (int i = 0; i < len; i++) {
        if (posX + i >= 0 && posX + i < WINDOW_WIDTH) {
            buffer[posY][posX + i] = text[i];
        }
    }
}

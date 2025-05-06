#include "gui.h"
#include "../main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Console buffer to store the current frame
static char buffer[WINDOW_HEIGHT][WINDOW_WIDTH + 1];
static char prev_buffer[WINDOW_HEIGHT][WINDOW_WIDTH + 1];
static int initialized = 0;

bool gui_init(void) {
    // Initialize terminal for non-blocking input
    system("stty raw -echo");
    
    // Set terminal size if supported
    printf("\033[8;%d;%dt", WINDOW_HEIGHT + 2, WINDOW_WIDTH + 2);
    
    // Clear screen and hide cursor
    printf("\033[2J\033[?25l");
    
    // Initialize buffer
    memset(buffer, ' ', WINDOW_HEIGHT * (WINDOW_WIDTH + 1));
    memset(prev_buffer, ' ', WINDOW_HEIGHT * (WINDOW_WIDTH + 1));
    for (int i = 0; i < WINDOW_HEIGHT; i++) {
        buffer[i][WINDOW_WIDTH] = '\0';
        prev_buffer[i][WINDOW_WIDTH] = '\0';
    }
    
    // Draw a border around the game area
    for (int i = 0; i < WINDOW_WIDTH; i++) {
        buffer[0][i] = '-';
        buffer[WINDOW_HEIGHT-1][i] = '-';
    }
    for (int i = 0; i < WINDOW_HEIGHT; i++) {
        buffer[i][0] = '|';
        buffer[i][WINDOW_WIDTH-1] = '|';
    }
    buffer[0][0] = '+';
    buffer[0][WINDOW_WIDTH-1] = '+';
    buffer[WINDOW_HEIGHT-1][0] = '+';
    buffer[WINDOW_HEIGHT-1][WINDOW_WIDTH-1] = '+';
    
    initialized = 1;
    
    return true;
}

void gui_cleanup(void) {
    // Show cursor again
    printf("\033[?25h");
    
    // Restore terminal settings
    system("stty cooked echo");
    
    // Clear screen and position cursor at home
    printf("\033[2J\033[H");
}

void gui_clear(void) {
    // Keep a copy of the previous buffer for optimized rendering
    memcpy(prev_buffer, buffer, WINDOW_HEIGHT * (WINDOW_WIDTH + 1));
    
    // Clear the buffer but maintain the border
    for (int i = 1; i < WINDOW_HEIGHT-1; i++) {
        for (int j = 1; j < WINDOW_WIDTH-1; j++) {
            buffer[i][j] = ' ';
        }
    }
}

void gui_present(void) {
    if (!initialized) return;
    
    // Reset cursor to home position
    printf("\033[H");
    
    // Render only changed parts for efficiency
    for (int i = 0; i < WINDOW_HEIGHT; i++) {
        for (int j = 0; j < WINDOW_WIDTH; j++) {
            if (buffer[i][j] != prev_buffer[i][j]) {
                printf("\033[%d;%dH%c", i+1, j+1, buffer[i][j]);
            }
        }
    }
    
    // Flush output
    fflush(stdout);
}

void gui_draw_rectangle(int posX, int posY, int width, int height, bool filled) {
    // Adjust coordinates to stay within drawable area
    posX = posX + 1;  // Add offset for the border
    posY = posY + 1;  // Add offset for the border
    
    // Ensure we're not drawing outside the valid area
    if (posX <= 0 || posY <= 0 || posX >= WINDOW_WIDTH-1 || posY >= WINDOW_HEIGHT-1) {
        return;
    }
    
    // Constrain dimensions
    if (posX + width > WINDOW_WIDTH-1) {
        width = WINDOW_WIDTH-1 - posX;
    }
    if (posY + height > WINDOW_HEIGHT-1) {
        height = WINDOW_HEIGHT-1 - posY;
    }
    
    char fillChar = filled ? '#' : '+';
    char horizontalChar = '-';
    char verticalChar = '|';
    
    // Draw the rectangle
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (filled || i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                char charToDraw = fillChar;
                if (!filled) {
                    if (i == 0 || i == height - 1) charToDraw = horizontalChar;
                    if (j == 0 || j == width - 1) charToDraw = verticalChar;
                    if ((i == 0 || i == height - 1) && (j == 0 || j == width - 1)) charToDraw = '+';
                }
                buffer[posY+i][posX+j] = charToDraw;
            }
        }
    }
}

void gui_draw_text(const char* text, int posX, int posY, bool centered) {
    // Adjust coordinates to stay within drawable area
    posX = posX + 1;  // Add offset for the border
    posY = posY + 1;  // Add offset for the border
    
    if (posY < 1 || posY >= WINDOW_HEIGHT-1) {
        return;
    }
    
    int len = strlen(text);
    if (centered) {
        posX = posX - len / 2;
    }
    
    for (int i = 0; i < len; i++) {
        if (posX + i >= 1 && posX + i < WINDOW_WIDTH-1) {
            buffer[posY][posX + i] = text[i];
        }
    }
}

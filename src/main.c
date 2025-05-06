#include "main.h"
#include <termios.h>
#include <fcntl.h>
#include <sys/time.h>

GameState currentState = STATE_MENU;
static struct termios old_term, new_term;
static struct timeval start_time;

// Initialize non-blocking input
static void init_input(void) {
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
    
    // Initialize time reference
    gettimeofday(&start_time, NULL);
}

// Restore terminal settings
static void cleanup_input(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
}

// Get key input
static int get_key(void) {
    int ch = getchar();
    if (ch == EOF) return -1;
    
    switch (ch) {
        case 27: // Escape sequence
            if (getchar() == '[') {
                ch = getchar();
                switch (ch) {
                    case 'A': return KEY_UP;
                    case 'B': return KEY_DOWN;
                    case 'C': return KEY_RIGHT;
                    case 'D': return KEY_LEFT;
                }
            }
            return KEY_ESCAPE;
        case 'w': case 'W': return KEY_W;
        case 's': case 'S': return KEY_S;
        case 'p': case 'P': return KEY_P;
        case 13:  return KEY_RETURN; // Enter key
        case 'q': case 'Q': return EVENT_QUIT;
    }
    
    return ch;
}

bool poll_event(Event* event) {
    int key = get_key();
    if (key == -1) return false;
    
    if (key == EVENT_QUIT) {
        event->type = EVENT_QUIT;
        return true;
    }
    
    event->type = EVENT_KEYDOWN;
    event->key.sym = key;
    return true;
}

unsigned int get_ticks(void) {
    struct timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_sec - start_time.tv_sec) * 1000 + 
           (now.tv_usec - start_time.tv_usec) / 1000;
}

void delay_ms(int ms) {
    usleep(ms * 1000);
}

int main(int argc, char *argv[]) {
    (void)argc; // Unused parameter
    (void)argv; // Unused parameter

    // Seed random number generator
    srand((unsigned int)time(NULL));

    // Initialize input
    init_input();

    // Initialize GUI
    if (!gui_init()) {
        fprintf(stderr, "Failed to initialize GUI!\n");
        cleanup_input();
        return 1;
    }

    // Initialize configuration
    if (!config_init()) {
        fprintf(stderr, "Warning: Could not load configuration, using defaults\n");
    }

    // Initialize game components
    game_init();
    menu_init();
    settings_init();

    // Game loop variables
    Event event;
    bool running = true;
    unsigned int frameStart, frameTime;

    // Main game loop
    while (running) {
        frameStart = get_ticks();

        // Process input
        while (poll_event(&event)) {
            if (event.type == EVENT_QUIT) {
                running = false;
            }

            switch (currentState) {
            case STATE_MENU:
                menu_handle_event(&event);
                break;
            case STATE_GAME:
                game_handle_event(&event);
                break;
            case STATE_SETTINGS:
                settings_handle_event(&event);
                break;
            case STATE_EXIT:
                running = false;
                break;
            }
        }

        // Update game state
        switch (currentState) {
        case STATE_MENU:
            menu_update();
            break;
        case STATE_GAME:
            game_update();
            break;
        case STATE_SETTINGS:
            settings_update();
            break;
        case STATE_EXIT:
            break;
        }

        // Render
        gui_clear();

        switch (currentState) {
        case STATE_MENU:
            menu_render();
            break;
        case STATE_GAME:
            game_render();
            break;
        case STATE_SETTINGS:
            settings_render();
            break;
        case STATE_EXIT:
            break;
        }

        gui_present();

        // Cap the frame rate
        frameTime = get_ticks() - frameStart;
        if (FRAME_DELAY > frameTime) {
            delay_ms(FRAME_DELAY - frameTime);
        }
    }

    // Save scores and settings before exit
    scores_save();
    config_save();

    // Cleanup
    game_cleanup();
    gui_cleanup();
    cleanup_input();

    return 0;
}

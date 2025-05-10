#include "main.h"
#include "gui/gui.h"
#include "game/game.h"
#include "game/menu/menu.h"
#include "game/menu/settings/settings.h"
#include "game/scores/scores.h"
#include "config/config.h"
#include <SDL2/SDL.h>
#include "sdl_includes.h"
#include <sys/time.h>

GameState currentState = STATE_MENU;
static struct timeval start_time;

// Initialize time reference
static void init_time(void) {
  gettimeofday(&start_time, NULL);
}

bool poll_event(Event* event) {
  SDL_Event sdlEvent;
  
  // Check for SDL events
  if (SDL_PollEvent(&sdlEvent)) {
    switch (sdlEvent.type) {
      case SDL_QUIT:
        event->type = EVENT_QUIT;
        return true;
        
      case SDL_KEYDOWN:
        event->type = EVENT_KEYDOWN;
        
        // Map SDL keys to our key codes
        switch (sdlEvent.key.keysym.sym) {
          case SDLK_UP:    event->key.sym = KEY_UP; break;
          case SDLK_DOWN:  event->key.sym = KEY_DOWN; break;
          case SDLK_LEFT:  event->key.sym = KEY_LEFT; break;
          case SDLK_RIGHT: event->key.sym = KEY_RIGHT; break;
          case SDLK_w:     event->key.sym = KEY_W; break;
          case SDLK_s:     event->key.sym = KEY_S; break;
          case SDLK_p:     event->key.sym = KEY_P; break;
          case SDLK_ESCAPE: event->key.sym = KEY_ESCAPE; break;
          case SDLK_RETURN: event->key.sym = KEY_RETURN; break;
          default: return false; // Ignore other keys
        }
        return true;
        
      case SDL_KEYUP:
        event->type = EVENT_KEYUP;
        
        // Map SDL keys to our key codes
        switch (sdlEvent.key.keysym.sym) {
          case SDLK_UP:    event->key.sym = KEY_UP; break;
          case SDLK_DOWN:  event->key.sym = KEY_DOWN; break;
          case SDLK_LEFT:  event->key.sym = KEY_LEFT; break;
          case SDLK_RIGHT: event->key.sym = KEY_RIGHT; break;
          case SDLK_w:     event->key.sym = KEY_W; break;
          case SDLK_s:     event->key.sym = KEY_S; break;
          case SDLK_p:     event->key.sym = KEY_P; break;
          case SDLK_ESCAPE: event->key.sym = KEY_ESCAPE; break;
          case SDLK_RETURN: event->key.sym = KEY_RETURN; break;
          default: return false; // Ignore other keys
        }
        return true;
    }
  }
  
  return false;
}

unsigned int get_ticks(void) {
  struct timeval now;
  gettimeofday(&now, NULL);
  return (now.tv_sec - start_time.tv_sec) * 1000 + 
         (now.tv_usec - start_time.tv_usec) / 1000;
}

void delay_milliseconds(int milliseconds) {
  SDL_Delay(milliseconds);
}

int main(int argc, char *argv[]) {
  (void)argc; // Unused parameter
  (void)argv; // Unused parameter

  // Seed random number generator
  srand((unsigned int)time(NULL));

  // Initialize time
  init_time();

  // Initialize GUI (which initializes SDL)
  if (!gui_init()) {
    fprintf(stderr, "Failed to initialize GUI!\n");
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
      delay_milliseconds(FRAME_DELAY - frameTime);
    }
  }

  // Save scores and settings before exit
  scores_save();
  config_save();

  // Cleanup
  game_cleanup();
  gui_cleanup();

  return 0;
}

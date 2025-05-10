#ifndef SDL_INCLUDES_H
#define SDL_INCLUDES_H

/* This file provides a compatibility layer for SDL2 includes */

/* First include the standard SDL header */
#include <SDL2/SDL.h>

/* Define dummy TTF types and functions if SDL_TTF is not available */
#ifndef SDL_TTF_INCLUDED
typedef struct _TTF_Font TTF_Font;

/* Minimal SDL_ttf function declarations to allow compilation */
int TTF_Init(void);
const char* TTF_GetError(void);
void TTF_Quit(void);
TTF_Font* TTF_OpenFont(const char *file, int ptsize);
void TTF_CloseFont(TTF_Font *font);
#endif

#endif // SDL_INCLUDES_H

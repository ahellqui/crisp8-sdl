#ifndef CRISP8_SDL_SCREEN_H
#define CRISP8_SDL_SCREEN_H

#include <defs.h>

#include <stdint.h>
#include <SDL2/SDL.h>

struct screen
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Rect displayPixels [CRISP8_DISPLAY_WIDTH * CRISP8_DISPLAY_HEIGHT];
};

// Initializes the screen struct. This has to be called before calling any drawing functions
void initScreen (struct screen* screen);

// Frees all memory accociated with a screen struct. This should be the last called function on a screen
void destroyScreen (struct screen* screen);

// Draws the framebuffer returned from crisp8GetFramebuffer
void drawFramebuffer (struct screen* screen, const uint8_t* const framebuffer);
#endif

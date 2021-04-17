#ifndef CRISP8_SDL_SCREEN_H
#define CRISP8_SDL_SCREEN_H

#include <defs.h>

#include <stdint.h>
#include <SDL2/SDL.h>

// Struct containing both handles to the program window as well as the chip-8 emulators screen
struct screen
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Rect displayPixels [CRISP8_DISPLAY_WIDTH * CRISP8_DISPLAY_HEIGHT];
};

// Initializes the screen struct. This has to be called before calling any drawing functions
//
// Parameters:
//  screen: The screen struct to initialize
void initScreen (struct screen* screen);

// Frees all memory accociated with a screen struct. This should be the last called function on a screen
//
// Parameters:
//  screen: The screen struct to destroy
void destroyScreen (struct screen* screen);

// Draws the framebuffer returned from crisp8GetFramebuffer to the screen
//
// Parameters:
//  screen: the screen to draw on
//  framebuffer: The framebuffer returned from crisp8GetFramebuffer
void drawFramebuffer (struct screen* screen, const uint8_t* const framebuffer);
#endif

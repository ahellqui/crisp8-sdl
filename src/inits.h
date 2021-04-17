// Wrappers around library init functions to make sure everything starts as intended

#ifndef CRISP8_SDL_INITS_H
#define CRISP8_SDL_INITS_H

#include "crisp8.h"

// Initializes all SDL systems needed whith proper configuration
void initSDL ();

// Closes all SDL systems initially allocated; should be called at the end of the program
void cleanupSDL ();

// Initializes a chip8 emulator with callbacks and loads a rom into its memory
//
// Parameters:
//  emulator: The chip-8 emulator to initialize
//  progFile: Path to the rom to load
void initChip8 (chip8* emulator, const char* progFile);
#endif

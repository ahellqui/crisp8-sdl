#ifndef CRISP8_SDL_LOOP_H
#define CRISP8_SDL_LOOP_H

#include "screen.h"

#include <crisp8.h>

// The main loop of the program.
// It runs until the window receives a close signal, however it doesn't deallocate anything so you can call it multiple
// times if you want
//
// Parameters:
//  emulator: The used chip-8 emulator
//  screen: The screen struct to draw on
//  fps: The fps (cycles per second) to run the loop at. Capped at 9999 fps.
//       because games from the chip-8's era depended on the framerate for their timing, this has a direct correlation
//       to game speed.
void loop (chip8 emulator, struct screen* screen, uint16_t fps);
#endif

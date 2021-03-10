#ifndef CRISP8_SDL_LOOP_H
#define CRISP8_SDL_LOOP_H

#include "screen.h"

#include <crisp8.h>

void loop (chip8 emulator, struct screen* screen, uint16_t fps);
#endif

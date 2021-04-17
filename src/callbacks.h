#ifndef CRISP8_SDL_CALLBACKS_H
#define CRISP8_SDL_CALLBACKS_H

#include <stdint.h>

// Callback functions for the crisp8 emulator. These shouldn't be called by anyone anywhere except the emulator
uint32_t inputCb ();
void audioCb ();

#endif

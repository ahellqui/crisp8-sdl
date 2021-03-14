#include "callbacks.h"
#include "sound.h"

#include <SDL2/SDL.h>

#include <defs.h>

uint32_t inputCb ()
{
    const uint8_t* keyState = SDL_GetKeyboardState (NULL);
    uint32_t keyMap = 0;

    SDL_PumpEvents ();

    // First row
    if (keyState [SDL_SCANCODE_1])
    {
        keyMap |= CRISP8_KEYPAD_1;
    }

    if (keyState [SDL_SCANCODE_2])
    {
        keyMap |= CRISP8_KEYPAD_2;
    }

    if (keyState [SDL_SCANCODE_3])
    {
        keyMap |= CRISP8_KEYPAD_3;
    }

    if (keyState [SDL_SCANCODE_4])
    {
        keyMap |= CRISP8_KEYPAD_C;
    }

    // Second row
    if (keyState [SDL_SCANCODE_Q])
    {
        keyMap |= CRISP8_KEYPAD_4;
    }

    if (keyState [SDL_SCANCODE_W])
    {
        keyMap |= CRISP8_KEYPAD_5;
    }

    if (keyState [SDL_SCANCODE_E])
    {
        keyMap |= CRISP8_KEYPAD_6;
    }

    if (keyState [SDL_SCANCODE_R])
    {
        keyMap |= CRISP8_KEYPAD_D;
    }

    // Third row
    if (keyState [SDL_SCANCODE_A])
    {
        keyMap |= CRISP8_KEYPAD_7;
    }

    if (keyState [SDL_SCANCODE_S])
    {
        keyMap |= CRISP8_KEYPAD_8;
    }

    if (keyState [SDL_SCANCODE_D])
    {
        keyMap |= CRISP8_KEYPAD_9;
    }

    if (keyState [SDL_SCANCODE_F])
    {
        keyMap |= CRISP8_KEYPAD_E;
    }

    // Fourth row
    if (keyState [SDL_SCANCODE_Z])
    {
        keyMap |= CRISP8_KEYPAD_A;
    }

    if (keyState [SDL_SCANCODE_X])
    {
        keyMap |= CRISP8_KEYPAD_0;
    }

    if (keyState [SDL_SCANCODE_C])
    {
        keyMap |= CRISP8_KEYPAD_B;
    }

    if (keyState [SDL_SCANCODE_V])
    {
        keyMap |= CRISP8_KEYPAD_F;
    }

    return keyMap;
}

void audioCb ()
{
    toggleBeep ();
}

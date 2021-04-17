#include "loop.h"

#include <SDL2/SDL.h>
#include <stdbool.h>

// Returns true if the window receives a close signal (e.g the user clicks on the red cross or equivalent)
static bool shouldQuit ()
{
    SDL_Event event;
    while (SDL_PollEvent (&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                return true;
                break;
        }
    }

    return false;
}

// Call at the end of a loop to cap the framerate
//
// Parameters:
//  lastTime: The time in milliseconds since the last frame
//  remainder: A variable keeping track of subseconds for a more exact framerate. Pass in a zeroed variable the first
//  time and reuse it later.
//  fps: The fps to cap the framerate to
static void capFramerate (uint32_t* lastTime, float* remainder, uint16_t fps)
{
    const float expectedFrametime = 1000.0f / fps;
    int wait = expectedFrametime + (int)*remainder;

    remainder -= (int)*remainder;

    uint32_t frametime = SDL_GetTicks () - *lastTime;

    if (frametime < 1)
    {
        frametime = 1;
    }
    wait -= frametime;
    *remainder += expectedFrametime - (int)expectedFrametime;

    // Only delay if we're actually faster than our framerate
    if (wait > 0)
    {
        SDL_Delay (wait);
    }

    *lastTime = SDL_GetTicks ();
}

void loop (chip8 emulator, struct screen* screen, uint16_t fps)
{
    crisp8SetFramerate (emulator, fps);
    
    uint32_t lastTime = SDL_GetTicks ();
    float remainderTime = 0;
    while (1)
    {
        if (shouldQuit ())
        {
            return;
        }

        crisp8RunCycle (emulator);
        const uint8_t* const framebuffer = crisp8GetFramebuffer (emulator);
        drawFramebuffer (screen, framebuffer);

        capFramerate (&lastTime, &remainderTime, fps);
    }
}

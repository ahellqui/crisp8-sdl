#include "screen.h"
#include "options.h"

// These are the actual window width and height rather than the chip-8's display size.
// The coordinates are not widescreen because the chip-8 wasn't
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 640

#define CHIP8_PIXEL_WIDTH WINDOW_WIDTH / CRISP8_DISPLAY_WIDTH
#define CHIP8_PIXEL_HEIGHT WINDOW_HEIGHT / CRISP8_DISPLAY_HEIGHT

static void clearScreen (struct screen* screen)
{
    SDL_SetRenderDrawColor (screen->renderer, globalOptions.backgroundColor.r,
                                              globalOptions.backgroundColor.g,
                                              globalOptions.backgroundColor.b,
                                              SDL_ALPHA_OPAQUE);
    SDL_RenderClear (screen->renderer);
}

static void presentScreen (struct screen* screen)
{
    SDL_RenderPresent (screen->renderer);
}

void initScreen (struct screen* screen)
{
    screen->window = SDL_CreateWindow ("Crisp8-SDL",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       WINDOW_WIDTH,
                                       WINDOW_HEIGHT,
                                       0);

    screen->renderer = SDL_CreateRenderer (screen->window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode (screen->renderer, SDL_BLENDMODE_BLEND);

    for (int i = 0; i < CRISP8_DISPLAY_WIDTH * CRISP8_DISPLAY_HEIGHT; i++)
    {
        
        screen->displayPixels [i].w = CHIP8_PIXEL_WIDTH;
        screen->displayPixels [i].h = CHIP8_PIXEL_HEIGHT;

        screen->displayPixels [i].x = (i * CHIP8_PIXEL_WIDTH) % WINDOW_WIDTH;
        screen->displayPixels [i].y = (i / CRISP8_DISPLAY_WIDTH) * CHIP8_PIXEL_HEIGHT;
    }
}

void destroyScreen (struct screen* screen)
{
    SDL_DestroyRenderer (screen->renderer);
    SDL_DestroyWindow (screen->window);
}

void drawFramebuffer (struct screen* screen, const uint8_t* const framebuffer)
{
    clearScreen (screen);

    for (int i = 0; i < CRISP8_DISPLAY_WIDTH * CRISP8_DISPLAY_HEIGHT; i++)
    {
        if (framebuffer [i])
        {
            // This frontend is written with the macro CRISP8_DISPLAY_USE_ALPHA defined. Hence, the pixels value are
            // their alpha value.
            SDL_SetRenderDrawColor (screen->renderer, globalOptions.foregroundColor.r,
                                                      globalOptions.foregroundColor.g,
                                                      globalOptions.foregroundColor.b,
                                                      framebuffer [i]);

            SDL_RenderFillRect (screen->renderer, &screen->displayPixels [i]);
        }
    }

    presentScreen (screen);
}

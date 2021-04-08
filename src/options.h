#ifndef CRISP8_SDL_OPTIONS_H
#define CRISP8_SDL_OPTIONS_H

#include <stdint.h>
#include <stddef.h> // NULL

struct rgbColor
{
    uint8_t r, g, b;
};

// Some global config values
extern struct crisp8SdlOptions
{
    // The fps (cycles per second) to run at, capped at 9999 fps
    uint16_t fps;

    // Hex values of background and foreground colors
    struct rgbColor foregroundColor;
    struct rgbColor backgroundColor;

    // The path to the rom
    char* rom;

} globalOptions;


// TODO document and stuff
void optionSetFps (char* fps);
void optionSetRom (char* romPath);
void optionSetFg (char* color);
void optionSetBg (char* color);

#endif

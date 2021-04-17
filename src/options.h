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

    // RGB values of background and foreground colors
    struct rgbColor foregroundColor;
    struct rgbColor backgroundColor;

    // The path to the rom
    char* rom;

} globalOptions;


// Parses the command line options and sets settings based on them.
// argc and argv should be passed directly from main
//
// Parameters:
//  argc: The number of arguments given
//  argv: Array of strings containing the arguments
void parseCommandLine (int argc, char* argv []);
#endif

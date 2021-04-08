#include "options.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// Default values for the global options
struct crisp8SdlOptions globalOptions = {
    .fps = 700,

    .foregroundColor.r = 0,
    .foregroundColor.g = 190,
    .foregroundColor.b = 25,

    .backgroundColor.r = 0,
    .backgroundColor.g = 0,
    .backgroundColor.b = 0,

    .rom = NULL
};

static bool hexStringToColor (char* str, struct rgbColor* colorData)
{
    size_t stringLen = strlen (str);
    if (strspn (str, "0123456789abcdef") != stringLen)
    {
        fputs ("Color value must contain only the digits 0-9 and/or letters a-f (lowercase)\n", stderr);
        return false;
    }
    else if (stringLen != 6)
    {
        fputs ("Color value must be 6 digits long\n", stderr);
        return false;
    }

    uint32_t hexValue = strtoul (str, NULL, 16);
    colorData->r = (hexValue >> 16) & 0xff;
    colorData->g = (hexValue >> 8)  & 0xff;
    colorData->b = (hexValue >> 0)  & 0xff;

    return true;
}

void optionSetFps (char* fps)
{
    const size_t argLength = strlen (fps);
    if (strspn (fps, "0123456789") != argLength)
    {
        fputs ("Fps value must contain only the digits 0-9\n", stderr);
        exit (1);
    }

    // There is no reason for an fps greater than 9999
    if (strlen (fps) > 4)
    {
        fputs ("Fps value to large. A maximum of 9999 is allowed\n", stderr);
        exit (1);
    }

    uint16_t fpsInt = strtoul (fps, NULL, 10);
    globalOptions.fps = fpsInt;
}

void optionSetRom (char* romPath)
{
    // We can actually get away with doing this since argv is stack allocated and the user
    // can't change rom without restarting the program
    globalOptions.rom = romPath;
}

void optionSetFg (char* color)
{
    struct rgbColor colorData;
    if (!(hexStringToColor (color, &colorData)))
    {
        exit (1);
    }

    globalOptions.foregroundColor = colorData;
}

void optionSetBg (char* color)
{
    struct rgbColor colorData;
    if (!(hexStringToColor (color, &colorData)))
    {
        exit (1);
    }

    globalOptions.backgroundColor = colorData;
}



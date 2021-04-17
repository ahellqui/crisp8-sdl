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

// Converts a string of hex numbers into RGB color values.
// The string must contain exactly 6 hexadecimal lowercase digits and must not begin with a hash
//
// Parameters:
//  str: The string to convert
//  colorData: Pointer to the struct in which the converted color data will be placed
//
// Return value:
//  true if the conversion was successful, false otherwise
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

// Sets the fps (cycles per second) of the emulator
//
// Parameters:
//  fps: string containing the desired fps value in base 10
static void cmdOptionSetFps (char* fps)
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

// Sets the path to the rom to load
//
// Parameters:
//  romPath: path to the rom to load
static void cmdOptionSetRom (char* romPath)
{
    // We can actually get away with doing this since argv is stack allocated and the user
    // can't change rom without restarting the program
    globalOptions.rom = romPath;
}

// Sets the foreground color of the emulator
//
// Parameters:
//  color: string containing the desired foreground color in 6 digit lowercase hex format
static void cmdOptionSetFg (char* color)
{
    struct rgbColor colorData;
    if (!(hexStringToColor (color, &colorData)))
    {
        exit (1);
    }

    globalOptions.foregroundColor = colorData;
}

// Sets the background color of the emulator
//
// Parameters:
//  color: string containing the desired background color in 6 digit lowercase hex format
static void cmdOptionSetBg (char* color)
{
    struct rgbColor colorData;
    if (!(hexStringToColor (color, &colorData)))
    {
        exit (1);
    }

    globalOptions.backgroundColor = colorData;
}

void parseCommandLine (int argc, char* argv [])
{
    if (argc == 1)
    {
        return;
    }

    if (argc == 2)
    {
        if (strcmp (argv [1], "--help") == 0)
        {
            /* printHelp (); */
            exit (0);
        }
    }

    if (argc % 2 == 0)
    {
        fprintf (stderr, "Argument %s needs a value\n", argv [argc - 1]);
        exit (1);
    }

    // Skip the program name
    int argCount = 1;
    // Since arguments come in pairs, we need to reserve a place for their value
    while (argCount < argc - 1)
    {
        if (strcmp (argv [argCount], "--fps") == 0)
        {
            cmdOptionSetFps (argv [argCount + 1]);
        }
        else if (strcmp (argv [argCount], "--rom") == 0)
        {
            cmdOptionSetRom (argv [argCount + 1]);
        }
        else if (strcmp (argv [argCount], "--fg") == 0)
        {
            cmdOptionSetFg (argv [argCount + 1]);
        }
        else if (strcmp (argv [argCount], "--bg") == 0)
        {
            cmdOptionSetBg (argv [argCount + 1]);
        }

        argCount += 2;
    }
}


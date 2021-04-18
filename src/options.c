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

    .useAlpha = true,

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

// Prints a help message explaining the usage
static void cmdPrintHelp ()
{
    puts (
           "crisp8-sdl --rom <path to rom> [options]\n"
           "Options:\n"
           "\t--help\tPrint this message and exit\n"
           "\t--fps\tThe fps or really clock cycles per second to run the program at\n"
           "\t--fg\tSet the foreground color to a color specified with a lowercase 6 digit hex string\n"
           "\t--fg\tSet the background color to a color specified with a lowercase 6 digit hex string\n"
         );
}

// Called when a command line option supplied is wrong
//
// Parameters:
//  command: the unrecognized command line option
static void cmdUnrecognized (char* command)
{
    fprintf (stderr, "Unrecognized command line option: %s\n\n", command);
    cmdPrintHelp ();
    exit (1);
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

// Sets whether to use alpha values on the display or not, disabling or enabling the fading pixels
//
// Parameters:
//  shouldUse: true if alpha should be enabled, false otherwise
static void cmdOptionSetAlpha (bool shouldUse)
{
    globalOptions.useAlpha = shouldUse;
}

// Checks for the presence of an argument for commands that need it and increments argCount if it exists
//
// Parameters:
//  argc: the total amount of command line options, should be passed directly from main
//  argCount: the number of the current command line option
//  command: the name of the current command line option
//
// Return value:
//  argCount incremented by one
static int checkCommandArg (int argc, int argCount, char* command)
{
    if (argCount + 1 == argc)
    {
        fprintf (stderr, "Argument %s needs a value\n", command); 
        exit (1);
    }

    return argCount + 1;
}

void parseCommandLine (int argc, char* argv [])
{
    if (argc == 1)
    {
        cmdPrintHelp ();
        exit (0);
    }

    // Skip the program name
    int argCount = 1;
    while (argCount < argc)
    {
        if (strcmp (argv [argCount], "--help") == 0)
        {
            cmdPrintHelp ();
            exit (0);
        }
        else if (strcmp (argv [argCount], "--fps") == 0)
        {
            argCount = checkCommandArg (argc, argCount, argv [argCount]);
            cmdOptionSetFps (argv [argCount]);
        }
        else if (strcmp (argv [argCount], "--rom") == 0)
        {
            argCount = checkCommandArg (argc, argCount, argv [argCount]);
            cmdOptionSetRom (argv [argCount]);
        }
        else if (strcmp (argv [argCount], "--fg") == 0)
        {
            argCount = checkCommandArg (argc, argCount, argv [argCount]);
            cmdOptionSetFg (argv [argCount]);
        }
        else if (strcmp (argv [argCount], "--bg") == 0)
        {
            argCount = checkCommandArg (argc, argCount, argv [argCount]);
            cmdOptionSetBg (argv [argCount]);
        }
        else if (strcmp (argv [argCount], "--no-alpha") == 0)
        {
            cmdOptionSetAlpha (false);
        }
        else
        {
            cmdUnrecognized (argv [argCount]);
        }

        argCount += 1;
    }
}


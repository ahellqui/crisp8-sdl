#include <crisp8.h>

#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "screen.h"
#include "loop.h"
#include "callbacks.h"
#include "sound.h"
#include "options.h"

// Initializes all SDL systems needed
static void initSDL ()
{
    if (SDL_Init (SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
    {
        printf ("Could not initialize SDL; aborting");
        abort ();
    }

    Mix_Init (MIX_INIT_OGG);
    Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_AllocateChannels (1);
}

static void cleanupSDL ()
{
    Mix_CloseAudio ();
    Mix_Quit ();
    SDL_Quit ();
}

// Returns an array containing the program, and puts the size of it in programSize.
// The returned array must be freed by the caller
static uint8_t* loadProgram (const char* programFile, uint16_t* programSize)
{
    if (programFile == NULL)
    {
        fputs ("No rom specified\n", stderr);
        exit (1);
    }

    int tmpProgSize = 200;

    uint8_t* programArr = malloc (tmpProgSize);
    if (!programArr)
    {
        fputs ("Malloc failure in loadProgram; aborting\n", stderr);
        abort ();
    }

    FILE* prog = fopen (programFile, "r");
    if (!prog)
    {
        fprintf (stderr, "Could not open file: %s, aborting\n", programFile);
        exit (1);
    }

    for (int i = 0; i < tmpProgSize; i++)
    {
        fread (programArr + i, 1, 1, prog);
        if (feof (prog))
        {
            *programSize = i;
            break;
        }

        if (i == tmpProgSize - 1)
        {
            tmpProgSize += 200;
            programArr = realloc (programArr, tmpProgSize);
            if (!programArr)
            {
                fputs ("Realloc failure in loadProgram; aborting\n", stderr);
                abort ();
            }
        }
    }

    return programArr;
}

static void initChip8 (chip8* emulator, const char* progFile)
{
    uint16_t progSize;
    uint8_t* prog = loadProgram (progFile, &progSize);

    crisp8Init (emulator);
    crisp8SetInputCallback (*emulator, inputCb);
    crisp8SetAudioCallback (*emulator, audioCb);
    crisp8InitializeProgram (*emulator, prog, progSize);

    free (prog);
}

static void parseCommandLine (int argc, char* argv [])
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
    // Since arguments come in pairs, we need to preserve a place for their value
    while (argCount < argc - 1)
    {
        if (strcmp (argv [argCount], "--fps") == 0)
        {
            optionSetFps (argv [argCount + 1]);
        }
        else if (strcmp (argv [argCount], "--rom") == 0)
        {
            optionSetRom (argv [argCount + 1]);
        }
        else if (strcmp (argv [argCount], "--fg") == 0)
        {
            optionSetFg (argv [argCount + 1]);
        }
        else if (strcmp (argv [argCount], "--bg") == 0)
        {
            optionSetBg (argv [argCount + 1]);
        }

        argCount += 2;
    }
}

int main (int argc, char* argv [])
{
    parseCommandLine (argc, argv);

    initSDL ();
    atexit (cleanupSDL);

    initSound ();

    srand (time (0));

    chip8 emulator;
    initChip8 (&emulator, globalOptions.rom);

    struct screen screen;
    initScreen (&screen);

    loop (emulator, &screen, globalOptions.fps);

    destroyScreen (&screen);
    crisp8Destroy (&emulator);

    return 0;
}

#include <SDL2/SDL.h>

#include <SDL2/SDL_mixer.h>
#include "inits.h"
#include "callbacks.h"

void initSDL ()
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

void cleanupSDL ()
{
    Mix_CloseAudio ();
    Mix_Quit ();
    SDL_Quit ();
}

// Returns an array containing the in bytes, and puts the size of it in programSize.
// The returned array must be freed by the caller
//
// Parameters:
//  - programFile: Path to the rom file to load
//  - programSize: Pointer to a variable in which the size of the rom will be loaded
//
// Return value:
//  A pointer to an array containing the rom
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

    FILE* prog = fopen (programFile, "rb");
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

    fclose (prog);

    return programArr;
}

void initChip8 (chip8* emulator, const char* progFile)
{
    uint16_t progSize;
    uint8_t* prog = loadProgram (progFile, &progSize);

    crisp8Init (emulator);
    crisp8SetInputCallback (*emulator, inputCb);
    crisp8SetAudioCallback (*emulator, audioCb);
    crisp8InitializeProgram (*emulator, prog, progSize);

    free (prog);
}


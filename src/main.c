#include <crisp8.h>

#include <stdio.h>
#include <SDL2/SDL.h>

#include "screen.h"
#include "loop.h"

static void initSDL ()
{
    if (SDL_Init (SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
    {
        printf ("Could not initialize SDL; aborting");
        abort ();
    }
}

static void cleanupSDL ()
{
    SDL_Quit ();
}

// Returns an array containing the program, and puts the size of it in programSize.
// The returned array must be freed by the caller
static uint8_t* loadProgram (const char* programFile, uint16_t* programSize)
{
    int tmpProgSize = 200;

    uint8_t* programArr = malloc (tmpProgSize);
    if (!programArr)
    {
        fputs ("Malloc failure in loadProgram; aborting", stderr);
        abort ();
    }

    FILE* prog = fopen (programFile, "r");

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
                fputs ("Realloc failure in loadProgram; aborting", stderr);
                abort ();
            }
        }
    }

    return programArr;
}

// This will also do things like initialize callbacks as those are added
static void initChip8 (chip8* emulator, const char* progFile)
{
    uint16_t progSize;
    uint8_t* prog = loadProgram (progFile, &progSize);

    crisp8Init (emulator);
    crisp8InitializeProgram (*emulator, prog, progSize);

    free (prog);
}

int main (int argc, char* argv [])
{
    if (argc != 2)
    {
        puts ("Supply the program name as the only argument");
        return 1;
    }

    initSDL ();
    atexit (cleanupSDL);

    chip8 emulator;
    initChip8 (&emulator, argv [1]);

    struct screen screen;
    initScreen (&screen);

    loop (emulator, &screen, 700);

    destroyScreen (&screen);
    crisp8Destroy (&emulator);

    return 0;
}

#include <crisp8.h>

#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "screen.h"
#include "loop.h"
#include "sound.h"
#include "options.h"
#include "inits.h"

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

#include "sound.h"

#include <SDL2/SDL_mixer.h>

// Certainly not a pretty solution, but the only reason I can see to not do this is if you want multiple emulators
// running with different subsystems, which is not something I'm trying to do.
Mix_Chunk* beepSound;
void initSound ()
{
    beepSound = Mix_LoadWAV ("../sound/beep.ogg");
}

void toggleBeep ()
{
    if (Mix_Playing (1))
    {
        Mix_HaltChannel (1);
    }
    else
    {
        Mix_PlayChannel (1, beepSound, -1);
    }
}

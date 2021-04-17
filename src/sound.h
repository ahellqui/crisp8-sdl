#ifndef CRISP8_SDL_SOUND_H
#define CRISP8_SDL_SOUND_H

// Loads the sound file containing the beep. Note that this is not in in inits.h because it doesn't initialize any
// library code
void initSound ();

// Plays a beep sound if it is not playing and stops it otherwise
void toggleBeep ();
#endif

#ifndef NYT_SOUND_h
#define NYT_SOUND_h

#include <Arduino.h>

void soundSetup(void (*getSoundHandlerFunc)(uint8_t *vectors));
void soundLoop();
void setSoundStatus(bool status);

#endif

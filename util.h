#ifndef NYT_UTIL_h
#define NYT_UTIL_h

#include <FastLED.h>
#include "led.h"

char getLedSpeedFromHeader(String getHeader);
int getCalibrationFromHeader(String getHeader);
CRGB getLedColorFromHeader(String getHeader);
ledCells get3DCellFromHeader(String getHeader);
uint8_t getPresetFromHeader(String getHeader);
uint8_t getPresetModeFromHeader(String getHeader);

#endif

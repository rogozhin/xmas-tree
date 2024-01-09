#pragma once

#ifndef NYT_MATRIX_h
#define NYT_MATRIX_h

#include <Arduino.h>

// Arduino_LED_Matrix.h doesn't compatible with FastLED on renesas platform?
// I've found that PORT macro is conflicting,
// so rename macro PORT on FastLED/src/platforms/arm/renesas/fastpin_arm_renesas.h

#define SYMBOL(_SYMBOL) symbols[_SYMBOL]

#define MATRIX_SYMBOL_OFF 0
#define MATRIX_SYMBOL_BYE 1
#define MATRIX_SYMBOL_HOURGLASS 2
#define MATRIX_SYMBOL_HI 3
#define MATRIX_SYMBOL_SHUFFLE 4
#define MATRIX_SYMBOL_REPEAT 5

void matrixSetup();
void matrixLoop();

void showSymbol(uint8_t symbol, uint32_t delay, bool restoreState);
void showSymbol(uint8_t symbol, uint32_t delay);
void showSymbol(uint8_t symbol);

#endif

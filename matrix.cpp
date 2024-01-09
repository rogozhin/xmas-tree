#include "matrix.h"
#include "Arduino_LED_Matrix.h"

uint32_t symbols[6][3] = {
  {0, 0, 0},
  {0x00007c00, 0x8010f202, 0x7c400f00},
  {0x1f81080f, 0x00600600, 0x901081f8},
  {0x00084984, 0x1849fc98, 0x49848849},
  {0x002f0f09, 0x20200400, 0x92f0f002},
  {0x0003fc40, 0x28018014, 0x123bc010}
};

ArduinoLEDMatrix matrix;

uint32_t matrixPrevFrame = 0;
uint32_t matrixDelay = 0;

void matrixSetup() {
  matrix.begin();
}

void matrixLoop() {
  if (matrixPrevFrame) {
    uint32_t currentTime = millis();
    if (matrixPrevFrame + matrixDelay < currentTime) {
      matrixPrevFrame = 0;
      matrix.loadFrame(SYMBOL(MATRIX_SYMBOL_OFF));
      // TODO restore state
    }
  }
}

void showSymbol(uint8_t symbol, uint32_t delay, bool restoreState) {
  matrix.loadFrame(SYMBOL(symbol));
  if (delay) {
    matrixPrevFrame = millis();
    matrixDelay = delay;
    // TODO restore state
  }
}
void showSymbol(uint8_t symbol, uint32_t delay) {
  showSymbol(symbol, delay, false);
}
void showSymbol(uint8_t symbol) {
  showSymbol(symbol, 0, false);
}

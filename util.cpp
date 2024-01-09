#include "util.h"

struct cellPos {
  uint8_t from;
  uint8_t to;
};

uint8_t doubleHex2int(char hex) {
    uint8_t val = 0;
    if (hex >= '0' && hex <= '9') hex = hex - '0';
    else if (hex >= 'a' && hex <='f') hex = hex - 'a' + 10;
    else if (hex >= 'A' && hex <='F') hex = hex - 'A' + 10;
    val = (hex << 4) | (hex & 0xF);
    return val;
}

CRGB parseColor(String colorStr) {
  int r = doubleHex2int(colorStr[0]);
  int g = doubleHex2int(colorStr[1]);
  int b = doubleHex2int(colorStr[2]);
  return CRGB(r, g, b);
}

uint8_t parseChar(char c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  }
  if (c >= 'a' && c <='Z') {
    return c - 'a' + 10;
  }
  if (c >= 'A' && c <='Z') {
    return c - 'A' + 10;
  }
  return 255;
}

cellPos parseCellCoordinate(char f, char t) {
  uint8_t from = parseChar(f);
  uint8_t to = parseChar(t);
  return {from, to};
}

int getCalibrationFromHeader(String getHeader) {
  int ledPos = getHeader.indexOf("led=");
  int ledPosEnd = getHeader.indexOf("&", ledPos);
  if (ledPos == -1 || ledPosEnd == -1) {
    return -1;
  }
  return getHeader.substring(ledPos + 4, ledPosEnd).toInt();
}

CRGB getLedColorFromHeader(String getHeader) {
  int colorPos = getHeader.indexOf("color=");
  int colorPosEnd = getHeader.indexOf("&", colorPos);

  if (colorPos == -1 || colorPosEnd == -1) {
    return NULL;
  }

  return parseColor(getHeader.substring(colorPos + 6, colorPosEnd));
}

char getLedSpeedFromHeader(String getHeader) {
  int speedPos = getHeader.indexOf("v=");
  if (speedPos == -1) {
    return -1;
  }
  return getHeader.charAt(speedPos + 2);
}

ledCells get3DCellFromHeader(String getHeader) {
  ledCells cells;
  // TODO make cells=abcdef, where fromX=a, toX=b, fromY=c, toY=d, fromZ=e, toZ=f
  int cellXPos = getHeader.indexOf("x=");
  int cellYPos = getHeader.indexOf("y=");
  int cellZPos = getHeader.indexOf("z=");
  if (cellXPos == -1 || cellYPos == -1 || cellZPos == -1) {
    cells = {255, 255, 255, 255, 255, 255};
    return cells;
  }
  cellPos x = parseCellCoordinate(getHeader.charAt(cellXPos + 2), getHeader.charAt(cellXPos + 3));
  cellPos y = parseCellCoordinate(getHeader.charAt(cellYPos + 2), getHeader.charAt(cellYPos + 3));
  cellPos z = parseCellCoordinate(getHeader.charAt(cellZPos + 2), getHeader.charAt(cellZPos + 3));

  cells = {x.from, y.from, z.from, x.to, y.to, z.to};

  return cells;
}

uint8_t getPresetFromHeader(String getHeader) {
  int presetPos = getHeader.indexOf("preset=");
  if (presetPos == -1) {
    return 0;
  }
  return getHeader.charAt(presetPos + 7) - '0';
}
uint8_t getPresetModeFromHeader(String getHeader) {
  int presetModePos = getHeader.indexOf("mode=");
  if (presetModePos == -1) {
    return 0;
  }
  return getHeader.charAt(presetModePos + 5) - '0';
}

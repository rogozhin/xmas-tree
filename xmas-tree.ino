#define IS_WIFI_ON 1
#define IS_SOUND_ON 1

#include <Arduino.h>
#if defined(IS_WIFI_ON) && (IS_WIFI_ON==1)
  #include "wifi.h"
#endif
#include "led.h"
#include "ir.h"
#include "matrix.h"
#include "util.h"
#if defined(IS_SOUND_ON) && (IS_SOUND_ON==1)
  #include "sound.h"
#endif

#define IR_MODE_NORMAL 0
#define IR_MODE_CALIBRATION 1
#define IR_MODE_PRESET_COLOR 2
uint8_t irMode = 0;

void setCalibrationLed(String getHeader) {
  int ledNum = getCalibrationFromHeader(getHeader);
  if (ledNum == -1) {
    return;
  }
  CRGB color = getLedColorFromHeader(getHeader);
  ledSetMode(MODE_CALIBRATION);
  ledOn(ledNum, color != NULL ? color: CRGB::White);
}

void setLedSpeed(String getHeader) {
  char speed = getLedSpeedFromHeader(getHeader);
  if (speed == -1) {
    return;
  }
  setSpeed(speed);
};

void setAllColor(String getHeader) {
  CRGB color = getLedColorFromHeader(getHeader);
  if (color == NULL) {
    return;
  }
  letSetPresetColor(color);
  ledSetMode(MODE_PRESET, PRESET_SOLID);
}

void set3DCell(String getHeader) {
  ledCells cells = get3DCellFromHeader(getHeader);
  CRGB color = getLedColorFromHeader(getHeader);
  if (color == NULL) {
    color = CRGB::Black;
  }
  ledSetMode(MODE_ONLINE);
  ledSetCell(cells, color);
  FastLED.show();
}

void setPreset(String getHeader) {
  uint8_t presetId = getPresetFromHeader(getHeader);
  uint8_t presetMode = getPresetModeFromHeader(getHeader);
  if (!presetId) {
    return;
  }
  LedPresetElement preset = getPresetById(presetId);
  if (preset.id == PRESET_SOLID) {
    letSetPresetColor();
  }
  ledSetMode(MODE_PRESET, preset.id, preset.modeLen > 0 ? presetMode : 0);
}

void setPresetAndMode(uint8_t presetId) {
  setShuffleMode(false);
  LedMode mode = ledGetMode();
  if (mode.preset == presetId) {
    nextPresetMode();
  } else {
    LedPresetElement preset = getPresetById(presetId);
    ledSetMode(MODE_PRESET, preset.id, preset.defaultMode);
  }
}

void handleWifiCommand(String getHeader) {
  if (getHeader.startsWith("GET /preset")) {
    setPreset(getHeader);
    return;
  }
  if (getHeader.startsWith("GET /cal")) {
    setCalibrationLed(getHeader);
    return;
  }
  if (getHeader.startsWith("GET /speed")) {
    setLedSpeed(getHeader);
    return;
  }
  if (getHeader.startsWith("GET /color")) {
    setAllColor(getHeader);
    return;
  }
  if (getHeader.startsWith("GET /3d")) {
    set3DCell(getHeader);
    return;
  }
  if (getHeader.startsWith("GET /shuffle")) {
    setShuffleMode();
    return;
  }
  if (getHeader.startsWith("GET /state")) {
    return;
  }
}
void irCallbackNormal(uint32_t command, bool repeat) {
  switch (command) {
    case 0x45: // button 1
      setShuffleMode(false);
      letSetPresetColor();
      ledSetMode(MODE_PRESET, PRESET_SOLID);
      break;
      // solid preset
    case 0x46: // button 2
      // spark preset
      setPresetAndMode(PRESET_SPARK);
      break;
    case 0x47: // button 3
      // rainbow preset
      setShuffleMode(false);
      ledSetMode(MODE_PRESET, PRESET_RAINBOW);
      break;
    case 0x44: // button 4
      // collect preset
      setPresetAndMode(PRESET_COLLECT);
      break;
    case 0x40: // button 5
      // flag preset
      setPresetAndMode(PRESET_FLAG_WAVE);
      break;
    case 0x43: // button 6
      setPresetAndMode(PRESET_FLAG_SIREN);
      break;
    case 0x7: // button 7
      setPresetAndMode(PRESET_SOUND);
      break;

    case 0x18: // button "up"
    case 0x20022: // button "up" logitech
      setBrightness('+');
      break;
    case 0x52: // button "down"
    case 0x20023: // button "down" logitech
      setBrightness('-');
      break;
    case 0x8: // button "left"
    case 0x20020: // button "menu" logitech
      setSpeed('-');
      break;
    case 0x5A: // button "right"
    case 0x20021: // button "select" logitech
      setSpeed('+');
      break;
    case 0x1C: // button "ok"
    case 0x20009: // button "on/off" logitech
      if (ledsStatus()) {
        showSymbol(MATRIX_SYMBOL_BYE, 1000, false);
        ledsOff();
      } else {
        ledsOn();
      }
      break;
    case 0x20015: // button "next" logitech
      nextPreset();
      break;
    case 0x2000A: // button "prev" logitech
      prevPreset();
      break;
    case 0x2000C: // button "play" logitech
      nextPresetMode();
      break;
    case 0x20066: // button "shuffle" logitech
      setShuffleMode(true);
      setRandomPreset();
      break;
    case 0x20012: // button "repeat" logitech
      setShuffleMode(false);
      break;

    case 0x15: // button 8
    case 0x9: // button 9
    case 0x19: // button 0
    case 0x16: // button *
    case 0xD: // button #
    case 0x20016: // button "signal" logitech
    case 0x2000D: // button "+" logitech
    case 0x2000E: // button "-" logitech
    default:
      break;
  }
}
void irCallbackPresetColor(uint16_t command, bool repeat) {
  #define PRESET_COLOR_STEP 0x10
  uint8_t preset = 0;
  uint8_t presetMode = 0;
  LedMode mode = ledGetMode();

  switch (command) {
    case 0x44: // button 4
      if (mode.presetColor.red < PRESET_COLOR_STEP) {
        mode.presetColor.red = 0;
      } else {
        mode.presetColor.red -= PRESET_COLOR_STEP;
      }
      break;
    case 0x45: // button 1
      if (mode.presetColor.red + PRESET_COLOR_STEP >= 0xFF) {
        mode.presetColor.red = 0xFF;
      } else {
        mode.presetColor.red += PRESET_COLOR_STEP;
      }
      break;

    case 0x40: // button 5
      if (mode.presetColor.green < PRESET_COLOR_STEP) {
        mode.presetColor.green = 0;
      } else {
        mode.presetColor.green -= PRESET_COLOR_STEP;
      }
      break;
    case 0x46: // button 2
      if (mode.presetColor.green + PRESET_COLOR_STEP >= 0xFF) {
        mode.presetColor.green = 0xFF;
      } else {
        mode.presetColor.green += PRESET_COLOR_STEP;
      }
      break;

    case 0x43: // button 6
      if (mode.presetColor.blue < PRESET_COLOR_STEP) {
        mode.presetColor.blue = 0;
      } else {
        mode.presetColor.blue -= PRESET_COLOR_STEP;
      }
      break;
    case 0x47: // button 3
      if (mode.presetColor.blue + PRESET_COLOR_STEP >= 0xFF) {
        mode.presetColor.blue = 0xFF;
      } else {
        mode.presetColor.blue += PRESET_COLOR_STEP;
      }
      break;
  }
  letSetPresetColor(mode.presetColor);
  Serial.print("preset color ");
  Serial.print(mode.presetColor.red, HEX);
  Serial.print(" ");
  Serial.print(mode.presetColor.green, HEX);
  Serial.print(" ");
  Serial.println(mode.presetColor.blue, HEX);
}
void irCallback(uint16_t address, uint16_t command, bool repeat) {
  uint32_t cmd = address << 16 | command;
  Serial.print("ir ");
  Serial.print(cmd, HEX);
  Serial.print(" ");
  Serial.println(repeat ? "repeat" : "");
  #if defined(LED_CORRECTION_MODE) && (LED_CORRECTION_MODE==1)
    irCorrection(command);
    return;
  #endif
  switch (cmd) {
    case 0x16: // button *
      irMode = irMode == IR_MODE_NORMAL ? IR_MODE_PRESET_COLOR : IR_MODE_NORMAL;
      return;
  }
  if (irMode == IR_MODE_NORMAL) {
    irCallbackNormal(cmd, repeat);
  } else if (irMode == IR_MODE_PRESET_COLOR) {
    irCallbackPresetColor(cmd, repeat);
  }
}
void handleSound(uint8_t *vectors) {
  setSoundLevels(vectors[1], vectors[2], vectors[3]);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial.println("Warming up...");
  matrixSetup();
  showSymbol(MATRIX_SYMBOL_HOURGLASS);

  ledSetup();
  #if defined(IS_WIFI_ON) && (IS_WIFI_ON==1)
    wifiSetup(handleWifiCommand);
  #endif
  irSetup(irCallback);
  showSymbol(MATRIX_SYMBOL_HI, 1000);
  #if defined(IS_SOUND_ON) && (IS_SOUND_ON==1)
    soundSetup(handleSound);
  #endif
  Serial.println("Warm!");
}

void loop() {
  #if defined(IS_WIFI_ON) && (IS_WIFI_ON==1)
    wifiLoop();
  #endif
  irLoop();
  matrixLoop();
  ledLoop();
  #if defined(IS_SOUND_ON) && (IS_SOUND_ON==1)
    soundLoop();
  #endif
}

#if defined(LED_CORRECTION_MODE) && (LED_CORRECTION_MODE==1)
  // 0xFF8A50
  uint8_t corr_r = (LED_CORRECTION & 0xFF0000) >> 16;
  uint8_t corr_g = (LED_CORRECTION & 0x00FF00) >> 8;
  uint8_t corr_b = LED_CORRECTION & 0x0000FF;
  uint8_t corr_st = 10;
  void irCorrection(uint16_t command) {
      switch (command) {
      case 0x44: // button 4
        if (corr_r < corr_st) {
          corr_r = 0;
        } else {
          corr_r -= corr_st;
        }
        break;
      case 0x45: // button 1
        if (corr_r + corr_st > 0xFF) {
          corr_r = 0xFF;
        } else {
          corr_r += corr_st;
        }
        break;

      case 0x40: // button 5
        if (corr_g < corr_st) {
          corr_g = 0;
        } else {
          corr_g -= corr_st;
        }
        break;
      case 0x46: // button 2
        if (corr_g + corr_st > 0xFF) {
          corr_g = 0xFF;
        } else {
          corr_g += corr_st;
        }
        break;

      case 0x43: // button 6
        if (corr_b < corr_st) {
          corr_b = 0;
        } else {
          corr_b -= corr_st;
        }
        break;
      case 0x47: // button 3
        if (corr_b + corr_st > 0xFF) {
          corr_b = 0xFF;
        } else {
          corr_b += corr_st;
        }
        break;
    }
    FastLED.setCorrection(CRGB(corr_r, corr_g, corr_b));
    Serial.print("correction ");
    Serial.print(corr_r, HEX);
    Serial.print(corr_g, HEX);
    Serial.println(corr_b, HEX);
  }
#endif

// EEPROM
// https://docs.arduino.cc/tutorials/uno-r4-wifi/eeprom

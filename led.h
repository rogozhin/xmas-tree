#ifndef NYT_LED_h
#define NYT_LED_h

#include <FastLED.h>
#include "led_settings.h"
#include "led_matrix.hpp"
#include "led_programs.h"

#define PALETTE_LEN 30
static uint32_t palette[30] = {
  0xffffff, 0xff0000, 0xff8000, 0xffbf00, 0xffff00, 0x80ff00, 0x00ff00,
  0x00ff80, 0x00ffff, 0x0080ff, 0x0000ff, 0x8000ff, 0xff00ff, 0xff0080,
  0xff1744, 0xf50057, 0xd500f9, 0x651fff, 0x3d5afe, 0x2979ff, 0x00b0ff,
  0x00e5ff, 0x1de9b6, 0x00e676, 0x76ff03, 0xc6ff00, 0xffea00, 0xffc400,
  0xff9109, 0xff3d00
};

#define MODE_CALIBRATION 1
#define MODE_PRESET 2
#define MODE_ONLINE 3

#define DEFAULT_PRESET PRESET_SPARK
#define DEFAULT_PRESET_MODE PRESET_MODE_SPARK_WARM_INVERSE
#define DEFAULT_MODE MODE_PRESET

struct LedMode {
  bool isOn = true;
  uint8_t brightness = DEFAULT_BRIGHTNESS;
  uint8_t speed = DEFAULT_SPEED;
  uint8_t mode = DEFAULT_MODE;
  uint8_t preset = PRESET_SOLID;
  bool shuffle = DEFAULT_SHUFFLE;
  uint8_t presetMode = 0;
  CRGB presetColor = 0;
  uint16_t presetStep = 0;
  uint16_t presetStepSmall = 0;
  uint32_t presetStepBig = 0;
  bool presetInited = false;
};
struct ledCells {
  uint8_t fromX;
  uint8_t fromY;
  uint8_t fromZ;
  uint8_t toX;
  uint8_t toY;
  uint8_t toZ;
};

void ledSetup();
void ledLoop();
void ledSetMode(uint8_t newMode);
void ledSetMode(uint8_t newMode, uint8_t newPreset);
void ledSetMode(uint8_t newMode, uint8_t newPreset, uint8_t newPresetMode);
void letSetPresetColor();
void letSetPresetColor(CRGB newColor);
void ledOn(int ledNum, CRGB color);
void ledOff(int ledNum);
bool ledsStatus();
void ledsSwitch();
void ledsOn();
void ledsOff();
void setSpeed(char speed);
void setBrightness(char brightness);
LedPresetElement getPresetById(uint8_t presetId);
void nextPreset();
void prevPreset();
void nextPresetMode();
void setRandomPreset();
void setShuffleMode(bool shuffle);
void setShuffleMode();
LedMode ledGetMode();
void ledSetCell(ledCells cells, CRGB color);
void doLedCommand(ledCommand command);

void setSoundLevels(uint8_t a, uint8_t b, uint8_t c);

// presets
void ledPresetSparkLoop();
void ledPresetRainbowLoop();
void ledPresetCollectLoop();
void ledPresetFlagWaveLoop();
void ledPresetFlagWaveSetup();
void ledPresetFlagSirenLoop();
void ledPresetSoundLoop();

#endif

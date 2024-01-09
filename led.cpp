#define FASTLED_HAS_CLOCKLESS 1 // fix VS Code IntelliSense issue

#include "led.h"
#include "rnd.hpp"
#include "matrix.h"
#include "sound.h"

CRGB leds[NUM_LEDS];

#define DELAY 1
#define STEP_SIZE 25

#define WARM_WHITE_COLOR CRGB(0xff, 0x50, 0x00)
#define WARM_WHITE_BRIGHT_COLOR CRGB(0xff, 0x8f, 0x2f)
#define WARM_WHITE_DARK_COLOR CRGB(0xaa, 0x25, 0x2f) // TODO check color

LedMode ledMode;

uint32_t prevFrame = 0;
bool isSoundFrameShowed = false;

uint8_t soundLevels[3] = {};

#define GET_FRAME_DELAY (1000 / FPS) * (11 - ledMode.preset == PRESET_SOUND ? 11 : ledMode.speed)

uint8_t programStep_test = 0;
void doTestProgram() {
  if (programStep_test >= sizeof(testProgram) / sizeof(testProgram[0])) {
    programStep_test = 0;
  }
  ledCommand command = testProgram[programStep_test];
  doLedCommand(command);
  programStep_test++;
}

void ledsClear() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

#define FADE_MIN_R 1
#define FADE_MIN_G 7
#define FADE_MIN_B 10
CRGB fadeColor(CRGB color, uint8_t fade, uint8_t maxFade) {
  if (fade >= maxFade) {
    return CRGB::Black;
  }
  uint8_t r = color.r >> fade;
  uint8_t g = color.g >> fade;
  uint8_t b = color.b >> fade;
  if (r < FADE_MIN_R && color.r != 0 || g < FADE_MIN_G && color.g != 0 || b < FADE_MIN_B && color.b != 0) {
    return CRGB::Black;
  }
  return CRGB(r, g, b);
}

void ledLoopPresetSetup() {
  switch (ledMode.preset) {
    case PRESET_FLAG_WAVE:
      ledPresetFlagWaveSetup();
      break;
    case PRESET_SPARK:
      ledMode.presetColor = ledMode.presetMode == PRESET_MODE_SPARK_WARM || ledMode.presetMode == PRESET_MODE_SPARK_WARM_INVERSE
        ? WARM_WHITE_COLOR
        : CRGB::White;
      if (ledMode.presetMode == PRESET_MODE_SPARK_WARM_INVERSE || ledMode.presetMode == PRESET_MODE_SPARK_WHITE_INVERSE) {
        fill_solid(leds, NUM_LEDS, ledMode.presetColor);
      } else {
        ledsClear();
      }
      break;
    case PRESET_RAINBOW:
    case PRESET_COLLECT:
    case PRESET_SOLID:
    default:
      ledsClear();
      break;
  }
  ledMode.presetInited = true;
}
void ledLoopPreset() {
  if (!ledMode.presetInited) {
    ledLoopPresetSetup();
  }
  switch (ledMode.preset) {
    case PRESET_SOLID:
      fill_solid(leds, NUM_LEDS, ledMode.presetColor);
      FastLED.show();
      break;
    case PRESET_SPARK:
      ledPresetSparkLoop();
      break;
    case PRESET_RAINBOW:
      ledPresetRainbowLoop();
      break;
    case PRESET_COLLECT:
      ledPresetCollectLoop();
      break;
    case PRESET_FLAG_WAVE:
      ledPresetFlagWaveLoop();
      break;
    case PRESET_FLAG_SIREN:
      ledPresetFlagSirenLoop();
      break;
    case PRESET_SOUND:
      ledPresetSoundLoop();
      break;
    default:
      break;
  }
}

bool isLedPresetLoop() {
  uint32_t currentTime = millis();
  if (ledMode.presetStepBig == 0 || !ledMode.shuffle) {
    ledMode.presetStepBig = currentTime;
  }
  if (ledMode.shuffle && ledMode.presetStepBig + BIG_STEP_DELAY < currentTime) {
    ledMode.presetStepBig = currentTime;
    setRandomPreset();
  }
  if (ledMode.preset == PRESET_SOUND && !isSoundFrameShowed) {
    isSoundFrameShowed = true;
    return true;
  }
  if (prevFrame + GET_FRAME_DELAY < currentTime) {
    prevFrame = currentTime;
    return true;
  }
  return false;
}
void ledPresetLoop() {
  bool doLoop = isLedPresetLoop();
  if (!doLoop) {
    return;
  }
  #if defined(LED_CORRECTION_MODE) && (LED_CORRECTION_MODE==1)
    for (uint8_t i = 0; i < 50; i++) {
      leds[i] = CRGB::White;
    }
    FastLED.show();
    return;
  #endif

  switch (ledMode.mode) {
    case MODE_PRESET:
      ledLoopPreset();
      break;
    default:
      break;
  }
  FastLED.show();
}

void ledSetup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, 0, NUM_LEDS);
  FastLED.setBrightness(ledMode.brightness);
  FastLED.setCorrection(LED_CORRECTION);
  ledSetMode(MODE_PRESET, DEFAULT_PRESET, DEFAULT_PRESET_MODE);
}

void ledLoop() {
  if (!ledMode.isOn) {
    return;
  }
  if (ledMode.mode == MODE_PRESET) {
    ledPresetLoop();
  }
}

void setLedSoundStatus() {
  if (ledMode.preset == PRESET_SOUND) {
    setSoundStatus(true);
  } else {
    setSoundStatus(false);
  }
}

void ledSetMode(uint8_t newMode) {
  ledMode.mode = newMode;
  ledMode.presetStep = 0;
  ledMode.presetStepSmall = 0;
  ledMode.preset = DEFAULT_PRESET;
  ledMode.presetMode = DEFAULT_PRESET_MODE;
  ledMode.presetInited = false;

  if (ledMode.mode == MODE_CALIBRATION) {
    ledsClear();
  }
  setLedSoundStatus();
}
void ledSetMode(uint8_t newMode, uint8_t newPreset) {
  ledSetMode(newMode);
  ledMode.preset = newPreset;
  setLedSoundStatus();
}
void ledSetMode(uint8_t newMode, uint8_t newPreset, uint8_t newPresetMode) {
  ledSetMode(newMode, newPreset);
  ledMode.presetMode = newPresetMode;
  setLedSoundStatus();
}

void letSetPresetColor() {
  letSetPresetColor(CRGB(palette[random(0, PALETTE_LEN)]));
}
void letSetPresetColor(CRGB newColor) {
  ledMode.presetColor = newColor;
}

void ledOn(int ledNum, CRGB color) {
  leds[ledNum] = color;
  FastLED.show();
}
void ledOff(int ledNum) {
  leds[ledNum] = CRGB::Black;
  FastLED.show();
};

bool ledsStatus() {
  return ledMode.isOn;
}
void ledsSwitch() {
  if (ledMode.isOn) {
    ledsOff();
  } else {
    ledsOn();
  }
}
void ledsOn() {
  ledMode.isOn = true;
  setLedSoundStatus();
}
void ledsOff() {
  ledMode.isOn = false;
  ledsClear();
  ledMode.presetInited = false;
  setSoundStatus(false);
}

uint16_t* getCellLeds(uint8_t x, uint8_t y, uint8_t z) {
  return getMatrixLeds(x, y, z);
}

void ledSetCell(ledCells cells, CRGB color) {
  if (cells.toX == 255 || cells.toY == 255 || cells.toZ == 255) {
    return;
  }

  for (uint8_t x = cells.fromX; x <= cells.toX; x++) {
    for (uint8_t y = cells.fromY; y <= cells.toY; y++) {
      for (uint8_t z = cells.fromZ; z <= cells.toZ; z++) {
        uint16_t* cellLeds = getCellLeds(x, y, z);
        uint8_t size = cellLeds[0];
        if (size == 0) {
          continue;
        }
        for (uint16_t i = 1; i < size + 1; i++) {
          leds[cellLeds[i]] = color;
        }
      }
    }
  }
}
void ledSetCell(uint8_t fromAngle, uint8_t toAngle, uint8_t fromZ, uint8_t toZ, CRGB color) {
  for (uint8_t x = 0; x < MATRIX_SIZE; x++) {
    for (uint8_t y = 0; y < MATRIX_SIZE; y++) {
      if (ledAngles[x][y] >= fromAngle && ledAngles[x][y] <= toAngle) {
        ledSetCell({x, y, fromZ, x, y, toZ}, color);
      }
    }
  }
}
void ledSetCell(uint8_t fromAngle, uint8_t toAngle, CRGB color) {
  ledSetCell(fromAngle, toAngle, 0, MATRIX_HEIGHT - 1, color);
}

CRGB decodeColorFromCommand(uint16_t color) {
  uint8_t r = ((color & CMD_R) >> 12) | ((color & CMD_R) >> 8);
  uint8_t g = ((color & CMD_G) >> 8) | ((color & CMD_G) >> 4);
  uint8_t b = (color & CMD_B) | ((color & CMD_B) << 4);

  return CRGB(r, g, b);
}

void doLedCommand(ledCommand command) {
  uint8_t fromX = (command.x & CMD_FROM_X) >> 4;
  uint8_t toX = command.x & CMD_TO_X;
  uint8_t fromY = (command.y & CMD_FROM_Y) >> 4;
  uint8_t toY = command.y & CMD_TO_Y;
  uint8_t fromZ = (command.z & CMD_FROM_Z) >> 4;
  uint8_t toZ = command.z & CMD_TO_Z;
  bool show = (command.x & CMD_SHOW) == CMD_SHOW;
  CRGB color = decodeColorFromCommand(command.color);

  ledSetCell({fromX, fromY, fromZ, toX, toY, toZ}, color);

  if (show) {
    FastLED.show();
  }
}

void setSpeed(char speed) {
  if (speed == '+') {
    ledMode.speed += 1;
    if (ledMode.speed > 10) {
      ledMode.speed = 10;
    }
  } else if (speed == '-') {
    ledMode.speed -= 1;
    if (ledMode.speed < 1) {
      ledMode.speed = 1;
    }
  } else {
    if (speed >= '0' && speed <= '9') {
      ledMode.speed = speed - '0' + 1;
    }
  }
}

void setBrightness(char brightness) {
  if (brightness == '+') {
    if (ledMode.brightness + BRIGHTNESS_STEP >= 255) {
      ledMode.brightness = 255;
    } else {
      ledMode.brightness += BRIGHTNESS_STEP;
    }
  } else if (brightness == '-') {
    if (ledMode.brightness - BRIGHTNESS_STEP <= BRIGHTNESS_MIN) {
      ledMode.brightness = BRIGHTNESS_MIN;
    } else {
      ledMode.brightness -= BRIGHTNESS_STEP;
    }
  } else {
    if (brightness >= '0' && brightness <= '9') {
      ledMode.brightness = (brightness - '0' + 1) * BRIGHTNESS_MIN;
    }
  }
  FastLED.setBrightness(ledMode.brightness);
}

CRGB getRandomPaletteColor(uint16_t seed) {
  return CRGB(palette[getRandomNumber(seed, PALETTE_LEN)]);
}

void incPresetStep(uint16_t limit) {
  ledMode.presetStep++;
  if (ledMode.presetStep >= limit) {
    ledMode.presetStep = 0;
  }
}

LedMode ledGetMode() {
  return ledMode;
}

LedPresetElement getPresetById(uint8_t presetId) {
  if (presetId == 0xFF) {
    return ledPresetList[LED_PRESETS_LEN - 1];
  }
  if (presetId > LED_PRESETS_LEN) {
    return ledPresetList[0];
  }
  for (uint8_t i = 0; i < LED_PRESETS_LEN; i++) {
    if (ledPresetList[i].id == presetId) {
      return ledPresetList[i];
    }
  }
  return ledPresetList[0];
}
void nextPreset() {
  LedPresetElement nextPreset = getPresetById(ledMode.preset + 1);
  ledSetMode(MODE_PRESET, nextPreset.id, nextPreset.defaultMode);
}
void prevPreset() {
  LedPresetElement nextPreset = getPresetById(ledMode.preset - 1);
  ledSetMode(MODE_PRESET, nextPreset.id, nextPreset.defaultMode);
}
void nextPresetMode() {
  if (ledMode.preset == PRESET_SOLID) {
    letSetPresetColor();
    return;
  }
  uint8_t presetId = ledMode.preset;
  uint8_t presetMode = ledMode.presetMode;
  if (presetMode == 0) {
    return;
  }
  LedPresetElement preset = getPresetById(presetId);
  presetMode++;
  if (presetMode > preset.modeLen) {
    presetMode = 1;
  }
  ledSetMode(MODE_PRESET, presetId, presetMode);
}
void setRandomPreset() {
  uint8_t presetNum = random(0, LED_PRESETS_LEN);
  uint8_t presetMode = ledPresetList[presetNum].modeLen > 1 ? random(1, ledPresetList[presetNum].modeLen + 1) : 0;
  ledSetMode(MODE_PRESET, ledPresetList[presetNum].id, presetMode);
}

void showShuffleSymbol() {
  showSymbol(ledMode.shuffle ? MATRIX_SYMBOL_SHUFFLE : MATRIX_SYMBOL_REPEAT, 1000);
}
void setShuffleMode(bool shuffle) {
  bool prevShuffle = ledMode.shuffle;
  ledMode.shuffle = shuffle;
  if (prevShuffle != ledMode.shuffle) {
    showShuffleSymbol();
  }
}
void setShuffleMode() {
  ledMode.shuffle = !ledMode.shuffle;
  showShuffleSymbol();
}
void setSoundLevels(uint8_t a, uint8_t b, uint8_t c) {
  soundLevels[0] = a;
  soundLevels[1] = b;
  soundLevels[2] = c;
  isSoundFrameShowed = false;
}

// presets

#define P_SPARK_SPARKS 50
#define P_SPARK_FADE 8
#define P_SPARK_STEPS 500
CRGB getSparkColor(uint16_t dotStep) {
  if (ledMode.presetMode == PRESET_MODE_SPARK_COLOR) {
    return getRandomPaletteColor(dotStep);
  }
  return ledMode.presetColor;
}
void ledPresetSparkLoop() {
  for (uint8_t s = 0; s < P_SPARK_SPARKS; s++) {
    uint16_t dotStep = ledMode.presetStep * P_SPARK_SPARKS + s;
    uint16_t spark = getRandomNumber(dotStep, NUM_LEDS);
    CRGB color = getSparkColor(dotStep);
    leds[spark] = color;
    for (int16_t i = ledMode.presetStep - 1; i >= 0 && i + P_SPARK_FADE > ledMode.presetStep; i--) {
      dotStep = i * P_SPARK_SPARKS + s;
      spark = getRandomNumber(dotStep, NUM_LEDS);
      uint16_t fade = ledMode.presetMode == PRESET_MODE_SPARK_WARM_INVERSE || ledMode.presetMode == PRESET_MODE_SPARK_WHITE_INVERSE
        ? (P_SPARK_FADE - (ledMode.presetStep - i)) / 3
        : ledMode.presetStep - i;
      color = getSparkColor(dotStep);
      color = fadeColor(color, fade, P_SPARK_FADE);
      leds[spark] = color;
    }
  }
  incPresetStep(P_SPARK_STEPS);
}

#define P_RAINBOW_HUE_STEP 5
#define P_RAINBOW_STEPS 255 / P_RAINBOW_HUE_STEP
void ledPresetRainbowLoop() {
  fill_rainbow_circular(leds, NUM_LEDS, ledMode.presetStep * P_RAINBOW_HUE_STEP, 0);

  incPresetStep(P_RAINBOW_STEPS);
}

void ledPresetCollectLoop() {
  if (
    (ledMode.presetMode != PRESET_MODE_COLLECT_FULL && ledMode.presetStepSmall == 0)
    || (ledMode.presetStep == 0 && ledMode.presetStepSmall == 0)
  ) {
    ledMode.presetColor = getRandomPaletteColor(millis());
  }

  uint8_t z = MATRIX_HEIGHT - ledMode.presetStepSmall - 1;

  ledSetCell({0, 0, z, MATRIX_SIZE, MATRIX_SIZE, z}, ledMode.presetColor);

  if (ledMode.presetMode == PRESET_MODE_COLLECT_CLEAR || ledMode.presetMode == PRESET_MODE_COLLECT_FULL) {
    z++;
    ledSetCell({0, 0, z, MATRIX_SIZE, MATRIX_SIZE, z}, CRGB::Black);
  }

  ledMode.presetStepSmall++;
  if (ledMode.presetStepSmall >= MATRIX_HEIGHT - ledMode.presetStep) {
    ledMode.presetStepSmall = 0;
    ledMode.presetStep++;
    if (ledMode.presetStep >= MATRIX_HEIGHT) {
      ledMode.presetStep = 0;
    }
  }
}

struct FlagStrip {
  CRGB color;
  uint8_t height;
};
static FlagStrip flagBL[] = {{CRGB::White, 7}, {CRGB::Red, 5}, {CRGB::White, 4}};
static FlagStrip flagNL[] = {{CRGB::Red, 6}, {CRGB::White, 6}, {CRGB::Blue, 4}};
static FlagStrip flagUA[] = {{CRGB::Blue, 10}, {0xFFAA00, 6}};
static FlagStrip flagSP[] = {{CRGB::Red, 7}, {0xFFAA00, 5}, {CRGB::Red, 4}};
FlagStrip *getCurrentFlag() {
  if (ledMode.presetMode == PRESET_MODE_FLAG_BL) {
    return flagBL;
  }
  if (ledMode.presetMode == PRESET_MODE_FLAG_NL) {
    return flagNL;
  }
  if (ledMode.presetMode == PRESET_MODE_FLAG_UA) {
    return flagUA;
  }
  if (ledMode.presetMode == PRESET_MODE_FLAG_SP) {
    return flagSP;
  }
}
uint8_t getCurrentFlagLen() {
  if (ledMode.presetMode == PRESET_MODE_FLAG_BL) {
    return sizeof(flagBL) / sizeof(flagBL[0]);
  }
  if (ledMode.presetMode == PRESET_MODE_FLAG_NL) {
    return sizeof(flagNL) / sizeof(flagNL[0]);
  }
  if (ledMode.presetMode == PRESET_MODE_FLAG_UA) {
    return sizeof(flagUA) / sizeof(flagUA[0]);
  }
  if (ledMode.presetMode == PRESET_MODE_FLAG_SP) {
    return sizeof(flagSP) / sizeof(flagSP[0]);
  }
}

void ledPresetFlagWaveSetup() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FlagStrip *flag = getCurrentFlag();
  uint8_t flagLen = getCurrentFlagLen();
  uint8_t toZ = MATRIX_HEIGHT - 1;
  for (uint8_t i = 0; i < flagLen; i++) {
    ledSetCell({0, 0, (uint8_t)(toZ - flag[i].height), MATRIX_SIZE, MATRIX_SIZE, toZ}, flag[i].color);
    toZ -= flag[i].height - 1;
  }
}
void ledPresetFlagWaveLoop() {
  FlagStrip *flag = getCurrentFlag();
  uint8_t flagLen = getCurrentFlagLen();
  uint8_t toZ = 0;
  for (uint8_t stripN = 0; stripN < flagLen - 1; stripN++) {
    toZ += flag[stripN].height;
    for (uint8_t i = 0; i < MATRIX_SIZE / 2; i++) {
      uint8_t step = (i + ledMode.presetStep) % MATRIX_SIZE;
      CRGB topColor = step != 0 ? flag[stripN + 1].color : flag[stripN].color;
      CRGB bottomColor = step == 2 ? flag[stripN + 1].color : flag[stripN].color;
      uint8_t z = MATRIX_HEIGHT - toZ + 1;
      ledSetCell({(uint8_t)(2 * i), 0, z, (uint8_t)(2 * i + 1), MATRIX_SIZE, z}, topColor);
    }
  }
  incPresetStep(MATRIX_SIZE);
}

#define P_FLAG_SIREN_STEPS 16
#define P_FLAG_SIREN_START_ANGLE 5
#define P_FLAG_SIREN_STEP_ANGLE 128 / P_FLAG_SIREN_STEPS
void ledPresetFlagSirenSetup() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FlagStrip *flag = getCurrentFlag();
  uint8_t flagLen = getCurrentFlagLen();
  if (flagLen == 3 && flag[0].color == flag[2].color) {
    fill_solid(leds, NUM_LEDS, flag[0].color);
  }
}
void ledPresetFlagSirenLoop() {
  FlagStrip *flag = getCurrentFlag();
  uint8_t flagLen = getCurrentFlagLen();
  uint8_t flagWidth = 128 / flagLen;
  for (uint8_t i = 0; i < flagLen; i++) {
    uint8_t fromAngle = P_FLAG_SIREN_START_ANGLE + P_FLAG_SIREN_STEP_ANGLE * ledMode.presetStep + i * flagWidth;
    uint8_t toAngle = fromAngle + flagWidth;
    ledSetCell(fromAngle, toAngle, flag[i].color);
    ledSetCell(fromAngle + 128, toAngle + 128, flag[i].color);
  }
  incPresetStep(P_FLAG_SIREN_STEPS);
}

uint8_t prevR = 0;
uint8_t prevG = 0;
uint8_t prevB = 0;
#define SOUND_FADE 50
#define SOUND_FADE_MIN 50
void setPrevSoundLevels(uint8_t fadeStep, uint8_t minFade) {
  if (prevR < soundLevels[0]) {
    prevR = soundLevels[0];
  } else if (prevR > fadeStep + minFade) {
    prevR -= fadeStep;
  } else {
    prevR = minFade;
  }
  if (prevG < soundLevels[1]) {
    prevG = soundLevels[1];
  } else if (prevG > fadeStep + minFade) {
    prevG -= fadeStep;
  } else {
    prevG = minFade;
  }
  if (prevB < soundLevels[2]) {
    prevB = soundLevels[2];
  } else if (prevB > fadeStep + minFade) {
    prevB -= fadeStep;
  } else {
    prevB = minFade;
  }
}
void ledPresetSoundLoopRGB() {
  setPrevSoundLevels(SOUND_FADE, SOUND_FADE_MIN);
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = i % 3;
    leds[i] = CRGB(x == 0 ? prevR : 0, x == 1 ? prevG : 0, x == 2 ? prevB : 0);
  }
}

#define SOUND_SPARKS_FACTOR 5
void ledPresetSoundLoopWhite() {
  setPrevSoundLevels(SOUND_FADE, 0);
  uint16_t level = (prevR + prevG + prevB) / 3.0 / 255.0 * NUM_LEDS;
  uint16_t levelFactor = 255.0 / ((prevR + prevG + prevB) / 3.0);
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    if (i % levelFactor == 0) {
      leds[i] = WARM_WHITE_BRIGHT_COLOR;
    } else {
      leds[i] = WARM_WHITE_COLOR;
    }
  }
  return;
}

#define SOUND_ROUND_START_ANGLE 0
void ledPresetSoundLoopRound() {
  CRGB wwB = WARM_WHITE_BRIGHT_COLOR;
  CRGB wwD = WARM_WHITE_DARK_COLOR;
  uint8_t level = (prevR + prevG + prevB) / 3.0;
  CRGB baseColor = CRGB(
    wwB.red + (wwB.red - wwD.red) / 255.0 * level,
    wwB.green + (wwB.green - wwD.green) / 255.0 * level,
    wwB.blue + (wwB.blue - wwD.blue) / 255.0 * level
  );
  fill_solid(leds, NUM_LEDS, baseColor);
  ledSetCell(SOUND_ROUND_START_ANGLE, prevB, CRGB::Blue);
  ledSetCell(255 - SOUND_ROUND_START_ANGLE - prevR, 255 - SOUND_ROUND_START_ANGLE, CRGB::Red);
}

void ledPresetSoundLoop() {
  switch (ledMode.presetMode) {
    case PRESET_MODE_SOUND_RGB:
      ledPresetSoundLoopRGB();
      break;
    case PRESET_MODE_SOUND_WHITE:
      ledPresetSoundLoopWhite();
      break;
    case PRESET_MODE_SOUND_ROUND:
      ledPresetSoundLoopRound();
      break;
    default:
      break;
  }
}

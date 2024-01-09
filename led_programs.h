#ifndef NYT_LED_PROGRAMS_h
#define NYT_LED_PROGRAMS_h

#define SHOW_CMD 0x80
#define OFF_CELL 0x00000000

#define CMD_FROM_X 0x70
#define CMD_TO_X 0x07
#define CMD_FROM_Y 0x70
#define CMD_TO_Y 0x07
#define CMD_FROM_Z 0xf0
#define CMD_TO_Z 0x0f
#define CMD_SHOW 0x80
#define CMD_R 0xf000
#define CMD_G 0x0f00
#define CMD_B 0x000f

#define PRESET_SOLID 1
#define PRESET_SPARK 2
#define PRESET_RAINBOW 3
#define PRESET_COLLECT 4
#define PRESET_FLAG_WAVE 5
#define PRESET_FLAG_SIREN 6
#define PRESET_SOUND 7

#define PRESET_MODE_SPARK_COLOR 1
#define PRESET_MODE_SPARK_WARM_INVERSE 2
#define PRESET_MODE_SPARK_WARM 3
#define PRESET_MODE_SPARK_WHITE_INVERSE 4
#define PRESET_MODE_SPARK_WHITE 5

#define PRESET_MODE_COLLECT_CLEAR 1
#define PRESET_MODE_COLLECT_FULL 2

#define PRESET_MODE_FLAG_BL 1
#define PRESET_MODE_FLAG_NL 2
#define PRESET_MODE_FLAG_UA 3
#define PRESET_MODE_FLAG_SP 4

#define PRESET_MODE_SOUND_RGB 1
#define PRESET_MODE_SOUND_WHITE 2
#define PRESET_MODE_SOUND_ROUND 3

struct LedPresetElement {
  uint8_t id;
  uint8_t modeLen;
  uint8_t defaultMode;
};

static LedPresetElement ledPresetList[] = {
  {PRESET_SOLID, 1, 0},
  {PRESET_SPARK, 5, PRESET_MODE_SPARK_WARM_INVERSE},
  {PRESET_RAINBOW, 1, 0},
  {PRESET_COLLECT, 2, PRESET_MODE_COLLECT_FULL},
  {PRESET_FLAG_WAVE, 4, PRESET_MODE_FLAG_BL},
  {PRESET_FLAG_SIREN, 4, PRESET_MODE_FLAG_BL},
  {PRESET_SOUND, 2, PRESET_MODE_SOUND_WHITE}
};
#define LED_PRESETS_LEN sizeof(ledPresetList) / sizeof(ledPresetList[0])

void ledPresetSparkLoop();

#include <stdint.h>

struct ledCommand {
	uint8_t x; // 0b 0xxx0xxx, 0b c???????, c - command, 1 = show
	uint8_t y; // 0b 0yyy0yyy
	uint8_t z; // 0b zzzzzzzz
	uint16_t color; // 0b rrrrgggg 0000bbbb
};

static ledCommand testProgram[32] = {
	{0x00 | SHOW_CMD, 0x03, 0x07, 0x77000000},
	{0x11, 0x03, 0x07, 0x77000000}, {0x00 | SHOW_CMD, 0x03, 0x07, OFF_CELL},
	{0x22, 0x03, 0x07, 0x77000000}, {0x11 | SHOW_CMD, 0x03, 0x07, OFF_CELL},
	{0x33, 0x03, 0x07, 0x77000000}, {0x22 | SHOW_CMD, 0x03, 0x07, OFF_CELL},
	{0x33 | SHOW_CMD, 0x03, 0x07, OFF_CELL},

	{0x03 | SHOW_CMD, 0x00, 0x07, 0x77000000},
	{0x03, 0x11, 0x07, 0x77000000}, {0x03 | SHOW_CMD, 0x00, 0x07, OFF_CELL},
	{0x03, 0x22, 0x07, 0x77000000}, {0x03 | SHOW_CMD, 0x11, 0x07, OFF_CELL},
	{0x03, 0x33, 0x07, 0x77000000}, {0x03 | SHOW_CMD, 0x22, 0x07, OFF_CELL},
	{0x03 | SHOW_CMD, 0x33, 0x07, OFF_CELL},

	{0x03 | SHOW_CMD, 0x03, 0x00, 0x77000000},
	{0x03, 0x03, 0x11, 0x77000000}, {0x03 | SHOW_CMD, 0x03, 0x00, OFF_CELL},
	{0x03, 0x03, 0x22, 0x77000000}, {0x03 | SHOW_CMD, 0x03, 0x11, OFF_CELL},
	{0x03, 0x03, 0x33, 0x77000000}, {0x03 | SHOW_CMD, 0x03, 0x22, OFF_CELL},
	{0x03, 0x03, 0x44, 0x77000000}, {0x03 | SHOW_CMD, 0x03, 0x33, OFF_CELL},
	{0x03, 0x03, 0x55, 0x77000000}, {0x03 | SHOW_CMD, 0x03, 0x44, OFF_CELL},
	{0x03, 0x03, 0x66, 0x77000000}, {0x03 | SHOW_CMD, 0x03, 0x55, OFF_CELL},
	{0x03, 0x03, 0x77, 0x77000000}, {0x03 | SHOW_CMD, 0x03, 0x66, OFF_CELL},
	{0x03 | SHOW_CMD, 0x03, 0x77, OFF_CELL}
};

#endif

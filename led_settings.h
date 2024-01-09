#ifndef NYT_LED_SETTINGS_h
#define NYT_LED_SETTINGS_h

#include <FastLED.h>

#define LED_CORRECTION 0xFF8A50
#define LED_CORRECTION_MODE 0

#define COLOR_ORDER RGB // first strip - GRB
#define LED_TYPE WS2812
#define NUM_LEDS 500
#define LED_PIN 6
#define FPS 50

#define BRIGHTNESS_STEP 30
#define BRIGHTNESS_MIN 70
#define DEFAULT_BRIGHTNESS 100
#define DEFAULT_SPEED 5
#define DEFAULT_SHUFFLE true

#define TREE_RATIO 2
#define MATRIX_SIZE 8
#define MATRIX_HEIGHT TREE_RATIO * MATRIX_SIZE

#define BIG_STEP_DELAY 1000 * 60 * 2 // 2 min

#endif


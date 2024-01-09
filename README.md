# XMAS-tree

This sketch is designed to make a 3d lights for xmas tree.

## Hardware
1. board: Arduino Uno Rev4 WiFi
1. leds: 500 WS2812 with RGB color order
1. microphone: MAX9814
1. ir receiver: KY-022

## WiFi
If you have a wifi on board then create `secret.h` with `secret.h.example` as a reference, else, set `IS_WIFI_ON` to `0`. Also, it is good idea to turn off the wifi during debugging as long it takes a lot of time on startup.

## Leds
I've used some random WS2812 led strings. I could say that all of led strips are different and parameters have to be adjusted in `led_settings.h`. Also, it is good idea to set right color correction for leds. To do so, set `LED_CORRECTION_MODE` to `1` and set good looking white color (check `irCorrection()`).

### 3d leds
To place leds onto right position in 3d, update `led_matrix.hpp` data from [xmas-tree-calibration](https://github.com/rogozhin/xmas-tree-calibration).

## Microphone
If do not have it or do not want to use it, set
`IS_SOUND_ON` to `0`.

## IR
I believe, any receiver will be good, just map buttons.

#include "sound.h"

#include <arduinoFFT.h>

#define MIC_PIN A0

#define SAMPLE_IN_ONE_LOOP 1
#define INTENSIFY 1
#define SAMPLES 128 // Must be a power of 2
#define SAMPLING_FREQUENCY 5000 // Hz, must be less than 10000 due to ADC
#define MAX_INTENSITY 500

#define RANGE_NUM 3

uint16_t ranges[RANGE_NUM] = {250, 750, SAMPLING_FREQUENCY / 2};

bool isSoundOn = false;

#if defined(SAMPLE_IN_ONE_LOOP) && (SAMPLE_IN_ONE_LOOP==1)
  unsigned long microseconds;
  unsigned int sampling_period_us;
#endif

double modules[RANGE_NUM] = {};
void (*getSoundHandler)(uint8_t *vectors);

double vReal[SAMPLES];
double vImag[SAMPLES];
arduinoFFT FFT = arduinoFFT(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

#if !defined(SAMPLE_IN_ONE_LOOP) || (SAMPLE_IN_ONE_LOOP==0)
  uint8_t sampleIndex = 0;
#endif

#if defined(INTENSIFY) && (INTENSIFY==1)
  #define INTENSE_FACTOR 0.8
  void intensify() {
    double max = modules[0];
    uint8_t maxIndex = 0;
    for (uint8_t i = 1; i < RANGE_NUM; i++) {
      if (modules[i] > max) {
        max = modules[i];
        maxIndex = i;
      }
    }
    for (uint8_t i = 0; i < RANGE_NUM; i++) {
      modules[i] *= 1 + (i == maxIndex ? INTENSE_FACTOR : -INTENSE_FACTOR);
    }
  }
#endif
uint8_t normalize(double b) {
  double c = b / MAX_INTENSITY;
  if (c < 0.2) {
    c = 0.00;
  } else if (c > 1) {
    c = 1.00;
  }
  return 255 * c;
}

#define GET_FREQ(_i) ((_i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES)
uint8_t getRange(uint8_t i) {
  double freq = GET_FREQ(i);
  for (uint8_t j = 0; j < RANGE_NUM; j++) {
    if (freq <= ranges[j]) {
      return j;
    }
  }
  return RANGE_NUM - 1;
}

void compute() {
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();

  for (uint8_t i = 0; i < RANGE_NUM; i++) {
    modules[i] = 0;
  }

  #define SOUND_CUT_LOW 2
  #define SOUND_CUT_THRESHOLD 100
  for (int i = SOUND_CUT_LOW; i < SAMPLES / 2; i++) {
    if (vReal[i] > SOUND_CUT_THRESHOLD) {
      uint8_t range = getRange(i);
      modules[range] += vReal[i];
    }
  }

  uint8_t result[RANGE_NUM + 1] = {RANGE_NUM};
  for (uint8_t i = 0; i < RANGE_NUM; i++) {
    modules[i] /= ((SAMPLES / 2) / RANGE_NUM);
    result[i + 1] = normalize(modules[i]);
  }

  #if defined(INTENSIFY) && (INTENSIFY==1)
    intensify();
  #endif
  getSoundHandler(result);
}

void setSoundStatus(bool status) {
  isSoundOn = status;
}

void soundSetup(void (*getSoundHandlerFunc)(uint8_t *vectors)) {
  getSoundHandler = getSoundHandlerFunc;
  #if defined(SAMPLE_IN_ONE_LOOP) && (SAMPLE_IN_ONE_LOOP==1)
    sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
  #endif
  pinMode(MIC_PIN, INPUT);
}

void soundLoop() {
  if (!isSoundOn) {
    return;
  }
  #if defined(SAMPLE_IN_ONE_LOOP) && (SAMPLE_IN_ONE_LOOP==1)
    microseconds = micros();
    for(int i = 0; i < SAMPLES; i++) {
        vReal[i] = analogRead(MIC_PIN);
        vImag[i] = 0;
        while(micros() - microseconds < sampling_period_us);
        microseconds += sampling_period_us;
    }
  #else
    if (sampleIndex < SAMPLES) {
      vReal[sampleIndex] = analogRead(MIC_PIN);
      vImag[sampleIndex] = 0;
      sampleIndex++;
      return;
    }
    sampleIndex = 0;
  #endif

  compute();
}

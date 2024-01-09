#include <Arduino.h>
#include "ir.h"
#include <IRremote.hpp>

#define DECODE_HASH
#define IR_DECODE_GAP 250

unsigned long lastIrFrame = millis();

void (*irCallback)(uint16_t address, uint16_t command, bool repeat);

void getIrSignal() {
  if (IrReceiver.decode()) {
    if (millis() - lastIrFrame > IR_DECODE_GAP) {
      irCallback(IrReceiver.decodedIRData.address, IrReceiver.decodedIRData.command, IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT ? true : false);
      lastIrFrame = millis();
    }
    IrReceiver.resume();
  }
}

void irSetup(void (*irCallbackFunc)(uint16_t address, uint16_t command, bool repeat)) {
  irCallback = irCallbackFunc;
  IrReceiver.begin(IR_RECV_PIN);
}
void irLoop() {
  getIrSignal();
}

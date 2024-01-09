#ifndef NYT_IR_h
#define NYT_IR_h

#define IR_RECV_PIN 10

void irSetup(void (*irCallbackFunc)(uint16_t address, uint16_t command, bool repeat));
void irLoop();

#endif

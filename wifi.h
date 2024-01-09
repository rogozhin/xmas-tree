#ifndef NYT_WIFI_h
#define NYT_WIFI_h

#include <Arduino.h>
#include "WiFiS3.h"
#include "secret.h"

void wifiSetup(void (*getCommandHandlerFunc)(String getHeader));
void wifiLoop();

#endif

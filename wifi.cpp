#include "wifi.h"
#include "WiFiS3.h"
#include "secret.h"
#include "led.h"

#define FPS 40
#define FRAME_DELAY 1000 / FPS
uint32_t wifiPrevFrame = 0;

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;
int status = WL_IDLE_STATUS;

void (*getCommandHandler)(String getHeader);

WiFiServer server(80);

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void wifiSetup(void (*getCommandHandlerFunc)(String getHeader)) {
  getCommandHandler = getCommandHandlerFunc;

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

    delay(5000);
  }
  server.begin();
  printWifiStatus();
}

void wifiLoop() {
  uint32_t currentTime = millis();
  if (wifiPrevFrame + FRAME_DELAY > currentTime) {
    return;
  }
  wifiPrevFrame = currentTime;
  bool sendStatus = false;

  WiFiClient client = server.available();
  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            if (sendStatus) {
              LedMode mode = ledGetMode();
              client.println("Content-Type: application/json");
              client.println("Connection: close");
              client.println("Access-Control-Allow-Origin: *");
              // client.println("Content-Length: 1000");
              client.println();
              client.print("{\"on\":"); client.print(mode.isOn ? "1" : "0"); client.print(",");
                client.print("\"brightness\":"); client.print(mode.brightness); client.print(",");
                client.print("\"speed\":"); client.print(mode.speed); client.print(",");
                client.print("\"mode\":"); client.print(mode.mode); client.print(",");
                client.print("\"preset\":"); client.print(mode.preset); client.print(",");
                client.print("\"presetMode\":"); client.print(mode.presetMode); client.print(",");
                client.print("\"presetColor\":{");
                  client.print("\"red\":"); client.print(mode.presetColor.red); client.print(",");
                  client.print("\"green\":"); client.print(mode.presetColor.green); client.print(",");
                  client.print("\"blue\":"); client.print(mode.presetColor.blue); client.print("},");
                client.print("\"shuffle\":"); client.print(mode.shuffle ? "1" : "0");
                client.println("}");
              client.flush();
            } else {
              client.println("Content-Type: text/text");
              client.println("Connection: close");
              client.println();
              client.println("ok");
            }
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        } else {
          if (currentLine.startsWith("GET /status")) {
            sendStatus = true;
          } else if (currentLine.startsWith("GET /")) {
            getCommandHandler(currentLine + "&");
          }
        }
      }
    }
    delay(1);
    client.stop();
  }
}

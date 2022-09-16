// Debug:
#ifdef DEBUG_ESP_PORT
#define DEBUG_MSG(...) DEBUG_ESP_PORT.printf(__VA_ARGS__)
#else
#define DEBUG_MSG(...)
#endif

// Modules:
#include "./PIPEInstance.h"
#include "./initWifi.h"
#include "./flash.h"
#include "./Request.h"
#include "./settings.h"

// Millis()
const int period = 10000;
unsigned long time_now = 0;

const char *ssid1 = WIFI_SSID;
const char *password1 = WIFI_PASSWORD;

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.print("\n\n\n\nF/setup: Started version ");
  Serial.println(VERSION);
  PIPEInstance.setUp();
  PIPEInstance.update();

  initWifi();
  getPipe();
  postPipe();
}

void loop()
{
  PIPEInstance.debug();
  delay(1000);
  // time_now = millis();
  //  while (millis() < time_now + period);
  //  Serial.println("\n\nF/loop: New period");
  //  getPipe();
  //  postPipe();
}

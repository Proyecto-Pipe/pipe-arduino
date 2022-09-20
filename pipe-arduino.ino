// Debug:
#ifdef DEBUG_ESP_PORT
#define DEBUG_MSG(...) DEBUG_ESP_PORT.printf(__VA_ARGS__)
#else
#define DEBUG_MSG(...)
#endif

// Dependencies:
#include <DHT.h>

// Modules:
#include "./PIPEInstance.h"
#include "./initWifi.h"
#include "./flash.h"
#include "./Request.h"
#include "./settings.h"

// Millis()
const int period = 10000;
unsigned long time_now = 0;

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.print("\n\n\n\nF/setup: Started version ");
  Serial.println(VERSION);

  DHT localDhtSensor(DHT_PIN, DHT_TYPE);
  DHT* dhtSensorPtr = &localDhtSensor;
  dhtSensorPtr->begin();

  PIPEInstance.setUp(dhtSensorPtr);
  PIPEInstance.update();

  // initWifi();
  // getPipe();
  // postPipe();
}

void loop()
{
  PIPEInstance.onFan();
  delay(4000);
  PIPEInstance.offFan();
  delay(10000);
  // time_now = millis();
  //  while (millis() < time_now + period);
  //  Serial.println("\n\nF/loop: New period");
  //  getPipe();
  //  postPipe();
}

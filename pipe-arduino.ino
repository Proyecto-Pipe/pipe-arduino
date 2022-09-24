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
#include "./Screen.h"
#include "./settings.h"

// Millis()
const int period = 10000;
unsigned long time_now = 0;

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.print("\n\n\n\nF/setup: Started version ");
  Serial.println(VERSION);

  Screen::setUp();

  DHT localDhtSensor(DHT_PIN, DHT_TYPE);
  localDhtSensor.begin();
  DHT* dhtSensorPtr = &localDhtSensor;
  Serial.println(localDhtSensor.readHumidity());
  Serial.println(dhtSensorPtr->readHumidity());
  PIPEInstance.setUp(dhtSensorPtr);
//  PIPEInstance.update();

//  while (true) {
//      Serial.println("Fafsa");
//      Serial.println(localDhtSensor.readHumidity());
//      Serial.println(dhtSensorPtr->readHumidity());
//      Serial.println(PIPEInstance._getAirHumidity());
//      delay(200);
//  }

  // initWifi();
  // getPipe();
  // postPipe();
}

void loop()
{
  delay(1000);
  // Serial.println(PIPEInstance._getAirHumidity());
  PIPEInstance.debug();

//  PIPEInstance.offFan();
//  delay(10000);
  // time_now = millis();
  //  while (millis() < time_now + period);
  //  Serial.println("\n\nF/loop: New period");
  //  getPipe();
  //  postPipe();
}

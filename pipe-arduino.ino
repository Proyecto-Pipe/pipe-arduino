// Debug:
#ifdef DEBUG_ESP_PORT
#define DEBUG_MSG(...) DEBUG_ESP_PORT.printf(__VA_ARGS__)
#else
#define DEBUG_MSG(...)
#endif

// Dependencies:
#include <DHT.h>
#include <WiFiClientSecureBearSSL.h>

// Modules:
#include "./PIPEInstance.h"
#include "./initWifi.h"
#include "./flash.h"
#include "./Request.h"
#include "./Screen.h"
#include "./settings.h"

// Millis()
unsigned long time_now = 0;
DHT* dhtSensorPtr;
DHT localDhtSensor(DHT_PIN, DHT_TYPE);

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.print("\n\n\n\nF/setup: Started version ");
  Serial.println(VERSION);

  Screen::setUp();
  Screen::setUpMessage();
  delay(1000);

  localDhtSensor.begin();
  dhtSensorPtr = &localDhtSensor;
  PIPEInstance.setUp(dhtSensorPtr);
  PIPEInstance.update();

  initWifi();
  getPipe();
  postPipe();
}

void loop()
{
  // https://www.norwegiancreations.com/2017/09/arduino-tutorial-using-millis-instead-of-delay/
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  // Ignore SSL certificate validation
  client->setInsecure();
  if (millis() >= time_now + PERIOD_DURATION) {
    time_now += PERIOD_DURATION;
    Serial.println("\n\nF/loop: New period");
  if (wifiConnected() == false) {
    initWifi();
  }
  getPipe();
  postPipe();
  };
}

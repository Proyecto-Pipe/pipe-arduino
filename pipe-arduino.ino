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
unsigned long time_isclientonline = 0;
unsigned long time_pipenow = 0;
unsigned long time_records = 0;
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
  postPipe(false);
}

bool isClientOnline = false;
void loop()
{
  // https://www.norwegiancreations.com/2017/09/arduino-tutorial-using-millis-instead-of-delay/
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  // Ignore SSL certificate validation
  client->setInsecure();
  if (wifiConnected() == false) {
    initWifi();
  }
  if (millis() >= time_isclientonline + ISCLIENTONLINE_PERIOD) { // Clock for isclientonline
    time_isclientonline += ISCLIENTONLINE_PERIOD;
    Serial.println("\n\nF/loop: ISCLIENTONLINE_PERIOD");
    isClientOnline = checkIsClientOnline();
  };
  if (isClientOnline && millis() >= time_pipenow + PIPENOW_PERIOD) { // Clock for pipenow
    time_pipenow += PIPENOW_PERIOD;
    Serial.println("\n\nF/loop: PIPENOW_PERIOD");
    getPipe();
    postPipe(false);
  };
  if (millis() >= time_records + RECORD_PERIOD) { // Clock for records
    time_records += RECORD_PERIOD;
    Serial.println("\n\nF/loop: RECORD_PERIOD");
    getPipe();
    postPipe(true);
  };
}

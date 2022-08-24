// Modules:
//#include "./PIPEInstance.h"
//#include "./Wifi.h"
//#include "./flash.h"
#include "./settings.h"
#include <ESP8266WiFi.h>

// Millis()
const int period = 10000;
unsigned long time_now = 0;

const char *ssid1 = WIFI_SSID;
const char *password1 = WIFI_PASSWORD;

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("F/initWifi: Started");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid1, password1);
  Serial.print("F/initWifi: Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(1000);
  }
  Serial.print("\nF/initWifi: Connected to wifi: ");
  
  Serial.print("\n\n\n\nF/setup: Started version ");
  Serial.println(VERSION);

  // Flash:
//  flash(300, 1);

  // Pipe
//  initWifi();

  // postPipe();
  // getPipe();

//  PIPEInstance.activatePump();
//  pinMode(14, OUTPUT);
}

void loop()
{
//  PIPEInstance.onBulb();
//  delay(4000);
//  PIPEInstance.offBulb();
//  delay(4000);
  //  time_now = millis();
  //  while (millis() < time_now + period);
  //  Serial.println("\n\nF/loop: New period");
  // getPipe();
  // postPipe();
}

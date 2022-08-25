// Modules:
#include "./PIPEInstance.h"
#include "./Wifi.h"
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
  Serial.setTimeout(2000);
  delay(100);
  while(!Serial) { }
  Serial.print("\n\n\n\nF/setup: Started version ");
  Serial.println(VERSION);

  // Flash:
//  flash(300, 1);

  // Pipe
  initWifi();

  // postPipe();
    getPipe();

//  PIPEInstance.activatePump();
}

void loop()
{
  Serial.println("hola");
//  digitalWrite(D7, HIGH);
//  delay(500);
//  digitalWrite(D7, LOW);
//  delay(1500);
  PIPEInstance.onBulb();
  delay(4000);
  PIPEInstance.offBulb();
  delay(4000);
  //  time_now = millis();
  //  while (millis() < time_now + period);
  //  Serial.println("\n\nF/loop: New period");
//   getPipe();
  // postPipe();
}

// Modules:
#include "./PIPEInstance.h"
#include "./Wifi.h"
#include "./flash.h"
#include "./settings.h"

// Millis()
const int period = 10000;
unsigned long time_now = 0;

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.print("\n\n\n\nF/setup: Started version ");
  Serial.println(VERSION);

  // Flash:
  flash(300, 1);

  // Pipe
  initWifi();

  // postPipe();
  // getPipe();

  PIPEInstance.activatePump();
  pinMode(14, OUTPUT);
}

void loop()
{
  PIPEInstance.onBulb();
  delay(4000);
  PIPEInstance.offBulb();
  delay(4000);
  //  time_now = millis();
  //  while (millis() < time_now + period);
  //  Serial.println("\n\nF/loop: New period");
  // getPipe();
  // postPipe();
}

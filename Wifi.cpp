#include "Wifi.h"

#include <SPI.h>
#include <WiFi.h>
#include "./settings.h"

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

IPAddress ip;

void initWifi()
{
  Serial.println("F/initWifi: Started");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("F/initWifi: Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(1000);
  }
  Serial.print("\nF/initWifi: Connected to wifi: ");
  ip = WiFi.localIP();
  Serial.println(ip);
}

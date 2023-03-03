#include "./initWifi.h"
#include "./Screen.h"

#include <ESP8266WiFi.h>
#include "./settings.h"
#include "./env.h"

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

IPAddress ip;

void initWifi()
{
  int dots = 1;
  Serial.println("F/initWifi: Started");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("F/initWifi: Connecting to Wifi ..");
  while (WiFi.status() != WL_CONNECTED)
  {
    Screen::searchingWifiMessage(dots);
    Serial.print('.');
    dots < 4 ? dots += 1 : dots = 1;
    delay(1000);
  }
  
  Serial.print("\nF/initWifi: Connected to wifi: ");
  ip = WiFi.localIP();
  Serial.println(ip);
}

bool wifiConnected() {
   Serial.println("F/checkWifiConnected");
   if (WiFi.status() == WL_CONNECTION_LOST || WiFi.status() == WL_DISCONNECTED) {
     return false;
   } else {
     return true;
   }
}

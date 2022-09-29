#include "./request.h"
#include "./Screen.h"

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "./PIPEInstance.h"
#include "./settings.h"
#include "./env.h"

#include <ESP8266WiFi.h>
WiFiClient WifiClient;

void getPipe()
{
  Serial.println("F/getPipe: Started");
  Screen::requestMessage("GET", false);
  HTTPClient http;
  http.begin(WifiClient, URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("password", API_PASSWORD);
  http.addHeader("is-pipe", "true");
  int httpCode = http.GET();

  String payload = http.getString();
  Serial.print("F/getPipe: code ");
  Serial.print(httpCode);
  Serial.print("  payload: ");
  Serial.println(payload);

  DynamicJsonDocument jsonRes(BUFFER_SIZE);
  deserializeJson(jsonRes, payload);
  const int isBulbOn = int(jsonRes["isBulbOn"]);
  const int isFanOn = int(jsonRes["isFanOn"]);
  const int isPumpOn = int(jsonRes["isPumpOn"]);

  if (isBulbOn == 1)
  {
    PIPEInstance.onBulb();
  }
  else
  {
    PIPEInstance.offBulb();
  }
  if (isFanOn == 1)
  {
    PIPEInstance.onFan();
  } else {
    PIPEInstance.offFan();
  }
  if (isPumpOn == 1)
  {
    PIPEInstance.activatePump();
  }
  Screen::requestMessage("GET", true);
  http.end();
}

void postPipe()
{
  Screen::requestMessage("POST", false);
  Serial.println("F/postPipe: Started");
  PIPEInstance.update();

  char bodyBuffer[BUFFER_SIZE];
  char rawBody[] = "{\"airHumidity\": \"%f\", \"soilHumidity\": \"%f\", \"temperature\": \"%f\", \"light\": \"%f\"}";
  sprintf(bodyBuffer, rawBody, float(PIPEInstance.airHumidity), float(PIPEInstance.soilHumidity), float(PIPEInstance.temperature), float(PIPEInstance.light));
  Serial.println("F/postPipe: Body:");
  Serial.println(bodyBuffer);
  
  HTTPClient http;
  http.begin(WifiClient, URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("password", API_PASSWORD);
  http.addHeader("is-pipe", "true");
  int httpCode = http.POST(bodyBuffer);
  if (httpCode > 0)
  {
    String payload = http.getString();
    Serial.println("F/postPipe: response: " + payload);
  }
  else
  {
    Serial.println("F/postPipe: Error in http request");
    Serial.println(httpCode);
  }
  http.end();
  Screen::requestMessage("POST", true);
}

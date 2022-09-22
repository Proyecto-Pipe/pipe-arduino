#include "./request.h"

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "./PIPEInstance.h"
#include "./settings.h"

#include <ESP8266WiFi.h>
WiFiClient WifiClient;

void getPipe()
{
  Serial.println("F/getPipe: Started");
  HTTPClient http;
  http.begin(WifiClient, URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("password", API_PASSWORD);
  int httpCode = http.GET();

  if (true)
  {
    Serial.println(http.headers());
    for (int i = 0; i < http.headers(); i++)
    {
      Serial.print(http.headerName(i));
      Serial.print(": ");
      Serial.println(http.header(i));
    }
    String payload = http.getString();
    Serial.println(payload);
    Serial.println(httpCode);
    Serial.println("F/getPipe: payload: " + payload);

    DynamicJsonDocument jsonRes(BUFFER_SIZE);
    deserializeJson(jsonRes, payload);
    const int lastPipeConnection = int(jsonRes["lastPipeConnection"]);
    const int isBulbOn = int(jsonRes["isBulbOn"]);
    const int isPumpOn = int(jsonRes["isPumpOn"]);

    Serial.println(lastPipeConnection);
    Serial.println(isBulbOn);
    Serial.println(isPumpOn);

    if (isBulbOn == 1)
    {
      PIPEInstance.onBulb();
    }
    else
    {
      PIPEInstance.offBulb();
    }
    if (isPumpOn == 1)
    {
      PIPEInstance.activatePump();
    }
  }
  else
  {
    Serial.println("F/getPipe: Error in http request");
    Serial.println(httpCode);
  }
  http.end();
}

void postPipe()
{
  Serial.println("F/postPipe: Started");
  PIPEInstance.update();
  Serial.println(PIPEInstance.isPumpOn);
  Serial.println(PIPEInstance.light);
  Serial.println(PIPEInstance.airHumidity);

  char bodyBuffer[BUFFER_SIZE];
  char rawBody[] = "{\"airHumidity\": \"%f\", \"soilHumidity\": \"%f\", \"temperature\": \"%f\", \"light\": \"%f\", \"isBulbOn\": \"%d\", \"isFanOn\": \"%d\", \"isPumpOn\": \"%d\"}";
  sprintf(bodyBuffer, rawBody, float(PIPEInstance.airHumidity), float(PIPEInstance.soilHumidity), float(PIPEInstance.temperature), float(PIPEInstance.light), int(PIPEInstance.isBulbOn), int(PIPEInstance.isFanOn), int(PIPEInstance.isPumpOn));
  Serial.println("F/postPipe: Body:");
  Serial.println(bodyBuffer);

  HTTPClient http;
  http.begin(WifiClient, URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("password", API_PASSWORD);
  int httpCode = http.POST(bodyBuffer);
  if (httpCode > 0)
  {
    String payload = http.getString();
    Serial.println("F/postPipe: payload: " + payload);
  }
  else
  {
    Serial.println("F/postPipe: Error in http request");
    Serial.println(httpCode);
  }
  http.end();
}

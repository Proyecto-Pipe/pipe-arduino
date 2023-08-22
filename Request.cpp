#include "./request.h"
#include "./Screen.h"

#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include "./PIPEInstance.h"
#include "./settings.h"
#include "./env.h"
#include "./startAutomation.h"

#include <ESP8266WiFi.h>
WiFiClient WifiClient;

bool checkIsClientOnline()
{
  Serial.println("F/checkIsClientOnline: Started");
  Screen::requestMessage("GET", false);

  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  // Ignore SSL certificate validation
  client->setInsecure();

  HTTPClient http;
  http.begin(*client, ISCLIENTONLINE_URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("password", API_PASSWORD);
  http.addHeader("is-pipe", "true");
  int httpCode = http.GET();

  String payload = http.getString();
  Serial.print("F/getPipe: code ");
  Serial.println(http.headers());
  Serial.print(httpCode);
  Serial.print("  payload: ");
  Serial.println(payload);

  DynamicJsonDocument jsonRes(BUFFER_SIZE);
  deserializeJson(jsonRes, payload);

  const int isClientOnline = int(jsonRes["isClientOnline"]);
  Screen::requestMessage("GET", true);
  http.end();
  return isClientOnline;
}

void getPipe()
{
  Serial.println("F/getPipe: Started");
  Screen::requestMessage("GET", false);
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  // Ignore SSL certificate validation
  client->setInsecure();

  HTTPClient http;
  http.begin(*client, RECORDS_URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("password", API_PASSWORD);
  http.addHeader("is-pipe", "true");
  int httpCode = http.GET();

  String payload = http.getString();
  Serial.print("F/getPipe: code ");
  Serial.println(http.headers());
  Serial.print(httpCode);
  Serial.print("  payload: ");
  Serial.println(payload);

  DynamicJsonDocument jsonRes(BUFFER_SIZE);
  deserializeJson(jsonRes, payload);

  const int automation = int(jsonRes["automation"]);
  if (automation == 1) {
    startAutomation();
  } else {
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
      PIPEInstance.onPump();
    } else {
      PIPEInstance.offPump();
    } 
  }
  Screen::requestMessage("GET", true);
  http.end();
}

void postPipe(bool createRecord)
{
  Screen::requestMessage("POST", false);
  Serial.println("F/postPipe: Started");
  PIPEInstance.update();

  char bodyBuffer[BUFFER_SIZE];
  char rawBody[] = "{\"airHumidity\": \"%f\", \"soilHumidity\": \"%f\", \"temperature\": \"%f\", \"light\": \"%f\"}";
  sprintf(bodyBuffer, rawBody, float(PIPEInstance.airHumidity), float(PIPEInstance.soilHumidity), float(PIPEInstance.temperature), float(PIPEInstance.light));
  Serial.println("F/postPipe: Body:");
  Serial.println(bodyBuffer);
  
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  // Ignore SSL certificate validation
  client->setInsecure();

  HTTPClient http;
  if (createRecord) {
    http.begin(*client, RECORDS_URL);
  } else {
    http.begin(*client, PIPENOW_URL);
  }

  http.addHeader("Content-Type", "application/json");
  http.addHeader("password", API_PASSWORD);
  http.addHeader("is-pipe", "true");
  int httpCode = http.POST(bodyBuffer);
  if (httpCode > 0)
  {
    String payload = http.getString();
    Serial.print("F/postPipe: code ");
    Serial.println(httpCode);
    Serial.println("F/postPipe: response: " + payload);
    Serial.println(http.headers());
  }
  else
  {
    Serial.println("F/postPipe: Error in http request");
    Serial.println(httpCode);
    Serial.println(http.headers());
  }
  http.end();
  Screen::requestMessage("POST", true);
}

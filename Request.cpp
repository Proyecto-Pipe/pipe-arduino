#include "Request.h"

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "PIPEInstance.h"
#include "./flash.h"
#include "./settings.h"

void getPipe()
{
  flash(300, 2);
  Serial.println("F/getPipe: Started");
  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("password", API_PASSWORD);
  int httpCode = http.GET();

  if (true)
  {
    String payload = http.getString();
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
    flash(100, 5);
    Serial.println("F/getPipe: Error in http request");
    Serial.println(httpCode);
  }
  http.end();
}

void postPipe()
{
  flash(300, 2);
  Serial.println("F/postPipe: Started");
  Serial.println(PIPEInstance.isPumpOn);
  Serial.println(PIPEInstance.light);
  Serial.println(PIPEInstance.humidity);

  char bodyBuffer[BUFFER_SIZE];
  char rawBody[] = "{\"humidity\": \"%f\", \"temperature\": \"%f\", \"light\": \"%f\", \"isBulbOn\": \"%d\", \"isPumpOn\": \"%d\"}";
  sprintf(bodyBuffer, rawBody, float(PIPEInstance.humidity), float(PIPEInstance.temperature), float(PIPEInstance.light), int(PIPEInstance.isBulbOn), int(PIPEInstance.isPumpOn));
  Serial.println("F/postPipe: Body:");
  Serial.println(bodyBuffer);

  HTTPClient http;
  http.begin(URL);
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
    flash(100, 5);
    Serial.println("F/postPipe: Error in http request");
    Serial.println(httpCode);
  }
  http.end();
}

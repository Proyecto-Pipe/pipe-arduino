// Libraries:
#include <SPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Modules:
#include "./PIPE.h"

// Variables: =================
#define VERSION "1.0.3"

#define FLASH_GPIO_NUM 4

#define DHT_PIN 12
#define DHT_TYPE DHT11

#define BULB_PIN 15

#define PUMP_RELAY_PIN 13
#define PUMP_DURATION 2000

#define BUFFER_SIZE 174

char URL[] = "https://pipe-server.herokuapp.com/v1/pipe";
// char URL[] = "https://rickandmortyapi.com/api";
#define PORT 80                   // HTTPS port
#define API_PASSWORD "3124315814" // Api

#define WIFI_SSID "iPhone de ete sech"
#define WIFI_PASSWORD "memedona"

// Millis()
const int period = 10000;
unsigned long time_now = 0;

// Others
void flash(int time, int times)
{
  for (int i = 0; i < times; i++)
  {
    digitalWrite(FLASH_GPIO_NUM, HIGH);
    delay(time);
    digitalWrite(FLASH_GPIO_NUM, LOW);
    delay(time);
  }
};

// Pipe
PIPE PIPEInstance;

// Wifi
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

// Request
void getPipe()
{
  flash(300, 2);
  Serial.println("F/getPipe: Started");
  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("password", API_PASSWORD);
  int httpCode = http.GET();
  // if (httpCode > 0) {
  if (true)
  {
    String payload = http.getString();
    Serial.println("F/getPipe: payload: " + payload);

    DynamicJsonDocument jsonRes(BUFFER_SIZE);
    deserializeJson(jsonRes, payload);
    const int lastPipeConnection = int(jsonRes["lastPipeConnection"]);
    const int isBulbOn = int(jsonRes["isBulbOn"]);
    const int isPumpOn = int(jsonRes["isPumpOn"]);
    //    Serial.println("F/getPipe: Last Pipe connection: " + lastPipeConnection);
    //    Serial.println("F/getPipe: isBulbOn: " + isBulbOn);
    //    Serial.println("F/getPipe: isPumpOn: " + isPumpOn);

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

void setup()
{
  Serial.begin(9600);
  Serial.print("\n\n\n\nF/setup: Started version ");
  Serial.println(VERSION);

  // Flash:
  pinMode(FLASH_GPIO_NUM, OUTPUT);
  flash(300, 3);

  // Humidity:
  dht.begin();

  // Pump
  pinMode(PUMP_RELAY_PIN, OUTPUT);

  // Pipe
  PIPEInstance = PIPE();
  initWifi();

  // postPipe();
  // getPipe();

  PIPEInstance.activatePump();
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

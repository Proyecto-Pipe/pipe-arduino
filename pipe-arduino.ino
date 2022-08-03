// Libraries:
#include <SPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "DHT.h"

// Variables:
#define VERSION "1.0.3"

#define FLASH_GPIO_NUM 4

#define DHTPIN 12
#define DHTTYPE DHT11

#define PUMP_DURATION 6000

//char URL[] = "https://pipe-server.herokuapp.com/v1/pipe";
char URL[] = "https://rickandmortyapi.com/api";
#define PORT 80 // HTTPS port
#define API_PASSWORD "3124315814" // Api

#define WIFI_SSID "iPhone de ete sech"
#define WIFI_PASSWORD "memedona"

// Millis()
const int period = 10000;
unsigned long time_now = 0;

// Others
void flash(int time, int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(FLASH_GPIO_NUM, HIGH);
    delay(time);
    digitalWrite(FLASH_GPIO_NUM, LOW);
    delay(time); 
  }
};

DHT dht(DHTPIN, DHTTYPE);

// Pipe
class Pipe1
{
public:
  float humidity;
  float temperature;
  float light;
  int isBulbOn;
  int isPumpOn;

  Pipe1()
  {
    Serial.println("C/Pipe: Started");
    updatePipe();
    isBulbOn = 0;
    isPumpOn = 20;
  }

  void onBulb()
  {
    Serial.println("C/Pipe: onBulb");
    isBulbOn = 1;
    _onBulb();
  }
  void offBulb()
  {
    Serial.println("C/Pipe: offBulb");
    isBulbOn = 0;
    _offBulb();
  }
  void activatePump()
  {
    Serial.println("C/Pipe: activatePump");
    isPumpOn = 1;
    _onPump();
    delay(PUMP_DURATION);
    _offPump();
    isPumpOn = 0;
  }

private:
  void updatePipe()
  {
    Serial.println("C/Pipe: private: updatePipe");
    humidity = getCurrentHumidity();
    temperature = getCurrentTemperature();
    light = getCurrentLight();
  }

  float getCurrentHumidity()
  {
    return dht.readHumidity();
  }

  float getCurrentTemperature()
  {
    return dht.readTemperature();
  }

  float getCurrentLight()
  {
    return 13.0;
  }

  void _setUpLight() {
    
  }

  void _onBulb() {
    
  }

  void _offBulb() {
    
  }

  void _setUpBulb() {
    
  }

  void _onPump() {
    
  }

  void _offPump() {
    
  }

  void _setUpPump() {
    
  }
};

Pipe1 pipe1;

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
  if (true) {
    String payload = http.getString();
    Serial.println("F/getPipe: payload: " + payload);
    
    DynamicJsonDocument jsonRes(1024);
    deserializeJson(jsonRes, payload);
    const int lastPipeConnection = jsonRes["lastPipeConnection"];
    const bool isBulbOn = jsonRes["isBulbOn"];
    const bool isPumpOn = jsonRes["isPumpOn"];
//    Serial.println("F/getPipe: Last Pipe connection: " + lastPipeConnection);
//    Serial.println("F/getPipe: isBulbOn: " + isBulbOn);
//    Serial.println("F/getPipe: isPumpOn: " + isPumpOn);

    Serial.println(lastPipeConnection);
    Serial.println(isBulbOn);
    Serial.println(isPumpOn);
  
    if (isBulbOn) {
      pipe1.onBulb();
    } else { 
      pipe1.offBulb();
    }
    if (isPumpOn) {
      pipe1.activatePump();
    }
  } else {
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
  Serial.println(pipe1.isPumpOn);
  Serial.println(pipe1.light);
  Serial.println(pipe1.humidity);

  char bodyBuffer[1024];
  char rawBody[] = "{\"humidity\": \"%f\", \"temperature\": \"%f\", \"light\": \"%f\", \"isBulbOn\": \"%d\", \"isPumpOn\": \"%d\"}";
  sprintf(bodyBuffer, rawBody, float(pipe1.humidity), float(pipe1.temperature), float(pipe1.light), int(pipe1.isBulbOn), int(pipe1.isPumpOn));
  Serial.println("F/postPipe: Body:");
  Serial.println(bodyBuffer);


  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("password", API_PASSWORD);
  int httpCode = http.POST(bodyBuffer); 
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println("F/postPipe: payload: " + payload);
  } else {
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
  flash(1000, 1);

  // Humidity:
  dht.begin();

  pipe1 = Pipe1();
  initWifi();

  // postPipe();
  getPipe();
}

void loop()
{
  time_now = millis();
  while (millis() < time_now + period);
  Serial.println("F/loop: New period");
}

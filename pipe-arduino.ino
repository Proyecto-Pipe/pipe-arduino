// Libraries:
#include <SPI.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Variables:
#define VERSION "1.0.3"

char URL[] = "https://pipe-server.herokuapp.com/v1/pipe";
#define PORT 80 // HTTPS port
#define API_PASSWORD "3124315814" // Api

#define CONTENTTYPE "application/json"
#define FINGERPRINT "DC 78 3C 09 3A 78 E3 A0 BA A9 C5 4F 7A A0 87 6F 89 01 71 4C"

#define WIFI_SSID "iPhone de ete sech"
#define WIFI_PASSWORD "memedona"

// Millis()
const int period = 10000;
unsigned long time_now = 0;

// Pipe
class Pipe
{
public:
  int humidity;
  int temperature;
  int light;
  bool isBulbOn;
  bool isPumpOn;

  Pipe()
  {
    Serial.println("C/Pipe: Started");
    updatePipe();
    isBulbOn = false;
    isPumpOn = false;
  }

  void onBulb()
  {
    Serial.println("C/Pipe: onBulb");
    isBulbOn = true;
  }
  void offBulb()
  {
    Serial.println("C/Pipe: offBulb");
    isBulbOn = false;
  }
  void onPump()
  {
    Serial.println("C/Pipe: onPump");
    isPumpOn = true;
  }
  void offPump()
  {
    Serial.println("C/Pipe: offPump");
    isPumpOn = false;
  }

private:
  void updatePipe()
  {
    Serial.println("C/Pipe: updatePipe");
    humidity = getCurrentHumidity();
    temperature = getCurrentTemperature();
    light = getCurrentLight();
  }

  int getCurrentHumidity()
  {
    return 0;
  }

  int getCurrentTemperature()
  {
    return 0;
  }

  int getCurrentLight()
  {
    return 0;
  }
};

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
  Serial.println("F/getPipe: Started");
  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("password", API_PASSWORD);
  int httpCode = http.GET(); 
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println("F/getPipe: payload: " + payload);
    
  } else {
    Serial.println("F/getPipe: Error in http request");
  }
  http.end();
}

void postPipe(Pipe pipe)
{
  Serial.println("F/postPipe: Started");
  char rawBody[] = "{\"humidity\": \"%d\", \"temperature\": \"%d\", \"light\": \"%d\", \"isBulbOn\": \"%d\", \"isPumpOn\": \"%d\"}";
  char bodyBuffer[100];
  sprintf(bodyBuffer, rawBody, pipe.humidity, pipe.temperature, pipe.light, pipe.isBulbOn, pipe.isPumpOn);
  Serial.println("F/postPipe: Body: " + String(bodyBuffer));
  
  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("password", API_PASSWORD);
  int httpCode = http.POST(bodyBuffer); 
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println("F/postPipe: payload: " + payload);
    
  } else {
    Serial.println("F/postPipe: Error in http request");
  }
  http.end();
}

void setup()
{
  Serial.begin(9600);
  Serial.print("\nF/setup: Started version ");
  Serial.println(VERSION);

  Pipe pipe = Pipe();
  initWifi();

  postPipe(pipe);
  getPipe();
}

void loop()
{
  time_now = millis();
  while (millis() < time_now + period);
  Serial.println("F/loop: New period");
}

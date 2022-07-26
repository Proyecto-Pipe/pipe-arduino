// Libraries:
#include <SPI.h>
#include <WiFi.h>

// Variables:
#define VERSION "1.0.3"

//#define URL "https://pipe-server.herokuapp.com"
//#define PATH "/v1/pipe"
const char URL[] = "https://rickandmortyapi.com";
const char PATH[] = "/api";
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
void setHeaders(WiFiClient client, String httpMethod)
{
  Serial.println("F/setHeaders: Setting Headers");
  client.println(httpMethod + " " + String(PATH) + " HTTP/1.1");
  client.println("Host: " + String(URL));
  client.println("Content-Type: application/json");
  client.println("password: " + String(API_PASSWORD));
  client.println("Connection: keep-alive");
  client.println(); // end Header
}

void getPipe(WiFiClient client)
{
//  if(client.connect(URL, PORT)) {
  if(true) {
    Serial.println(client.connect(URL, PORT));
    Serial.println("F/getPipe: Connected to server: Setting Headers");
    setHeaders(client, "GET");
    Serial.println("F/getPipe: Connected to server: Setted Headers");
    Serial.println(client.available());
    while(client.available()) {
      Serial.print(client.read());
//      if(client.available()){
//        Serial.print(",");
//        Serial.print(client.read());
//      }
    }

    client.stop();
    Serial.println("\nF/getPipe: Disconnected from server");
  } else {
    Serial.println("F/getPipe: Can't connect to server");
  }
}

void postPipe(WiFiClient client, Pipe pipe)
{
  char rawBody[] = "{\"humidity\": \"%d\", \"temperature\": \"%d\", \"light\": \"%d\", \"isBulbOn\": \"%d\", \"isPumpOn\": \"%d\"}";
  char bodyBuffer[100];
  sprintf(bodyBuffer, rawBody, pipe.humidity, pipe.temperature, pipe.light, pipe.isBulbOn, pipe.isPumpOn);

  if(client.connect(URL, PORT)) {
    Serial.println("F/getPipe: Connecting to server: Setting Headers");
    setHeaders(client, "POST");
    Serial.println("F/getPipe: Connecting to server: Setted Headers");

    client.println(bodyBuffer);

    while(client.connected()) {
      if(client.available()){
        // GSAGSAGHASDHSA
        char c = client.read();
        Serial.print(c);
      }
    }
    
    client.stop();
    Serial.println("\nF/getPipe: Disconnected from server");
  } else {
    Serial.println("F/getPipe: Can't connect to server");
  }
}

void setup()
{
  Serial.begin(9600);
  Serial.print("\nF/setup: Started version ");
  Serial.println(VERSION);

  Pipe pipe();
  initWifi();
  
  WiFiClient wifiClient;
  getPipe(wifiClient);
}

void loop()
{
  time_now = millis();
  while (millis() < time_now + period);
  Serial.println("F/loop: New period");
}

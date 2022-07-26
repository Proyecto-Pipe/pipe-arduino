// Libraries:
#include <SPI.h>
#include <WiFi.h>
#include <Fetch.h>

// Variables:
#define VERSION "1.0.2"

#define URL "https://pipe-server.herokuapp.com"
#define PORT 443 // HTTPS port
#define PATH "/v1/pipe"
#define API_PASSWORD "3124315814" // Api

#define CONTENTTYPE "application/json"
#define BODY "{\"email\": \"test@test.com\", \"password\": \"test:80\"}"
#define FINGERPRINT "DC 78 3C 09 3A 78 E3 A0 BA A9 C5 4F 7A A0 87 6F 89 01 71 4C"

#define WIFI_SSID "iPhone de ete sech"
#define WIFI_PASSWORD "memedona"

// Millis()
int period = 10000;
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

void initWifi()
{
  Serial.println("F/initWifi: Started");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(1000);
  }
  Serial.print("F/initWifi: Connected to wifi: ");
  Serial.print(WiFi.localIP() + "\n");
}

// Wifi options
RequestOptions getGetOptions()
{
  Serial.println("F/getGetOptions: Started()");
  RequestOptions options;
  options.method = "GET";
  options.headers["Content-Type"] = "application/json";
  options.headers["Connection"] = "keep-alive";
  options.headers["password"] = API_PASSWORD;
  return options;
}

RequestOptions getPostOptions(Pipe pipe)
{
  Serial.println("F/getPostOptions: Started()");
  RequestOptions options;
  options.method = "POST";
  options.headers["Content-Type"] = "application/json";
  options.headers["Connection"] = "keep-alive";
  options.headers["password"] = API_PASSWORD;
  char rawBody[] = "{\"humidity\": \"%d\", \"temperature\": \"%d\", \"light\": \"%d\", \"isBulbOn\": \"%d\", \"isPumpOn\": \"%d\"}";
//  String body = "{\"humidity\": \"" + pipe.humidity + "\"" +
//                 ",\"temperature\": \"" + pipe.temperature + "\"" +
//                 ",\"light\": \"" + pipe.light + "\"" +
//                 ",\"isBulbOn\": \"" + pipe.isBulbOn + "\"" +
//                 ",\"isPumpOn\": \"" + pipe.isPumpOn + "\"" +
//                 "}";
//  body.toCharArray(bodyBuffer, 100);
  char bodyBuffer[100];
  sprintf(bodyBuffer, rawBody, pipe.humidity, pipe.temperature, pipe.light, pipe.isBulbOn, pipe.isPumpOn);
  options.body = bodyBuffer;
  Serial.println("F/getPostOptions: options.body: " + options.body);
  return options;
}

void setup()
{
  Pipe pipe();
  Serial.begin(9600);
  initWifi();
  Serial.print("\nF/setup: Started version ");
  Serial.println(VERSION);
  Response response = fetch(URL, getGetOptions());
  Serial.println(response);
}

void loop()
{
  time_now = millis();
  while (millis() < time_now + period)
  {
    Serial.println("F/loop: New period");
  }
}

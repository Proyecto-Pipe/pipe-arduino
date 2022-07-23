#include <SPI.h>
#include <WiFi.h>
#include <Fetch.h>

// HTTP REQUEST
#define URL "https://rickandmortyapi.com"
#define PORT 443 // HTTPS port
#define PATH "/api"
#define METHOD "GET"
#define CONTENTTYPE "application/json"
#define BODY "{\"email\": \"test@test.com\", \"password\": \"test:80\"}"
#define FINGERPRINT "DC 78 3C 09 3A 78 E3 A0 BA A9 C5 4F 7A A0 87 6F 89 01 71 4C"


const char* ssid = "iPhone de ete sech";
const char* password = "memedona";

void initWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

// RequestOptions
class RequestOptions {
    private:
    public:
        String method;
        Headers headers;
        Body body;
        #if defined(ESP8266)
        String fingerprint;
        #endif
        String caCert;
        RequestOptions();
};

// Pipe
class Pipe
{
public:
    int humidity;
    int temperature;
    int light;

    // bool isBulbOn;
    // int lastPumpDate[5];

    Pipe()
    {
        Serial.println("FSAFSA");
        updatePipe();
        // isBulbOn = false;
    }

    void activatePump() {}

private:
    // VARIABLE FUNCTIONS
    void updatePipe()
    {
        Serial.println("PIPE: updatePipe() called");
        humidity = getCurrentHumidity();
        temperature = getCurrentTemperature();
        light = getCurrentLight();
    }

    
    int getCurrentHumidity()
    {
    }

    int getCurrentTemperature()
    {
    }

    int getCurrentLight()
    {
    }
};

void setup()
{
    Pipe pipe();
    Serial.begin(9600);
    initWifi();
    Serial.println("Setup complete.\n");

    ResponseOptions options;
    options.method = "GET";
    options.headers["Content-Type"] = "application/json";
    options.headers["Connection"] = "keep-alive";
    options.body = "email=EMAIL&password=PASSWORD";
    Response response = fetch("https://rickandmortyapi.com/api", options);
    Serial.println(response);
}

void loop()
{
}

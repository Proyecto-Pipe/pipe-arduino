#include <SPI.h>
#include <WiFi.h>
#include <Fetch.h>

// https://www.norwegiancreations.com/2017/09/arduino-tutorial-using-millis-instead-of-delay/

// HTTP REQUEST
#define URL "https://pipe-server.herokuapp.com"
#define PORT 443 // HTTPS port
#define PATH "/pipe"

#define METHOD "GET"
#define CONTENTTYPE "application/json"
#define BODY "{\"email\": \"test@test.com\", \"password\": \"test:80\"}"
#define FINGERPRINT "DC 78 3C 09 3A 78 E3 A0 BA A9 C5 4F 7A A0 87 6F 89 01 71 4C"

const char* ssid = "iPhone de ete sech";
const char* password = "memedona";

class ResponseOptions {
    String method;
    Headers headers;
    String body;
    int follow;
};

ResponseOptions options;
options.method = "GET";
options.headers["Content-Type"] = "application/json";
options.headers["Connection"] = "keep-alive";
options.headers["password"] = "3124315814";
options.body = "{\"email\":\"EMAIL\", \"password\"=\"PASSWORD\"}";

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

    void checkServer() {
      options.method = "GET";
      Response response = fetch(URL, options);
      
    }

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
    Response response = fetch(URL, options);
    Serial.println(response);
}

void loop()
{
}

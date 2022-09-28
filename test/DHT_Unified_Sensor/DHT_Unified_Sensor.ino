//#include <Adafruit_Sensor.h>
#include <DHT.h>
//#include <DHT_U.h>

#define DHTPIN D6
#define DHTTYPE    DHT11

DHT dht(DHTPIN, DHTTYPE);

uint32_t delayMS = 1;

void setup() {
  Serial.begin(115200);
  // Initialize device.
  dht.begin();
}

void loop() {
  // Delay between measurements.
//  delay(delayMS);
  // Get temperature event and print its value.
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(temperature);
    Serial.println("°C");
  }

  if (isnan(humidity)) {
    Serial.println("Error reading humidity!");
  }
  else {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
  }
}

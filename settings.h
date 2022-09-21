#ifndef SETTINGS_H
#define SETTINGS_H

#define VERSION "1.0.4"

// Pins Order:
// 16 5 4 0 2 3.3V GND
// D0 D1 D2 D3 D4 3V GND D5 D6 D7 D8

// No usable pins:
// D0 (GPIO16), D3 (GPIO0), D4 (GPIO2), D8 (GPIO15), TX (GPIO1)
#define FLASH_PIN D7

#define DHT_PIN D6
#define DHT_TYPE DHT11

#define BULB_PIN D7

#define FAN_PIN D0

#define PUMP_PIN D2
#define PUMP_DURATION 2000

#define ANALOG_PIN A0
#define PHOTORESISTOR_ACTIVATOR_PIN D2
#define SOIL_ACTIVATOR_PIN D8

#define DISPLAY_SDA D4 // Serial Data
#define DISPLAY_SCL D5 // Serial Clock

#define BUFFER_SIZE 174

#define SERIAL_BAUD_RATE 115200

const char URL[] = "http://pipe-server.herokuapp.com/v1/pipe";

#define PORT 80
#define API_PASSWORD "4141"

#define WIFI_SSID "iPhone de ete sech"
#define WIFI_PASSWORD "password"

#endif

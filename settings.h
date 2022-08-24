#ifndef SETTINGS_H
#define SETTINGS_H

#define VERSION "1.0.4"

#define FLASH_PIN D7

// Pins Order:
// 16 5 4 0 2 3.3V GND
// D0 D1 D2 D3 D4 3V GND D5 D6 D7 D8

#define DHT_PIN D1
#define DHT_TYPE DHT11

#define PUMP_RELAY_PIN D2
#define PUMP_DURATION 2000

#define BULB_PIN D3

#define PHOTORESISTOR_PIN D5

#define SOUL_MOISTURE_SENSOR_PIN A0

#define BUFFER_SIZE 174

#define SERIAL_BAUD_RATE 115200

const char URL[] = "https://pipe-server.herokuapp.com/v1/pipe";
// char URL[] = "https://rickandmortyapi.com/api";
#define PORT 80                   // HTTPS port
#define API_PASSWORD "23deherrera" // Api

#define WIFI_SSID "iPhone de ete sech"
#define WIFI_PASSWORD "password"

#endif

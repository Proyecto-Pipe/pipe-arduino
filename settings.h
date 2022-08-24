#ifndef SETTINGS_H
#define SETTINGS_H

#define VERSION "1.0.3"

#define FLASH_GPIO_NUM 4

// Pins Order:
// 16 5 4 0 2 3.3V GND

#define DHT_PIN 16
#define DHT_TYPE DHT11

#define PUMP_RELAY_PIN 5
#define PUMP_DURATION 2000

#define BULB_PIN 14

#define PHOTORESISTOR_PIN 0

#define SOUL_MOISTURE_SENSOR_PIN A0

#define BUFFER_SIZE 174

#define SERIAL_BAUD_RATE 9600

const char URL[] = "https://pipe-server.herokuapp.com/v1/pipe";
// char URL[] = "https://rickandmortyapi.com/api";
#define PORT 80                   // HTTPS port
#define API_PASSWORD "23deherrera" // Api

#define WIFI_SSID "iPhone de ete sech"
#define WIFI_PASSWORD "password"

#endif

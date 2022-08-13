#ifndef SETTINGS_H
#define SETTINGS_H

#define VERSION "1.0.3"

#define FLASH_GPIO_NUM 4

// Pins Order:
// 5V GND 12 13 15 14 2 4

#define DHT_PIN 12
#define DHT_TYPE DHT11

#define PUMP_RELAY_PIN 13
#define PUMP_DURATION 2000

#define BULB_PIN 15

#define PHOTORESISTOR_PIN 14

#define BUFFER_SIZE 174

const char URL[] = "https://pipe-server.herokuapp.com/v1/pipe";
// char URL[] = "https://rickandmortyapi.com/api";
#define PORT 80                   // HTTPS port
#define API_PASSWORD "3124315814" // Api

#define WIFI_SSID "iPhone de ete sech"
#define WIFI_PASSWORD "memedona"

#endif

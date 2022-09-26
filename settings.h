#ifndef SETTINGS_H
#define SETTINGS_H

#define VERSION "2.0.0"

// Pins Order:
// 16 5 4 0 2 3.3V GND
// D0 D1 D2 D3 D4 3V GND D5 D6 D7 D8

// No usable pins:
// D0 (GPIO16), D3 (GPIO0), D4 (GPIO2), D8 (GPIO15), TX (GPIO1)
#define FLASH_PIN D7

#define DHT_PIN D6
#define DHT_TYPE DHT11

#define BULB_PIN D3

#define FAN_PIN D0

#define PUMP_PIN D1
#define PUMP_DURATION 2000

#define ANALOG_PIN A0
#define PHOTORESISTOR_ACTIVATOR_PIN D2
#define SOIL_ACTIVATOR_PIN D8

#define DISPLAY_SDA 2 // D4
#define DISPLAY_SCL 14 // D5

#define BUFFER_SIZE 174

#define SERIAL_BAUD_RATE 115200

const char URL[] = "http://pipe-server.herokuapp.com/v1/pipe";

#define PORT 80
#define PERIOD_DURATION 1

#endif

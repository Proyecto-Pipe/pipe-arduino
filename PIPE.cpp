#include "PIPE.h"

#include "DHT.h"
#include "./settings.h"

DHT dht = DHT(DHT_PIN, DHT_TYPE);

PIPE::PIPE()
{
  Serial.println("C/Pipe: Started");
  _setUpPIPE();
  _updatePIPE();
  isBulbOn = 0;
  isPumpOn = 0;
}

void PIPE::onBulb()
{
  Serial.println("C/Pipe: onBulb");
  isBulbOn = 1;
  _onBulb();
}

void PIPE::offBulb()
{
  Serial.println("C/Pipe: offBulb");
  isBulbOn = 0;
  _offBulb();
}

void PIPE::activatePump()
{
  Serial.println("C/Pipe: activatePump");
  isPumpOn = 1;
  _onPump();
  delay(PUMP_DURATION);
  _offPump();
  isPumpOn = 0;
}

void PIPE::_updatePIPE()
{
  Serial.println("C/Pipe: private: updatePipe");
  humidity = _getCurrentHumidity();
  temperature = _getCurrentTemperature();
  light = _getCurrentLight();
}

void PIPE::_setUpPIPE()
{
  // Humidity & Temperature:
  dht.begin();

  // Photoresistor:
  pinMode(PHOTORESISTOR_PIN, OUTPUT);

  // Pump:
  pinMode(PUMP_RELAY_PIN, OUTPUT);
}

float PIPE::_getCurrentHumidity()
{
  return dht.readHumidity();
}

float PIPE::_getCurrentTemperature()
{
  return dht.readTemperature();
}

float PIPE::_getCurrentLight()
{
  return analogRead(PHOTORESISTOR_PIN);
}

void PIPE::_onBulb()
{
  digitalWrite(BULB_PIN, HIGH);
}

void PIPE::_offBulb()
{
  digitalWrite(BULB_PIN, LOW);
}

void PIPE::_onPump()
{
  digitalWrite(PUMP_RELAY_PIN, HIGH);
}

void PIPE::_offPump()
{
  digitalWrite(PUMP_RELAY_PIN, LOW);
}

#include "./PIPE.h"

#include "./settings.h"

#include <DHT.h>

const float MAX_ANALOG_LIGHT = 1024;

PIPE::PIPE()
{
  Serial.println("C/Pipe: Started");
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

void PIPE::onFan()
{
  Serial.println("C/Pipe: onFan");
  isFanOn = 1;
  _onFan();
}

void PIPE::offFan()
{
  Serial.println("C/Pipe: offFan");
  isFanOn = 0;
  _offFan();
}

void PIPE::activatePump()
{
  Serial.println("C/Pipe: activatePump");
  isPumpOn = 1;
  _onPump();
  delay(PUMP_DURATION);
  _offPump();
  isPumpOn = 0;
  Serial.println("C/Pipe: activatePump finished");
}

void PIPE::setUp(DHT *dhtSensorPtr_)
//void PIPE::setUp()
{
  Serial.println("C/Pipe: setUp");
  // DHT:
  dhtSensorPtr = dhtSensorPtr_;

  // Photoresistor and Soil:
  pinMode(ANALOG_PIN, INPUT);
  pinMode(PHOTORESISTOR_ACTIVATOR_PIN, OUTPUT);
  pinMode(SOIL_ACTIVATOR_PIN, OUTPUT);

  // Bulb:
  pinMode(BULB_PIN, OUTPUT);
  digitalWrite(BULB_PIN, LOW);
  isBulbOn = 0;

  // Fan:
  pinMode(FAN_PIN, OUTPUT);

  // Pump:
  pinMode(PUMP_PIN, OUTPUT);
  isPumpOn = 0;
}

void PIPE::update()
{
  Serial.print("C/Pipe: update: ");
//  humidity = _getCurrentHumidity();
  Serial.print("humidity ");
  temperature = _getCurrentTemperature();
  Serial.print("temperature ");
  light = _getCurrentLight();
  Serial.print("light\n");
}

void PIPE::debug()
{
  Serial.println("C/Pipe: debug:");
  update();
  Serial.print("  humidity: ");
  Serial.println(humidity);
  Serial.print("  temperature: ");
  Serial.println(temperature);
  Serial.print("  light: ");
  Serial.println(light);
  Serial.print("  isBulbOn: ");
  Serial.println(isBulbOn);
  Serial.print("  isFanOn: ");
  Serial.println(isFanOn);
  Serial.print("  isPumpOn: ");
  Serial.println(isPumpOn);
}

float PIPE::_getCurrentHumidity()
{
  digitalWrite(PHOTORESISTOR_ACTIVATOR_PIN, LOW);
  digitalWrite(SOIL_ACTIVATOR_PIN, HIGH);
  delay(200);
  const float analogHumidity = analogRead(ANALOG_PIN);
  return analogHumidity;
}

float PIPE::_getCurrentTemperature()
{
//  return dhtSensorPtr->readTemperature();
  return 32.2;
}

float PIPE::_getCurrentLight()
{
//  digitalWrite(PHOTORESISTOR_ACTIVATOR_PIN, HIGH);
//  digitalWrite(SOIL_ACTIVATOR_PIN, LOW);
//  delay(200);
  const float analogLight = analogRead(ANALOG_PIN);
//  return (analogLight * 100.0) / MAX_ANALOG_LIGHT;
  return analogLight;
}

void PIPE::_onBulb()
{
  digitalWrite(BULB_PIN, HIGH);
}

void PIPE::_offBulb()
{
  digitalWrite(BULB_PIN, LOW);
}

void PIPE::_onFan()
{
  digitalWrite(FAN_PIN, HIGH);
}

void PIPE::_offFan()
{
  digitalWrite(FAN_PIN, LOW);
}

void PIPE::_onPump()
{
  digitalWrite(PUMP_PIN, HIGH);
}

void PIPE::_offPump()
{
  digitalWrite(PUMP_PIN, LOW);
}

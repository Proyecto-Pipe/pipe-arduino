#include "./PIPE.h"

#include <DHT.h>
#include "./settings.h"

const float MAX_ANALOG_LIGHT = 1024;

DHT dhtSensor(DHT_PIN, DHT_TYPE);

PIPE::PIPE()
{
  Serial.println("C/Pipe: Started");
  setUp();
  update();
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

void PIPE::setUp()
{
  Serial.println("C/Pipe: setUp");

  // Humidity & Temperature:
  // dhtSensor.begin();

  // Photoresistor:
  pinMode(PHOTORESISTOR_PIN, INPUT);

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
  Serial.println("C/Pipe: update");
  humidity = _getCurrentHumidity();
  temperature = _getCurrentTemperature();
  light = _getCurrentLight();
}

void PIPE::debug()
{
  Serial.println("C/Pipe: debug:");
  update();
  Serial.print("  Humidity: ");
  Serial.println(humidity);
  Serial.print("  Temperature: ");
  Serial.println(temperature);
  Serial.print("  Light: ");
  Serial.println(light);
}

float PIPE::_getCurrentHumidity()
{
  return dhtSensor.readHumidity();
}

float PIPE::_getCurrentTemperature()
{
  return dhtSensor.readTemperature();
}

float PIPE::_getCurrentLight()
{
  const float analogLight = analogRead(PHOTORESISTOR_PIN);
  return (analogLight * 100.0) / MAX_ANALOG_LIGHT;
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

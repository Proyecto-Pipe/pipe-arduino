#include "./PIPE.h"

#include "./settings.h"

#include <DHT.h>

const float MAX_ANALOG_LIGHT = 1024.0;
const float MAX_ANALOG_SOIL_HUMIDITY = 1024.0;

PIPE::PIPE()
{
  Serial.println("C/Pipe: PIPE");
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

void PIPE::onPump()
{
  Serial.println("C/Pipe: onPump");
  isPumpOn = 1;
  _onPump();
}

void PIPE::offPump()
{
  Serial.println("C/Pipe: offPump");
  isPumpOn = 0;
  _offPump();
}

void PIPE::setUp(DHT *dhtSensorPtr_)
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
  airHumidity = _getAirHumidity();
  Serial.print("airHumidity ");
  soilHumidity = _getSoilHumidity();
  Serial.print("soilHumidity ");
  temperature = _getTemperature();
  Serial.print("temperature ");
  light = _getLight();
  Serial.print("light\n");
}

void PIPE::debug()
{
  Serial.println("C/Pipe: debug:");
  update();
  Serial.print("  airHumidity: ");
  Serial.println(airHumidity);
  Serial.print("  soilHumidity: ");
  Serial.println(soilHumidity);
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

void PIPE::debugControls()
{
  Serial.println("C/Pipe: debugControls:");
  onBulb();
  onFan();
  Serial.println("++++++++ Everyting activated");
  Serial.print("Delay.....");
  delay(2000);
  Serial.println("end");
  offBulb();
  offFan();
  Serial.println("-------- Everything deactivated");
  Serial.print("Delay....");
  delay(2000);
  Serial.println("end");
}

float PIPE::_getAirHumidity()
{
  delay(100);
  float humidity = dhtSensorPtr->readHumidity();
  return humidity;
}

float PIPE::_getSoilHumidity()
{
  const float analogHumidity = _readAnalog(true);
  const float inverseHumidity = MAX_ANALOG_SOIL_HUMIDITY - analogHumidity;
  return (inverseHumidity * 100.0) / MAX_ANALOG_SOIL_HUMIDITY;
}

float PIPE::_getTemperature()
{
  delay(100);
  return dhtSensorPtr->readTemperature();
}

float PIPE::_getLight()
{
  const float analogLight = _readAnalog(false);
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
  digitalWrite(FAN_PIN, LOW);
}

void PIPE::_offFan()
{
  digitalWrite(FAN_PIN, HIGH);
}

void PIPE::_onPump()
{
  digitalWrite(PUMP_PIN, LOW);
}

void PIPE::_offPump()
{
  digitalWrite(PUMP_PIN, HIGH);
}

float PIPE::_readAnalog(bool isForSoilHumiditySensor) {
  float value;
  if (isForSoilHumiditySensor) {
    digitalWrite(PHOTORESISTOR_ACTIVATOR_PIN, LOW);
    digitalWrite(SOIL_ACTIVATOR_PIN, HIGH);
    value = analogRead(ANALOG_PIN);
    digitalWrite(PHOTORESISTOR_ACTIVATOR_PIN, HIGH);
    digitalWrite(SOIL_ACTIVATOR_PIN, LOW);
  } else {
    digitalWrite(PHOTORESISTOR_ACTIVATOR_PIN, HIGH);
    digitalWrite(SOIL_ACTIVATOR_PIN, LOW);
    value = analogRead(ANALOG_PIN);
    digitalWrite(PHOTORESISTOR_ACTIVATOR_PIN, LOW);
    digitalWrite(SOIL_ACTIVATOR_PIN, HIGH);
  }
  return value;
}

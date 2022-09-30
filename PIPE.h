#ifndef PIPE_H
#define PIPE_H

#include <DHT.h>

class PIPE
{
public:
  PIPE();

  float airHumidity;
  float soilHumidity;
  float temperature;
  float light;
  int isBulbOn;
  int isFanOn;
  int isPumpOn;

  void onBulb();
  void offBulb();
  void onFan();
  void offFan();
  void onPump();
  void offPump();

  void setUp(DHT* dhtSensorPtr_);
  void update();
  void debug();
  void debugControls();

private:
  DHT* dhtSensorPtr;

  float _getAirHumidity();
  float _getSoilHumidity();
  float _getTemperature();
  float _getLight();

  void _onBulb();
  void _offBulb();

  void _onFan();
  void _offFan();

  void _onPump();
  void _offPump();

  float _readAnalog(bool isForSoilHumiditySensor);
};

#endif

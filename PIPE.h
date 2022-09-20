#ifndef PIPE_H
#define PIPE_H

#include <DHT.h>

class PIPE
{
public:
  PIPE();

  float humidity;
  float temperature;
  float light;
  int isBulbOn;
  int isFanOn;
  int isPumpOn;

  void onBulb();
  void offBulb();
  void onFan();
  void offFan();
  void activatePump();

  void setUp(DHT* dhtSensorPtr_);
  void update();
  void debug();

private:
  DHT* dhtSensorPtr;

  float _getCurrentHumidity();
  float _getCurrentTemperature();
  float _getCurrentLight();

  void _onBulb();
  void _offBulb();

  void _onFan();
  void _offFan();

  void _onPump();
  void _offPump();
};

#endif

#ifndef PIPE_H
#define PIPE_H

class PIPE
{
public:
  PIPE();

  float humidity;
  float temperature;
  float light;
  int isBulbOn;
  int isPumpOn;

  void onBulb();
  void offBulb();
  void activatePump();

private:
  void _updatePIPE();

  void _setUpPIPE();

  float _getCurrentHumidity();
  float _getCurrentTemperature();
  float _getCurrentLight();

  void _onBulb();
  void _offBulb();

  void _onPump();
  void _offPump();
};

#endif

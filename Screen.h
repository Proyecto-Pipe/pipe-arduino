#ifndef SCREEN_H
#define SCREEN_H

#include <LiquidCrystal_I2C.h>

class Screen
{
public:
  static void setUp();
  
  static void helloWorld();
  static void setUpMessage();
  static void searchingWifiMessage(int dots);
  static void requestMessage(char verb[], bool done);
};

#endif

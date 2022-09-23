#ifndef SCREEN_H
#define SCREEN_H

#include <LiquidCrystal_I2C.h>

class Screen
{
public:
  static void setUp();
private:
  static LiquidCrystal_I2C lcd;
};

#endif

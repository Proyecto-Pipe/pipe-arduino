#ifndef SCREEN_H
#define SCREEN_H

#include "./LiquidCrystal_I2C-1.1.2/LiquidCrystal_I2C.h"
#include <LiquidCrystal_I2C.h>

class Screen
{
public:
  static void setUp();

  const static int helloWorldCode = 0;
  static void helloWorld();

  static void yield(int code);
};

#endif

#include "./Screen.h"
#include "./settings.h"

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void Screen::setUp()
{
  Wire.begin(DISPLAY_SDA, DISPLAY_SCL);
  lcd.init();               
  lcd.backlight();
}

void Screen::helloWorld()
{
  lcd.setCursor(0,0);
  lcd.print("Hello World!");
  lcd.setCursor(0,1);
  lcd.print("{{{(>_<)}}}");
}

void Screen::yield(int code)
{
  lcd.clear();
  if (code == helloWorldCode) helloWorld();
}

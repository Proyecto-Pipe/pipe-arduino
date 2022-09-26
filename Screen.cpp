#include "./Screen.h"
#include "./settings.h"
#include "./PIPEInstance.h"
#include "./settings.h"
#include "./env.h"

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
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hello World!");
  lcd.setCursor(0,1);
  lcd.print("{{{(>_<)}}}");
}

void Screen::setUpMessage()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("P.I.P.E. Started!");
}

void Screen::searchingWifiMessage(int dots) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connecting");
  String dotsString = "";
  for (int i = 0; i < dots; i++) {
    dotsString.concat(".");
  }
  lcd.setCursor(10,0);
  lcd.print(dotsString);
  lcd.setCursor(0,1);
  lcd.print(WIFI_SSID);
}

void Screen::requestMessage(char verb[], bool done)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sever: ");
  lcd.setCursor(8,0);
  lcd.print(verb);
  lcd.setCursor(0,1);
  if (done) {
    lcd.print("Done :)");
  } else {
    lcd.print("In progress");
  }
}

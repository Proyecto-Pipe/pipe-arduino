//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#define SDA_PIN D4
#define SCL_PIN D5

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
bool once = true;

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);
}


void loop()
{
  if (once == true) {
    once = false;
    lcd.init();               
    lcd.backlight();

    while (true) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Hello,");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("world!");
      delay(1000);
    }

  }

}

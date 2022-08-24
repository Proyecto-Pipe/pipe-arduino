#include "./flash.h"

#include "./settings.h"

int i = 0;

void flash(int time, int times)
{
  if (i == 0) {
    pinMode(FLASH_PIN, OUTPUT);
    i++;
  }
  

  for (int i = 0; i < times; i++)
  {
    digitalWrite(FLASH_PIN, HIGH);
    delay(time);
    digitalWrite(FLASH_PIN, LOW);
    delay(time);
  }
}

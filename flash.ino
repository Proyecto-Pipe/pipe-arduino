#include "./flash.h"

#include "./settings.h"

int i = 0;

void flash(int time, int times)
{
  if (i == 0) {
    pinMode(FLASH_GPIO_NUM, OUTPUT);
    i++;
  }
  

  for (int i = 0; i < times; i++)
  {
    digitalWrite(FLASH_GPIO_NUM, HIGH);
    delay(time);
    digitalWrite(FLASH_GPIO_NUM, LOW);
    delay(time);
  }
}

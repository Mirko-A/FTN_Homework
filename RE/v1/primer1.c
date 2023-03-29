#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) 
{
  int pin, i;
  
  if (wiringPiSetup() == -1) exit(1);

  pinMode(1, PWM_OUTPUT);

  while(1)
  {
    for (i = 0; i < 1024; i++)
    {
      pwmWrite(1, i);
      delay(10);
    }

    for (i = 1024; i >= 0; i--)
    {
      pwmWrite(1, i);
      delay(10);
    }
  }

  return 0;
}

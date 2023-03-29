#include <wiringPi.h>
#include <softPwm.h>
#include <stdlib.h>

#define PWM_PIN 28
#define KEY_UP_PIN 21
#define KEY_DOWN_PIN 22


int main()
{
  int i = 0;
  int key_pressed = 0; // inicijalno 1 jer pritisnut taster daje 0!!!
  int old_key_pressed = 0; // inicijalno 1 jer pritisnut taster daje 0!!!
  int pwm_value = 0;


  if (wiringPiSetup() == -1) exit(1);

  pinMode(KEY_UP_PIN, INPUT);
  pinMode(KEY_DOWN_PIN, INPUT);

  if (softPwmCreate(PWM_PIN, pwm_value, 100) != 0) exit(2);

  while(1)
  {
    if (digitalRead(KEY_UP_PIN) == 0)
    {
      key_pressed = 1;
    }
    else if (digitalRead(KEY_DOWN_PIN) == 0)
    {
      key_pressed = 2;
    }
    else
    {
      key_pressed = 0;
    }

    if (key_pressed != old_key_pressed)
    {
      // delay za debouncing
      delay(30);

      if (key_pressed == 1) 
      {
        // taster 1 je pritisnut, uvecaj pwm
        pwm_value = pwm_value + 20;
        
        if (pwm_value > 100) pwm_value = 100; 
      }
      else if (key_pressed == 2)
      {
        // taster 2 je pritisnut, smanji pwm
        pwm_value = pwm_value - 20;
        
        if (pwm_value < 0) pwm_value = 0; 
      }
    }

    softPwmWrite(PWM_PIN, pwm_value);

    old_key_pressed = key_pressed;
  }

  return 0;
}
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <stdint.h>
#include <lcd.h>

#define KEY_NOT_PRESSED (0u)

#define PIN_LOW     (0u)
#define PIN_HIGH    (1u)

#define KEY_UP      (21)
#define KEY_DOWN    (22)
#define KEY_LEFT    (23)
#define KEY_RIGHT   (24)

#define MAX_X  (15u)
#define MAX_Y  (1u)

#define MIN_X  (0u)
#define MIN_Y  (0u)

// dodela vrednosti za konkretne pinove
// prema gornjoj tabeli i semi DVK512
const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

int main()
{
	uint8_t x = 0;
    uint8_t y = 0;
	
	uint8_t key_pressed     = KEY_NOT_PRESSED;
	uint8_t old_key_pressed = KEY_NOT_PRESSED;
	
    int lcd_h;

    if (wiringPiSetup() < 0)
	{
        fprintf(stderr, "ERROR: %s\n", strerror (errno));
        return 1;
    }
	
    lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
    
	lcdPosition(lcd_h, 0,0);
    lcdPrintf(lcd_h,"^");
	
	while (1)
	{
		if (digitalRead(KEY_UP) == PIN_LOW)
		{
			key_pressed = KEY_UP;
		}
		else if (digitalRead(KEY_DOWN) == PIN_LOW)
		{
			key_pressed = KEY_DOWN;
		}
		else if (digitalRead(KEY_LEFT) == PIN_LOW)
		{
			key_pressed = KEY_LEFT;
		}
		else if (digitalRead(KEY_RIGHT) == PIN_LOW)
		{
			key_pressed = KEY_RIGHT;
		}
		else
		{
			key_pressed = KEY_NOT_PRESSED;
		}
		
		if (key_pressed != old_key_pressed)
		{
			switch (key_pressed)
			{
				case KEY_UP:
				{
					y = (y == MIN_Y) ? MAX_Y : (y - 1);
				}
				break;
				case KEY_DOWN:
				{
					y = (y == MAX_Y) ? MIN_Y : (y + 1);
				}
				break;
				case KEY_LEFT:
				{
					x = (x == MIN_X) ? MAX_X : (x - 1);
				}
				break;
				case KEY_RIGHT:
				{
					x = (x == MAX_X) ? MIN_X : (y + 1);
				}
				break;
				default
				    /* Do nothing */
				break
			}
		}
		
        lcdClear(lcd_h);
		lcdPosition(lcd_h, x, y);
        lcdPrintf(lcd_h,"^");
		
		old_key_pressed = key_pressed;
		
        delay(100);
	}
}

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>  
#include <wiringPi.h>
#include <lcd.h>
#include <errno.h>


const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

int lcd_h;

int main(int argc, char *argv[]) 
{  
   if(wiringPiSetup() < 0)
   {
       fprintf(stderr, "Greska pri inicijalizaciji: %s\n", strerror(errno));
       exit(1);
   }
   
   lcd_h = lcdInit(2,16,4,RS,EN,D0,D1,D2,D3,D0,D1,D2,D3);

   lcdPosition(lcd_h, 0, 0);
   lcdPrintf(lcd_h, "Displej sa 16 ch");
   lcdPosition(lcd_h, 0, 1);
   lcdPrintf(lcd_h, "u 2 reda.");

   delay(2000);

   lcdClear(lcd_h);
   return 0;
}

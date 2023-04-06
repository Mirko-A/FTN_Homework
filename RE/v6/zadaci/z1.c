#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcd.h>

#define LCD_RS 3
#define LCD_E 14
#define LCD_D4 4
#define LCD_D5 12
#define LCD_D6 13
#define LCD_D7 6

int lcd;
const char PCF8591 = 0x48;
int fd, adcVal;
int main() {
 if (wiringPiSetup () == -1) exit (1);
 fd = wiringPiI2CSetup(PCF8591);
 lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4,LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);
 lcdClear(lcd);
 while (1) {
      // procitaj trimer pot sa AIN3 ulaza
wiringPiI2CReadReg8(fd, PCF8591 + 3); // dummy
adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 3);
float voltage = (adcVal * 3.3) / 255.0;
char buf[16];
snprintf(buf, 16, "Voltage: %.2fV", voltage);
lcdPosition(lcd, 0, 0);
lcdPuts(lcd, buf);
wiringPiI2CWriteReg8(fd, PCF8591 + 4, adcVal);
// procitaj DAC preko AIN2
wiringPiI2CReadReg8(fd, PCF8591 + 2); // dummy
adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 2);
printf("DAC vrednost = %d \n\n", adcVal);
delay(500);
}
return 0;
}



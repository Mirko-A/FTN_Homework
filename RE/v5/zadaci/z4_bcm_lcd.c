#include <wiringPi.h>
//#include <wiringPiI2C.h>
#include <bcm2835.h> 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <lcd.h>

// Adresa PCF8563 na I2C magistrali
#define DEVICE_ID (0x51)

// Pinovi tastera na RPi
#define KEY_UP    (21u)
#define KEY_DOWN  (22u)
#define KEY_OK    (23u)
#define KEY_UNOS  (24u)
#define KEY_NOT_PRESSED (0u)

// Adrese PCF8563 registara (5, 6, 8 za DAN, MES, GOD)
#define SEC_ADDR    (0x02)
#define MIN_ADDR    (0x03)
#define HR_ADDR     (0x04)
#define DAY_ADDR    (0x05)
#define WEEK_ADDR   (0x06)
#define MONTH_ADDR  (0x07)
#define YEAR_ADDR   (0x08)

// Dodela vrednosti za konkretne pinove LCD-a
#define LCD_RS 3
#define LCD_E 14
#define LCD_D4 4
#define LCD_D5 12
#define LCD_D6 13
#define LCD_D7 6

// Dimenzije LCD-a
#define ROWS     2
#define COLUMNS  16

// hh:mm:ss + \n -> 8 + 1 = 9 
#define TIME_STRING_LEN (9u)
// dd:mm:yy + \n -> 8 + 1 = 9
#define DATE_STRING_LEN (9u)

#define FALSE (0u)
#define TRUE  (1u)
typedef unsigned char boolean

typedef enum
{
    DISPLAY = 0x00,
    ENTER_TIME,
    STOP,
} FsmState;

typedef enum
{
    SEC   = 0u,
    MNT   = 1u,
    HOUR  = 2u,
    DAY   = 3u,
    WEEK  = 4u,
    MONTH = 5u,
    YEAR  = 6u,
    SLOTS_LEN
} TimeSlot;

TimeSlot time_slot = SEC;

FsmState state = INIT;

// Needed for button pressing
unsigned char key_pressed = 0;
unsigned char old_key_pressed = 0;

unsigned char WriteBuf[2] = {0}; 

// sec, min, sat...
const unsigned int MAX_TIME_VALUES[] = {60, 60, 24, 31, 12, 99};

unsigned char a_clock[13] = {0};

// Lcd handle
int lcd_h = -1;

int bcdToD(unsigned char byte)
{
    unsigned int b1, b2;
    b1 = byte & 0x0F;
    b2 = ((byte >> 4) & 0x0F) * 10;
    return b1 + b2;
}

unsigned int dToBcd(unsigned int byte)
{
    return ((byte / 10) << 4) + (byte % 10);
}

void setInitialTime(void)
{
    struct tm t;
    time_t now;

    printf("Inititalizing the clock...\n");

    now = time(NULL);
    gmtime_r(&now, &t);

    // Set seconds
    a_clock[SEC] = dToBcd(t.tm_sec);
    WriteBuf[0] = SEC_ADDR;
    WriteBuf[1] = a_clock[SEC];
    bcm2835_i2c_write(WriteBuf, 2);
 
    // Set minutes
    a_clock[MNT] = dToBcd(t.tm_min);
    WriteBuf[0] = MIN_ADDR;
    WriteBuf[1] = a_clock[MNT];
    bcm2835_i2c_write(WriteBuf, 2);

    // Set hours
    a_clock[HOUR] = dToBcd(t.tm_hour);
    WriteBuf[0] = HR_ADDR;
    WriteBuf[1] = a_clock[HOUR];
    bcm2835_i2c_write(WriteBuf, 2);

    // Set day of month
    a_clock[DAY] = dToBcd(t.tm_mday);
    WriteBuf[0] = MONTH_ADDR;
    WriteBuf[1] = a_clock[DAY];
    bcm2835_i2c_write(WriteBuf, 2);

    // Set day of week
    a_clock[WEEK] = dToBcd(t.tm_wday);
    WriteBuf[0] = WEEK_ADDR;
    WriteBuf[1] = a_clock[WEEK];
    bcm2835_i2c_write(WriteBuf, 2);

    // Set month
    a_clock[MONTH] = dToBcd(t.tm_mon + 1);
    WriteBuf[0] = MONTH_ADDR;
    WriteBuf[1] = a_clock[MONTH];
    bcm2835_i2c_write(WriteBuf, 2);

    // Set year
    a_clock[YEAR] = dToBcd(t.tm_year - 100);
    WriteBuf[0] = YEAR_ADDR;
    WriteBuf[1] = a_clock[YEAR];
    bcm2835_i2c_write(WriteBuf, 2);
}

void rtcInit(void)
{
    setInitialTime();

    // Inicijalizacija RTC-a (start clock)
    WriteBuf[0] = 0x00;
    WriteBuf[1] = 0x00;

    bcm2835_i2c_write(WriteBuf, 2);
}

void setCustomTime(void)
{
    // Set seconds
    WriteBuf[0] = SEC_ADDR;
    WriteBuf[1] = a_clock[SEC];
    bcm2835_i2c_write(WriteBuf, 2);
 
    // Set minutes
    WriteBuf[0] = MIN_ADDR;
    WriteBuf[1] = a_clock[MNT];
    bcm2835_i2c_write(WriteBuf, 2);

    // Set hours
    WriteBuf[0] = HR_ADDR;
    WriteBuf[1] = a_clock[HOUR];
    bcm2835_i2c_write(WriteBuf, 2);

    // Set day of month
    WriteBuf[0] = MONTH_ADDR;
    WriteBuf[1] = a_clock[DAY];
    bcm2835_i2c_write(WriteBuf, 2);

    // Set day of week
    WriteBuf[0] = WEEK_ADDR;
    WriteBuf[1] = a_clock[WEEK];
    bcm2835_i2c_write(WriteBuf, 2);

    // Set month
    WriteBuf[0] = MONTH_ADDR;
    WriteBuf[1] = a_clock[MONTH];
    bcm2835_i2c_write(WriteBuf, 2);

    // Set year
    WriteBuf[0] = YEAR_ADDR;
    WriteBuf[1] = a_clock[YEAR];
    bcm2835_i2c_write(WriteBuf, 2);
}

void readTime(void)
{
    WriteBuf[0] = SEC_ADDR;
    bcm2835_i2c_write_read_rs(WriteBuf, 1, a_clock, SLOTS_LEN);

// TODO: put back in if needed
#if 0 
    a_clock[0] =  a_clock[0] & 0x7F;
    a_clock[1] =  a_clock[1] & 0x7F;
    a_clock[2] =  a_clock[2] & 0x3F;
    a_clock[3] =  a_clock[3] & 0x3F;
    a_clock[5] = (a_clock[5] & 0x1F) + 1;
    a_clock[6] =  a_clock[6] + 100;
#endif
}

void printClock(void)
{
    printf("Secs: %02X - %3d\n", a_clock[0], bcdToD(a_clock[0] & 0x7F));
    printf("Mins: %02X - %3d\n", a_clock[1], bcdToD(a_clock[1] & 0x7F));
    printf("Hour: %02X - %3d\n", a_clock[2], bcdToD(a_clock[2] & 0x3F));
    printf("Days: %02X - %3d\n", a_clock[3], bcdToD(a_clock[3] & 0x3F));
    printf("Mnth: %02X - %3d\n", a_clock[5], bcdToD(a_clock[5] & 0x1F) + 1);
    printf("Year: %02X - %3d\n", a_clock[6], bcdToD(a_clock[6] + 100));
}

void printTimeLcd(int x, int y, boolean clear)
{
    unsigned char a_time_string[TIME_STRING_LEN] = {0};

    if (clear == TRUE) lcdClear(lcd_h);

    // Converting time to string TODO: dec or hex?
    itoa(a_clock[SEC], &a_time_string[0], DECIMAL);
    a_time_string[2] = ':';
    itoa(a_clock[MNT], &a_time_string[3], DECIMAL);
    a_time_string[5] = ':';
    itoa(a_clock[HOUR], &a_time_string[6], DECIMAL);
    a_time_string[8] = ':';
    a_time_string[9] = '\n';

    lcdPosition(lcd_h, x, y);
    lcdPrintf(lcd_h, "%s", a_time_string);
}

void printDateLcd(int x, int y, boolean clear)
{
    unsigned char a_date_string[DATE_STRING_LEN] = {0};

    if (clear == TRUE) lcdClear(lcd_h);

    // Converting date to string TODO: dec or hex?
    itoa(a_clock[DAY], &a_date_string[0], DECIMAL);
    a_date_string[2] = ':';
    itoa(a_clock[MONTH], &a_date_string[3], DECIMAL);
    a_date_string[5] = ':';
    itoa(a_clock[YEAR], &a_date_string[6], DECIMAL);
    a_date_string[8] = ':';
    a_date_string[9] = '\n';

    lcdPosition(lcd_h, x, y);
    lcdPrintf(lcd_h, "%s", a_date_string);
}

void printClockLcd(void)
{
    lcdClear(lcd_h);
    printTimeLcd(0, 0, FALSE);
    printDateLcd(0, 1, FALSE);
}

void printClockSelected(TimeSlot slot)
{
    if (slot == SEC)
    {
        printf("Secs: %02X - %3d <\n", a_clock[0], bcdToD(a_clock[0] & 0x7F));
    }
    else
    {
        printf("Secs: %02X - %3d\n", a_clock[0], bcdToD(a_clock[0] & 0x7F));
    }
    
    if (slot == MNT)
    {
        printf("Mins: %02X - %3d <\n", a_clock[1], bcdToD(a_clock[1] & 0x7F));
    }
    else
    {
        printf("Mins: %02X - %3d\n", a_clock[1], bcdToD(a_clock[1] & 0x7F));
    }

    if (slot == HOUR)
    {
        printf("Hour: %02X - %3d <\n", a_clock[2], bcdToD(a_clock[2] & 0x3F));
    }
    else
    {
        printf("Hour: %02X - %3d\n", a_clock[2], bcdToD(a_clock[2] & 0x3F));
    }

    if (slot == DAY)
    {
        printf("Days: %02X - %3d <\n", a_clock[3], bcdToD(a_clock[3] & 0x3F));
    }
    else
    {
        printf("Days: %02X - %3d\n", a_clock[3], bcdToD(a_clock[3] & 0x3F));
    }

    if (slot == MONTH)
    {
        printf("Mnth: %02X - %3d <\n", a_clock[5], bcdToD(a_clock[5] & 0x1F) + 1);
    }
    else
    {
        printf("Mnth: %02X - %3d\n", a_clock[5], bcdToD(a_clock[5] & 0x1F) + 1);
    }

    if (slot == YEAR)
    {
        printf("Year: %02X - %3d <\n", a_clock[6], bcdToD(a_clock[6] + 100));
    }
    else
    {
        printf("Year: %02X - %3d\n", a_clock[6], bcdToD(a_clock[6] + 100));
    }
}

void printClockSelectedLcd(TimeSlot slot)
{
    if ((slot == SEC) ||
        (slot == MNT) ||
        (slot == HOUR))
    {
        printTimeLcd(0, 0, TRUE);
        
        switch (slot)
        {
            case SEC: lcdPosition(lcd_h, 1, 1);
            break;
            case MNT: lcdPosition(lcd_h, 3, 1);
            break;
            case HOUR: lcdPosition(lcd_h, 5, 1);
            break;
            default:
            break;
        }

        lcdPrintf(lcd_h, "^");
    }
    else if ((slot == DAY)   ||
             (slot == MONTH) ||
             (slot == YEAR))
    {
        printDateLcd(0, 0, TRUE);
        
        switch (slot)
        {
            case DAY: lcdPosition(lcd_h, 1, 1);
            break;
            case MONTH: lcdPosition(lcd_h, 3, 1);
            break;
            case YEAR: lcdPosition(lcd_h, 5, 1);
            break;
            default:
            break;
        }

        lcdPrintf(lcd_h, "^");
    }
    else
    {
        printf("WARNING: Incorrect time slot provided.");
    }
}

void updateTime(unsigned char key)
{
    if (key == KEY_DOWN)
    {
        if (a_clock[time_slot] == 0u)
        {
            a_clock[time_slot] = MAX_TIME_VALUES[time_slot];
        }
        else
        {
            a_clock[time_slot]--;
        }
    }
    else if (key == KEY_UP)
    {
        if (a_clock[time_slot] == MAX_TIME_VALUES[time_slot])
        {
            a_clock[time_slot] = 0;
        }
        else
        {
            a_clock[time_slot]++;
        }
    }
}

int main(int argc, char **argv)
{
#if 0
    if (wiringPiSetup()  < 0)
    {
        printf("ERROR: Failed to init wiringPi.\n");
        return -1;
    }

    pinMode(KEY_UP, INPUT);
    pinMode(KEY_DOWN, INPUT);      
    pinMode(KEY_OK, INPUT);
    pinMode(KEY_UNOS, INPUT);  
#endif     

    printf("Initializing I2C protocol...\n");
    if (!bcm2835_init())
    {
        printf("ERROR: Failed to init I2C communication.\n");
        return -1;
    }

    printf("Starting I2C communication...\n");
    bcm2835_i2c_begin(); 
    
    bcm2835_i2c_setSlaveAddress(DEVICE_ID);
    bcm2835_i2c_set_baudrate(10000);
    
    rtcInit();

    lcd_h = lcdInit(ROWS, COLUMNS, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);
    if (lcd_h)
    {
        printf("ERROR: Failed to init LCD.\n");
        return -1;
    }
    lcdClear(lcd_h);
	lcdPosition(lcd_h, 0, 0);

    while(1)
    {
        if (digitalRead(KEY_UP) == 0)
        {
            key_pressed = KEY_UP;
            //printf("21");
        }
        else if (digitalRead(KEY_DOWN) == 0)
        {
            key_pressed = KEY_DOWN;
            //printf("22");
        }
        else if (digitalRead(KEY_UNOS) == 0)
        {
            key_pressed = KEY_UNOS;
            //printf("23");
        }
        else if (digitalRead(KEY_OK) == 0)
        {
            key_pressed = KEY_OK;
            //printf("24");
        }
        else
        {
            key_pressed = KEY_NOT_PRESSED;
        }

        switch (state)
        {
            case DISPLAY:
            {
                readTime();
                printClockLcd(); 

                if (key_pressed == KEY_UNOS && key_pressed != old_key_pressed)
                {
                    state = ENTER_TIME;
                }

                bcm2835_delay(200);
            }
            break;
            case ENTER_TIME:
            {
                printClockSelectedLcd(time_slot);

                if (key_pressed != old_key_pressed)
                {
                    if (key_pressed == KEY_UP || key_pressed == KEY_DOWN)
                    {
                        updateTime(key_pressed);
                    }
                    else if (key_pressed == KEY_UNOS)
                    {
                        if (time_slot == YEAR)
                        {
                            time_slot = SEC;
                        }
                        else
                        {
                            time_slot++;
                        }
                    }
                    else if (key_pressed == KEY_OK)
                    {
                        // Stop the clock 
                        WriteBuf[0] = 0x00;
                        WriteBuf[1] = 0x20;
                        bcm2835_i2c_write(WriteBuf, 2);

                        // Write new time to RTC
                        setCustomTime();

                        // Start the clock 
                        WriteBuf[0] = 0x00;
                        WriteBuf[1] = 0x00;
                        bcm2835_i2c_write(WriteBuf, 2);

                        state = DISPLAY;
                    }
                }

                bcm2835_delay(200);
            }
            break;
            case STOP:
            {
                
                bcm2835_i2c_end();
                bcm2835_close();

                return 0;
            }
            break;
            default: state = STOP;
            break;
        }
    }
}
















#include <wiringPi.h>
//#include <wiringPiI2C.h>
#include <bcm2835.h> 
#include <stdio.h>
#include <time.h>
#include <unistd.h>


// adresa PCF8563 na I2C magistrali
#define DEVICE_ID (0x51)

// Pinovi tastera na RPi
#define KEY_UP    (21u)
#define KEY_DOWN  (22u)
#define KEY_OK    (23u)
#define KEY_UNOS  (24u)
#define KEY_NOT_PRESSED (0u)

// adrese PCF8563 registara (5, 6, 8 za DAN, MES, GOD)
#define SEC_ADDR    (0x02)
#define MIN_ADDR    (0x03)
#define HR_ADDR     (0x04)
#define DAY_ADDR    (0x05)
#define WEEK_ADDR   (0x06)
#define MONTH_ADDR  (0x07)
#define YEAR_ADDR   (0x08)

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

FsmState state = DISPLAY;

// Needed for button pressing
unsigned char key_pressed = 0;
unsigned char old_key_pressed = 0;

unsigned char WriteBuf[2] = {0}; 

// sec, min, sat...
const unsigned int MAX_TIME_VALUES[] = {60, 60, 24, 31, 12, 99};

unsigned char a_clock[13] = {0};

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
    WriteBuf[0] = DAY_ADDR;
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

void printTime(void)
{
    printf("Secs: %02X - %3d\n", a_clock[0], bcdToD(a_clock[0] & 0x7F));
    printf("Mins: %02X - %3d\n", a_clock[1], bcdToD(a_clock[1] & 0x7F));
    printf("Hour: %02X - %3d\n", a_clock[2], bcdToD(a_clock[2] & 0x3F));
    printf("Days: %02X - %3d\n", a_clock[3], bcdToD(a_clock[3] & 0x3F));
    printf("Mnth: %02X - %3d\n", a_clock[5], bcdToD(a_clock[5] & 0x1F) + 1);
    printf("Year: %02X - %3d\n", a_clock[6], bcdToD(a_clock[6] + 100));
}

void printTimeSelected(TimeSlot slot)
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

    while(1)
    {
        if (digitalRead(KEY_UP) == 0)
        {
            //key_pressed = KEY_UP;
            //printf("21");
        }
        else if (digitalRead(KEY_DOWN) == 0)
        {
            //key_pressed = KEY_DOWN;
            //printf("22");
        }
        else if (digitalRead(KEY_UNOS) == 0)
        {
            //key_pressed = KEY_UNOS;
            //printf("23");
        }
        else if (digitalRead(KEY_OK) == 0)
        {
            //key_pressed = KEY_OK;
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
                printTime(); // TODO: Change to LCD

                if (key_pressed == KEY_UNOS && key_pressed != old_key_pressed)
                {
                    state = ENTER_TIME;
                }

                bcm2835_delay(2000); // TODO: Lower when LCD is used
            }
            break;
            case ENTER_TIME:
            {
                printTimeSelected(time_slot); // TODO: Change to LCD

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

                bcm2835_delay(2000); // TODO: Lower when LCD is used
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

        printf("\n");
    }
}
















#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define DEVICE_ID (0x51)

#define KEY_UP    (21u)
#define KEY_DOWN  (22u)
#define KEY_OK    (23u)
#define KEY_UNOS  (24u)
#define KEY_NOT_PRESSED (0u)

// adrese registara (5, 6, 8 za DAN, MES, GOD)
#define SEC_ADDR 0x02
#define MIN_ADDR 0x03
#define HR_ADDR  0x04
#define DAY_ADDR 0x05
#define WEEK_ADDR 0x06
#define MONTH_ADDR 0x07
#define YEAR_ADDR  0x08

unsigned char key_pressed = 0;
unsigned char old_key_pressed = 0;

typedef enum
{
    INIT = 0x00,
    DISPLAY,
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
    YEAR  = 6u
} TimeSlot;

TimeSlot time_slot = SEC;

FsmState state = INIT;

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

void setTime(int i2c_fd)
{
    struct tm t;
    time_t now;

    printf("Setting the clock...\n");

    now = time(NULL);
    gmtime_r(&now, &t);

    a_clock[0] = dToBcd(t.tm_sec);
    a_clock[1] = dToBcd(t.tm_min);
    a_clock[2] = dToBcd(t.tm_hour);
    a_clock[3] = dToBcd(t.tm_mday);
    a_clock[4] = dToBcd(t.tm_wday);
    a_clock[5] = dToBcd(t.tm_mon + 1);
    a_clock[6] = dToBcd(t.tm_year - 100);
    a_clock[7] = 0;
    a_clock[8] = 0;
    a_clock[9] = 0;
    a_clock[10] = 0;
    a_clock[11] = 0;
    a_clock[12] = 0;

    wiringPiI2CWriteReg8(i2c_fd, 0, 0x20); // Stop the clock

    // Start reading form register 0:
    wiringPiI2CWrite(i2c_fd, 2);
    // Write 7 bytes
    write(i2c_fd, a_clock, 13);

    wiringPiI2CWriteReg8(i2c_fd, 0, 0x00);  // Start the clock
}



void readTime(int i2c_fd)
{
    // Start reading form register 0:
    wiringPiI2CWrite(i2c_fd, 2);
    delay(10);
    // Read in 7 bytes
    int bytes_read = read(i2c_fd, a_clock, 7);

    if (bytes_read != 7)
    {
        printf("read got: %d\n", bytes_read);
    }
    else
    {
        printf("Read 7 bytes");
    }
// TODO
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
#if 1
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
           
    int rtc_i2c_fd = wiringPiI2CSetup(DEVICE_ID);
    if (rtc_i2c_fd < 0)
    {
        printf("ERROR: Failed to init I2C communication.\n");
        return -1;
    }

    setTime(rtc_i2c_fd);

    printf("Status reg 0: %d\n", wiringPiI2CReadReg8(rtc_i2c_fd, 0));
    printf("Status reg 1: %d\n", wiringPiI2CReadReg8(rtc_i2c_fd, 1));

    wiringPiI2CWriteReg8(rtc_i2c_fd, 0, 0);
    wiringPiI2CWriteReg8(rtc_i2c_fd, 1, 0);

    printf("Status reg 0: %d\n", wiringPiI2CReadReg8(rtc_i2c_fd, 0));
    printf("Status reg 1: %d\n", wiringPiI2CReadReg8(rtc_i2c_fd, 1));

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
            case INIT:
            {            
                state = DISPLAY;
            }
            break;
            case DISPLAY:
            {
                readTime(rtc_i2c_fd);
                printTime(); // TODO: Change to LCD

                if (key_pressed == KEY_UNOS && key_pressed != old_key_pressed)
                {
                    state = ENTER_TIME;
                }

                delay(500); // TODO: Lower when LCD is used
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
                        //TODO: here time should be updated to new time (z4)
                        state = DISPLAY;
                    }
                }

                delay(500); // TODO: Lower when LCD is used
            }
            break;
            case STOP:
            {

                return 0;
            }
            break;
            default: state = STOP;
            break;
        }

        printf("\n");
    }
}
















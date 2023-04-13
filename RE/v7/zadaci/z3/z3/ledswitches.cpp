#include "ledswitches.h"
#include "ui_ledswitches.h"
#include "stdint.h"
#include "wiringPi.h"

const uint8_t LEDS[4] = {25u, 26u, 27u, 28u};

LedSwitches::LedSwitches(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LedSwitches)
{
    ui->setupUi(this);
}

LedSwitches::~LedSwitches()
{
    delete ui;
}


void LedSwitches::on_checkBox_stateChanged(int arg1)
{
    digitalWrite(LEDS[0], arg1);
}

void LedSwitches::on_checkBox_2_stateChanged(int arg1)
{
    digitalWrite(LEDS[1], arg1);
}

void LedSwitches::on_checkBox_3_stateChanged(int arg1)
{
    digitalWrite(LEDS[2], arg1);
}

void LedSwitches::on_checkBox_4_stateChanged(int arg1)
{
    digitalWrite(LEDS[3], arg1);
}

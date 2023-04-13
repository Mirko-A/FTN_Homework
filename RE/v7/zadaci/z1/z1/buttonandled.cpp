#include "buttonandled.h"
#include "ui_buttonandled.h"

#include "wiringPi.h"
#define LED_PIN (25u)

buttonAndLed::buttonAndLed(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::buttonAndLed)
{
    ui->setupUi(this);
}

buttonAndLed::~buttonAndLed()
{
    delete ui;
}


void buttonAndLed::on_pushButton_clicked()
{
    if (digitalRead(LED_PIN) == 1)
    {
        digitalWrite(LED_PIN, 0);
    }
    else
    {
        digitalWrite(LED_PIN, 1);
    }
}

#include "sliderdimmer.h"
#include "ui_sliderdimmer.h"
#include "wiringPi.h"
#include "softPwm.h"

#define LED_PIN (25u)

sliderDimmer::sliderDimmer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::sliderDimmer)
{
    ui->setupUi(this);
}

sliderDimmer::~sliderDimmer()
{
    delete ui;
}


void sliderDimmer::on_horizontalSlider_valueChanged(int value)
{
    softPwmWrite(LED_PIN, value);
}

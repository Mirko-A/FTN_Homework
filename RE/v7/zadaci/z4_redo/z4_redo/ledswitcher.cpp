#include "ledswitcher.h"
#include "ui_ledswitcher.h"

LedSwitcher::LedSwitcher(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LedSwitcher)
{
    ui->setupUi(this);
}

LedSwitcher::~LedSwitcher()
{
    delete ui;
}


void LedSwitcher::on_pushButton_clicked(bool checked)
{
    if (checked == true)
    {
        ui->label->setPixmap(QPixmap(":/imgs/switch_on.png"));
    }
    else
    {
        ui->label->setPixmap(QPixmap(":/imgs/switch_off.png"));
    }
}

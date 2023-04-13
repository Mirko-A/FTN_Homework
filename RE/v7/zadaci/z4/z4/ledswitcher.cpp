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


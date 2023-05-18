#include "lcdtext.h"
#include "ui_lcdtext.h"

#include "lcd.h"

LcdText::LcdText(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LcdText)
{
    ui->setupUi(this);
}

LcdText::~LcdText()
{
    delete ui;
}


void LcdText::on_pushButton_clicked()
{
    QString red1_text = ui->Red1_Txt->text();
    QString red2_text = ui->Red2_Txt->text();

    lcdPosition(lcd, 0, 0);
    lcdPrintf(lcd, red1_text.toLocal8Bit().data());
    lcdPosition(lcd, 0, 1);
    lcdPrintf(lcd, red2_text.toLocal8Bit().data());
}

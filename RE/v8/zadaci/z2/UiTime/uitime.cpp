#include "uitime.h"
#include "ui_uitime.h"
#include <QTime>
#include <QTimer>

const QString format = "hh:mm:ss";

Ui::UiTime* ui_alias;

UiTime::UiTime(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UiTime)
{
    ui->setupUi(this);

    ui_alias = ui;

    QTimer* sec_ticker = new QTimer(this);
    connect(sec_ticker, SIGNAL(timeout()), this, SLOT(updateTime()));
    sec_ticker->start(1000);
}

UiTime::~UiTime()
{
    delete ui;
}

void updateTime(void)
{
    readTime();
    QTime time(a_clock[HOUR], a_clock[MNT], a_clock[SEC], 0);
    QString time_str = time.toString(format);
    ui_alias->Ispis->setText(time_str);
}

void UiTime::on_pushButton_clicked()
{

}


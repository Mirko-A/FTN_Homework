#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <wiringPiI2C.h>

#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>

#include <iostream>

extern unsigned char WriteBuf;
extern unsigned char ReadBuf;

extern int i2c_fd;

static unsigned int x_pos = 0;

QtCharts::QChart* chart = nullptr;
QtCharts::QLineSeries* series = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    series = new QtCharts::QLineSeries();

    QtCharts::QChart* chart = new QtCharts::QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    chart->axisX()->setRange(0, 5);
    chart->axisY()->setRange(0, 3.3);

    chart->setTitle("Merenje napona");

    QtCharts::QChartView* chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->verticalLayout->addWidget(chartView);

    sec_ticker = new QTimer(this);
    connect(sec_ticker, SIGNAL(timeout()), this, SLOT(UpdateChart()));
    sec_ticker->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sec_ticker;
}

void MainWindow::UpdateChart()
{
    ReadBuf = wiringPiI2CReadReg8(i2c_fd, LIGHT_ADDR);
    double voltage = (double)ReadBuf * 3.3f / 255.0f;

    series->append(x_pos, voltage);

    x_pos += 1;
    if(x_pos == 6)
    {
        series->clear();
        x_pos = 0;
    }
}

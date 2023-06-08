#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>

// adresa PCF8563 na I2C magistrali
#define DEVICE_ID (0x48)

#define LIGHT_ADDR (DEVICE_ID + 0)
#define VOLTAGE_ADDR (DEVICE_ID + 3)
#define TEMP_ADDR (DEVICE_ID + 1)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void UpdateSensorValues();

private:
    Ui::MainWindow *ui;
    QTimer* sec_ticker;
};
#endif // MAINWINDOW_H

#ifndef LEDSWITCHER_H
#define LEDSWITCHER_H

#include <QMainWindow>
#include "wiringPi.h"

#define LED_PIN (25u)

QT_BEGIN_NAMESPACE
namespace Ui { class LedSwitcher; }
QT_END_NAMESPACE

class LedSwitcher : public QMainWindow
{
    Q_OBJECT

public:
    LedSwitcher(QWidget *parent = nullptr);
    ~LedSwitcher();

private:
    Ui::LedSwitcher *ui;
};
#endif // LEDSWITCHER_H

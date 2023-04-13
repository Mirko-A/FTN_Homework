#ifndef LEDSWITCHES_H
#define LEDSWITCHES_H

#include <QMainWindow>

extern const uint8_t LEDS[4];

QT_BEGIN_NAMESPACE
namespace Ui { class LedSwitches; }
QT_END_NAMESPACE

class LedSwitches : public QMainWindow
{
    Q_OBJECT

public:
    LedSwitches(QWidget *parent = nullptr);
    ~LedSwitches();

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_4_stateChanged(int arg1);

private:
    Ui::LedSwitches *ui;
};
#endif // LEDSWITCHES_H

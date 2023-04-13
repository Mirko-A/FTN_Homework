#ifndef BUTTONANDLED_H
#define BUTTONANDLED_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class buttonAndLed; }
QT_END_NAMESPACE

class buttonAndLed : public QMainWindow
{
    Q_OBJECT

public:
    buttonAndLed(QWidget *parent = nullptr);
    ~buttonAndLed();

private slots:
    void on_pushButton_clicked();

private:
    Ui::buttonAndLed *ui;
};
#endif // BUTTONANDLED_H

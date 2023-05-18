#ifndef LCDTEXT_H
#define LCDTEXT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class LcdText; }
QT_END_NAMESPACE

extern int lcd;

class LcdText : public QMainWindow
{
    Q_OBJECT

public:
    LcdText(QWidget *parent = nullptr);
    ~LcdText();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LcdText *ui;
};
#endif // LCDTEXT_H

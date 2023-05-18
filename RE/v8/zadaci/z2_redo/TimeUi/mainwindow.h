#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef enum
{
    SEC   = 0u,
    MNT   = 1u,
    HOUR  = 2u,
    DAY   = 3u,
    WEEK  = 4u,
    MONTH = 5u,
    YEAR  = 6u,
    SLOTS_LEN
} TimeSlot;

extern void setCustomTime(void);
extern void readTime(void);
extern unsigned char a_clock[];

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateTime(void);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
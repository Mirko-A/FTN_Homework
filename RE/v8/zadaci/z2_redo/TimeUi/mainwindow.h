#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Taster_clicked();
    void updateTime(void);

    void on_InvertRow_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QTimer* sec_ticker;
};
#endif // MAINWINDOW_H

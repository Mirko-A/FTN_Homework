#ifndef UITIME_H
#define UITIME_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class UiTime; }
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

extern void updateTime(void);

class UiTime : public QMainWindow
{
    Q_OBJECT

public:
    UiTime(QWidget *parent = nullptr);
    ~UiTime();

private slots:
    void on_pushButton_clicked();

    void on_Ispis_textChanged(const QString &arg1);

private:
    Ui::UiTime *ui;
};
#endif // UITIME_H

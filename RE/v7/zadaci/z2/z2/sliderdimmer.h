#ifndef SLIDERDIMMER_H
#define SLIDERDIMMER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class sliderDimmer; }
QT_END_NAMESPACE

class sliderDimmer : public QMainWindow
{
    Q_OBJECT

public:
    sliderDimmer(QWidget *parent = nullptr);
    ~sliderDimmer();

private slots:
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::sliderDimmer *ui;
};
#endif // SLIDERDIMMER_H

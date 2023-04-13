#ifndef SLIDEANDPROGRESS_H
#define SLIDEANDPROGRESS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SlideAndProgress; }
QT_END_NAMESPACE

class SlideAndProgress : public QMainWindow
{
    Q_OBJECT

public:
    SlideAndProgress(QWidget *parent = nullptr);
    ~SlideAndProgress();

private:
    Ui::SlideAndProgress *ui;
};
#endif // SLIDEANDPROGRESS_H

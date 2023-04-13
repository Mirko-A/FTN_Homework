#include "slideandprogress.h"
#include "ui_slideandprogress.h"

SlideAndProgress::SlideAndProgress(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SlideAndProgress)
{
    ui->setupUi(this);
}

SlideAndProgress::~SlideAndProgress()
{
    delete ui;
}


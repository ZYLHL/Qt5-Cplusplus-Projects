#include "digitalclock.h"
#include "ui_digitalclock.h"
#include <QtCore>

DigitalClock::DigitalClock(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DigitalClock)
{
    ui->setupUi(this);
    ui->lcdNumber->setStyleSheet("border: 5px solid black; color: black; background: white;");
    QTimer *pTimer=new QTimer(this);
    pTimer->setInterval(1000);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    pTimer->start();
}

DigitalClock::~DigitalClock()
{
    delete ui;
}

void DigitalClock::onTimeOut() {
    QDateTime dateTime=QDateTime::currentDateTime();
    ui->lcdNumber->display(dateTime.toString("yyyy-MM-dd HH:mm:ss"));
}

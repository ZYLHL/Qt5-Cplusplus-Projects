#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H

#include <QMainWindow>
#include <QLCDNumber>
#include <QTimer>
#include <QDateTime>

namespace Ui {
class DigitalClock;
}

class DigitalClock : public QMainWindow
{
    Q_OBJECT
public:
    explicit DigitalClock(QWidget *parent = nullptr);
    ~DigitalClock();
private slots:
    void onTimeOut();
private:
    Ui::DigitalClock *ui;
};

#endif // DIGITALCLOCK_H

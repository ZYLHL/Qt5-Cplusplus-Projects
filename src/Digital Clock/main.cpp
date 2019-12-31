#include "digitalclock.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DigitalClock w;
    w.show();

    return a.exec();
}

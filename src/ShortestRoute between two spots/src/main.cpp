#include "pch.hpp"
#include "ui/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QTranslator translations(&a);
    translations.load(QLocale::system(), "", "", ":/ts");
    a.installTranslator(&translations);

    MainWindow w;
    w.show();
    return a.exec();
}

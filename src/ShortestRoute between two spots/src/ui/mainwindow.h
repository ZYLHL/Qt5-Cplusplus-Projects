#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pch.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_calculate_clicked();
    void on_pushButton_bus1_clicked();
    void on_pushButton_bus2_clicked();
    void on_pushButton_bus3_clicked();

private:
    Ui::MainWindow *ui;
    int start = -1, end = -1;
    bool isStart=true;
    void set_point(int n);
    void zoom(int addWidth);
};
#endif // MAINWINDOW_H

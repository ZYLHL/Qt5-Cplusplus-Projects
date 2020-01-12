#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "pch.hpp"
#include "core/demo.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    zoom(0);
    connect(ui->zoomArea, &ZoomArea::zoomin, [this] {zoom(100);});
    connect(ui->zoomArea, &ZoomArea::zoomout, [this] {zoom(-100);});

    connect(ui->pushButton_start, &QPushButton::clicked, [this] {isStart = true;});
    connect(ui->pushButton_end, &QPushButton::clicked, [this] {isStart = false;});
    connect(ui->actionAboutQt, &QAction::triggered, [this] {QMessageBox::aboutQt(this);});
    connect(ui->actionAbout, &QAction::triggered, [this] {
        QString content = tr(
            "<h3>幻想市公共交通乘坐路线查询程序</h3>"
            "<b>版本号：v0.1(Only For Demo)</b>"
            "<h4>开发者：新阳国际集团迪里科技工作室</h4>"
        );
        QMessageBox::about(this, tr("关于此程序"), content);
    });

    for (int i = 0; i <= 16; i++) {
        QString num = num.asprintf("%02d", i);
        connect(ui->frame->findChild<QPushButton *>("pushButton_p" + num), &QPushButton::clicked, [this, i] {
            set_point(i);
        });
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_calculate_clicked() {
    if (ui->radioButton_dijkstra->isChecked()) {
        ui->textBrowser_path->setText(QString::fromStdString(dij(start, end)));
    } else if (ui->radioButton_floyd->isChecked()) {
        ui->textBrowser_path->setText(QString::fromStdString(floyd(start, end)));
    } else
        throw std::runtime_error("no algo select");
}

void MainWindow::set_point(int n) {
    if (isStart) {
        start = n;
        ui->pushButton_start->setText(tr("Start: %1").arg(QString::fromStdString(getName(n))));
    } else {
        end = n;
        ui->pushButton_end->setText(tr("End: %1").arg(QString::fromStdString(getName(n))));
    }
}

void MainWindow::zoom(int addWidth) {
    using namespace std;
    static bool first = true;
    static vector<QPushButton *> buttons;
    static vector<pair<double, double>> points;
    static double raw_width, raw_height;
    if (first) {
        raw_width = ui->label_img->pixmap()->width();
        raw_height = ui->label_img->pixmap()->height();
        ui->label_img->setGeometry(0, 0, raw_width, raw_height);
        ui->label_img->setScaledContents(true);
        ui->frame->setMinimumSize(ui->label_img->width(), ui->label_img->height());
        for (int i = 0; i <= 16; i++) {
            QString num = num.asprintf("%02d", i);
            buttons.push_back(ui->frame->findChild<QPushButton *>("pushButton_p" + num));
            points.push_back(make_pair(
                                 buttons.back()->x() + buttons.back()->width() / 2,
                                 buttons.back()->y() + buttons.back()->height() / 2
                             ));
        }
        first = false;
    }

    double new_width = ui->label_img->width() + addWidth;
    double new_height = raw_height * new_width / raw_width;
    ui->label_img->setGeometry(0, 0, new_width, new_height);
    ui->frame->setMinimumSize(ui->label_img->width(), ui->label_img->height());
    for (size_t i = 0; i < buttons.size(); i++) {
        buttons[i]->setGeometry(
            points[i].first / raw_width * new_width - buttons[i]->width() / 2,
            points[i].second / raw_height * new_height - buttons[i]->height() / 2,
            buttons[i]->width(),
            buttons[i]->height()
        );
    }
}

void MainWindow::on_pushButton_bus1_clicked() {
    QString String1="一号线站点如下：\n"
                    "物流集散中心\n"
                    "大学城\n"
                    "机场航站楼\n"
                    "新世界中心\n"
                    "园区路口\n"
                    "新阳大厦\n";
    ui->textBrowser_path->setText(String1);
}

void MainWindow::on_pushButton_bus2_clicked() {
    QString String2="二号线(环线)站点如下：\n"
                    "物流集散中心\n"
                    "大学城\n"
                    "机场航站楼\n"
                    "音乐谷广场\n"
                    "中华社区\n"
                    "丰源路口\n"
                    "新阳大厦\n"
                    "滨江别墅带\n"
                    "污水处理厂\n"
                    "石化园区\n"
                    "幻想北客站\n"
                    "中华山脚\n"
                    "物流集散中心\n";
    ui->textBrowser_path->setText(String2);
}

void MainWindow::on_pushButton_bus3_clicked() {
    QString String3="三号线站点如下：\n"
                    "幻想北客站\n"
                    "人民公园\n"
                    "辛德尔路\n"
                    "新世界中心\n"
                    "中华社区\n"
                    "汽车总站\n";
    ui->textBrowser_path->setText(String3);
}

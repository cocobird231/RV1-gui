#include "mainwindow.h"
#include "./../ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qosdevicedialog->show();
    the_install_shell->show();
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_QosPushButton_clicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::on_SensorPushButton_clicked);
}
MainWindow::~MainWindow()
{
    delete ui;

}



void MainWindow::on_QosPushButton_clicked(){

    qosdevicedialog->show();
}
void MainWindow::on_SensorPushButton_clicked(){
    the_sensor_form->show();
}

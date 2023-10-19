#include "mainwindow.h"
#include "./../ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_QosPushButton_clicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::on_SensorPushButton_clicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::on_data_server_record_puchButton_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::on_install_shell_PushButton_clicked);

}
MainWindow::~MainWindow()
{
    the_sensor_form->close();
    qosdevicedialog->close();
    the_install_shell->close();
    delete ui;

}

void MainWindow::on_QosPushButton_clicked(){
    qosdevicedialog->show();
}
void MainWindow::on_SensorPushButton_clicked(){
    the_sensor_form->show();
}
void MainWindow::on_data_server_record_puchButton_clicked(){
    the_data_server_record->show();
}
void MainWindow::on_install_shell_PushButton_clicked(){
    the_install_shell->show();
}
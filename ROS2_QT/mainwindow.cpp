#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qosdevicedialog->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtuon_clicked(){

    qosdevicedialog->show();
}

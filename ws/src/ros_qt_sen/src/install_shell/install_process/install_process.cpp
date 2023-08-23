#include "install_process.h"
#include "./../ui_install_process.h"

install_process::install_process(QWidget *parent,QString host_name) :
    QWidget(parent),
    ui(new Ui::install_process)
{
    ui->setupUi(this);
    ui->label_2->setText(host_name);
}
void install_process::setText(QString contants){
    ui->textBrowser->setText(contants);
}
install_process::~install_process()
{
    delete ui;
}

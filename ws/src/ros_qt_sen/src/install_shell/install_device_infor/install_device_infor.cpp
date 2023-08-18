#include "install_device_infor.h"
#include "./../ui_install_device_infor.h"

install_device_infor::install_device_infor(QWidget *parent,QString host_name,QString infor) :
    QWidget(parent),
    ui(new Ui::install_device_infor)
{
    ui->setupUi(this);
    ui->label_2->setText(host_name);
    ui->textBrowser->setText(infor);
    connect(ui->pushButton,&QPushButton::clicked,this,&install_device_infor::on_close_push_button_clicked);

}
void install_device_infor::on_close_push_button_clicked(){
    delete this;
}
install_device_infor::~install_device_infor()
{
    delete ui;
}

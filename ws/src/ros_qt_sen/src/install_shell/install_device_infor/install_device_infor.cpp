#include "install_device_infor.h"
#include "./../ui_install_device_infor.h"

install_device_infor::install_device_infor(QWidget *parent,QString ip_address,QString user_name,QString device_type_URL,QString infor) :
    QWidget(parent),
    ui(new Ui::install_device_infor)
{
    ui->setupUi(this);

    Ip_address = ip_address;
    User_name = user_name;
    Device_type_URL = device_type_URL;

    ui->label_2->setText(ip_address);
    ui->textBrowser->setText(infor);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&install_device_infor::on_open_expolrer_push_button);

    connect(ui->pushButton,&QPushButton::clicked,this,&install_device_infor::on_close_push_button_clicked);
}
void install_device_infor::on_open_expolrer_push_button(){
    QProcess* open_expolrer =new QProcess();
    QString open_expolrer_cmd = "nautilus --browser sftp://"+this->User_name+"@"+this->Ip_address+"/home/"+this->User_name+"/"+Device_type_URL;
    open_expolrer->startDetached(open_expolrer_cmd);
}
void install_device_infor::on_close_push_button_clicked(){
    delete this;
}
install_device_infor::~install_device_infor()
{
    delete ui;
}

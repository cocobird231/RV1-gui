#include "install_option.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include "./../ui_install_option.h"
#include <QDebug>
QJsonDocument install_option_file_json_document;

install_option::install_option(QWidget *parent,QString host_name,QString device,QString pack_name,QString interface,QString ip) :
    QWidget(parent),
    ui(new Ui::install_option)
{
    ui->setupUi(this);
    ui->label_5->setText(host_name);
    ui->lineEdit->setText(interface!="" ? interface:"eth0");
    ui->lineEdit_2->setText(ip!="" ? ip:"dhcp");
    QFile install_option_file("install_option.json");

    if(!install_option_file.open(QIODevice::ReadWrite)) {
    qDebug() << "File open error,the premission may denied.";
    } else {
    qDebug() <<"install_setting File open!";
    }
    QByteArray install_byte = install_option_file.readAll();
    install_option_file_json_document = QJsonDocument::fromJson(install_byte);
    QJsonObject install_option_root = install_option_file_json_document.object();
    if(device =="raspberry pi"){
        QJsonArray rpi_sensor_pack = install_option_root["rpi_sensoers"].toObject()["pack_names"].toArray();
        QJsonArray chassis_pack = install_option_root["chassis"].toObject()["pack_names"].toArray();
        QList<QString> pack_list ;
        for(auto packe_value : rpi_sensor_pack){
            qDebug()<<packe_value.toString();
            pack_list.append(packe_value.toString());
        }
        for(auto packe_value : chassis_pack){
            pack_list.append(packe_value.toString());
        }
        ui->comboBox->addItems(pack_list);
    }
    if(device =="jetson"){
        QJsonArray jetson_sensors_pack = install_option_root["jetson_sensors"].toObject()["pack_names"].toArray();
        QList<QString>  pack_list ;
        for(auto packe_value : jetson_sensors_pack){
            pack_list<<packe_value.toString();
        }
        ui->comboBox->addItems(pack_list);
    }
    ui->comboBox->setCurrentText(pack_name);
}

void install_option::on_save_and_close_push_button_clicked(){

}
void install_option::on_close_push_button_clicked(){

}
void install_option::on_reset_push_button_clicked(){

}

install_option::~install_option()
{
    delete ui;
}

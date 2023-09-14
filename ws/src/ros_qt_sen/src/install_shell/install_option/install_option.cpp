#include "install_option.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include "./../ui_install_option.h"
#include <QDebug>
QJsonDocument install_option_file_json_document;


install_option::install_option(QWidget *parent,QString mac_address,QString device,QString pack_name,QString interface,QString ip) :
    QWidget(parent),
    ui(new Ui::install_option)
{
    ui->setupUi(this);

    this->Mac_address =mac_address;
    this->Device=device;
    this->Pack_name=pack_name;
    this->Interface = interface;
    this->Ip=ip;


 QFile install_file("install_setting.json");
    if(!install_file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error,the premission may denied.";
    } else {
        qDebug() <<"install_setting File open!";
    }
    QByteArray install_setting_file = install_file.readAll();
    QJsonDocument install_setting_json_document = QJsonDocument::fromJson(install_setting_file);
    QJsonObject install_setting_root = install_setting_json_document.object();
    QJsonObject install_config = install_setting_root["install_config"].toObject();
    QJsonObject install_host  =install_config[mac_address].toObject();



    ui->label_5->setText(install_host["host_name"].toString());
    ui->lineEdit->setText(interface!="" ? interface:"eth0");
    ui->lineEdit_2->setText(ip!="" ? ip:"dhcp");
    connect(ui->pushButton,&QPushButton::clicked,this,&install_option::on_close_push_button_clicked);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&install_option::on_save_and_close_push_button_clicked);
    connect(ui->pushButton_3,&QPushButton::clicked,this,&install_option::on_reset_push_button_clicked);

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

    if (Pack_name != "")
    {
        ui->comboBox->setCurrentText(Pack_name);
    }else{
        ui->comboBox->setCurrentIndex(0);
    }
    
}

void install_option::on_save_and_close_push_button_clicked(){
    QString mac_address =this->Mac_address;
    QString Package_Name = ui->comboBox->currentText();
    QString interface = ui->lineEdit->text();
    QString IP = ui->lineEdit_2->text();

    QFile install_file("install_setting.json");
    if(!install_file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error,the premission may denied.";
    } else {
        qDebug() <<"install_setting File open!";
    }
    QByteArray install_setting_file = install_file.readAll();
    QJsonDocument install_setting_json_document = QJsonDocument::fromJson(install_setting_file);
    QJsonObject install_setting_root = install_setting_json_document.object();
    QJsonObject install_config = install_setting_root["install_config"].toObject();
    QJsonObject install_host  =install_config[mac_address].toObject();
    install_host["Package_Name"]=Package_Name;
    install_host["interface"]=interface;
    install_host["IP"]=IP;
    install_config[mac_address] = install_host;
    install_setting_root["install_config"]=install_config;
    install_setting_json_document.setObject(install_setting_root);
    install_file.resize(0);
    install_file.write(install_setting_json_document.toJson());
    install_file.close();
    delete this;
}
void install_option::on_close_push_button_clicked(){
    delete this;

}
void install_option::on_reset_push_button_clicked(){

    QFile install_option_file("install_option.json");
    if(!install_option_file.open(QIODevice::ReadWrite)) {
    qDebug() << "File open error,the premission may denied.";
    } else {
    qDebug() <<"install_setting File open!";
    }
    QByteArray install_byte = install_option_file.readAll();
    install_option_file_json_document = QJsonDocument::fromJson(install_byte);
    QJsonObject install_option_root = install_option_file_json_document.object();
    if(Device =="raspberry pi"){
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
    if(Device =="jetson"){
        QJsonArray jetson_sensors_pack = install_option_root["jetson_sensors"].toObject()["pack_names"].toArray();
        QList<QString>  pack_list ;
        for(auto packe_value : jetson_sensors_pack){
            pack_list<<packe_value.toString();
        }
        ui->comboBox->addItems(pack_list);
    }

    if (Pack_name != "")
    {
        ui->comboBox->setCurrentText(Pack_name);
    }else{
        ui->comboBox->setCurrentIndex(0);
    }
}

install_option::~install_option()
{
    delete ui;
}

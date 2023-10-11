#include "install_process.h"
#include "./../ui_install_process.h"
#include <libssh/libssh.h>
#include <QDebug>
#include <thread>
#include <stdio.h>
#include <iostream>
#include <QScrollBar>
install_process::install_process(QWidget *parent,std::string user_name,std::string Password,std::string host_name,std::string mac_address,std::string ip_address,std::string pack_name,std::string interface,std::string ip,std::string device,bool remove, bool update,bool install ,bool preserve,bool update_depolyment,bool depoly) :
    QWidget(parent),
    ui(new Ui::install_process)
{
    ui->setupUi(this);

    ui->label_2->setText(QString::fromStdString(host_name));
    ui->label_8->setText(QString::fromStdString(mac_address));
    ui->label_9->setText(QString::fromStdString(ip_address));
    ui->label_10->setText(QString::fromStdString(pack_name));
    ui->label_11->setText(QString::fromStdString(interface));
    ui->label_12->setText(QString::fromStdString(ip));
    this->device = device;
    this->remove = remove;
    this->update =update;
    this->install = install;
    this->preserve = preserve;
    this->update_depolyment = update_depolyment;

    // timmer.setSingleShot(true);
    QObject::connect(&timmer, &QTimer::timeout,this, &install_process::set_text_broswer);
    connect(ui->pushButton,&QPushButton::clicked,this,&install_process::on_close_push_button_clicked);
    timmer.start(2000);
    if(!depoly){
    std::shared_ptr<std::thread> install_mission_threads = std::make_shared<std::thread>(std::bind(&install_process::install_misson,this,user_name,Password,ip_address,pack_name,interface,ip,device));
    install_mission_threads->detach();
    }else{
    std::shared_ptr<std::thread> depoly_threads = std::make_shared<std::thread>(std::bind(&install_process::depoly,this,user_name,Password,ip_address,pack_name,interface,ip,device));
    depoly_threads->detach();
    }

}
void install_process::on_close_push_button_clicked(){
    delete this;
}
void install_process::set_text_broswer( ){
    ui->textBrowser->setText(this->ssh_infor);

    ui->textBrowser->verticalScrollBar()->setValue(ui->textBrowser->verticalScrollBar()->maximum());
}

void install_process::depoly(std::string user_name,std::string Password,std::string ip_address,std::string pack_name,std::string interface,std::string ip,std::string device){

    qDebug()<<QString::fromStdString(user_name);
    int rc;
    int port = 22;
    char buffer[256];
    int nbytes = 0;
    int verbosity = SSH_LOG_PROTOCOL;
    // Open session and set options
    ssh_session my_ssh_session = ssh_new();
    
    if (my_ssh_session == NULL)
        return;
    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST,ip_address.c_str());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);
    ssh_options_set(my_ssh_session,SSH_OPTIONS_PASSWORD_AUTH,Password.c_str());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER,user_name.c_str());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_CIPHERS_C_S,"aes128-ctr");
    ssh_options_set(my_ssh_session,SSH_OPTIONS_TIMEOUT_USEC,"10");
    rc = ssh_connect(my_ssh_session);
    if (rc != SSH_OK)  
    {
        ssh_free(my_ssh_session);
        return ;
    }
    qDebug()<<"Auth";
    rc = ssh_userauth_password(my_ssh_session, user_name.c_str(), Password.c_str());

    qDebug()<<"rc";
    if (rc != SSH_AUTH_SUCCESS)  
    {
        ssh_free(my_ssh_session);
        qDebug()<<"Auth error";
        return;
    }
    qDebug()<<"channel";


    QList<QString> depoly_string;

    if(device =="raspberry pi"){
        depoly_string.append("./ros2_docker/install.sh -rm");
        depoly_string.append("sudo rm -rf ros2_docker");

        if(pack_name =="py_chassis"){
        depoly_string.append("curl -fsSL ftp://61.220.23.239/rv-11/get-chassis-install.sh | bash");
        }else{
        depoly_string.append("curl -fsSL ftp://61.220.23.239/rv-11/get-rpi-sensors-install.sh | bash");
        }
    }
    if(device =="jetson"){
        depoly_string.append("./jetson_sensors/install.sh -rm");
        depoly_string.append("curl -fsSL ftp://61.220.23.239/rv-11/get-jetson-sensors-install.sh | bash");
    }



    QByteArray ssh_Qbyte;
    QByteArray ssh_merge_qbyte;
    QString ssh_infor_string;
for(QString depoly_ssh_command:depoly_string){

    ssh_channel channel = ssh_channel_new(my_ssh_session);
    if (channel == NULL){
        qDebug()<<"channel is missing pointer";
        return;
    }
        qDebug()<<" open session";
    rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK)
    {
        qDebug()<<"channel get error";
        ssh_free(my_ssh_session);
        ssh_channel_free(channel);
        return ;
    }
    std::string  depoly_ssh_command_string = depoly_ssh_command.toStdString();
    qDebug()<<"ssh request command is _"+QString::fromStdString(depoly_ssh_command_string)+" _";
    rc = ssh_channel_request_exec(channel, depoly_ssh_command_string.c_str());

    if (rc != SSH_OK)
    {
        qDebug()<<"channel request error.";
        qDebug()<<"ssh request command is _"+QString::fromStdString(depoly_ssh_command_string)+" _";
        ssh_channel_close(channel);
        ssh_channel_free(channel);
    }

  while (ssh_channel_is_open(channel) &&! ssh_channel_is_eof(channel))
    {
        qDebug()<<"ssh_channel_is_open(channel) &&! ssh_channel_is_eof(channel)";
        // ssh_Qbyte = QByteArray::fromRawData(buffer,nbytes);
        // ssh_merge_qbyte.append(ssh_Qbyte);
        // nbytes =  ssh_channel_read(channel, buffer, sizeof(buffer), 0);
        // ssh_infor_string=ssh_merge_qbyte;
        nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
        if (nbytes <= 0)
            break;
        
        ssh_infor_string += QByteArray::fromRawData(buffer,nbytes);
        this->ssh_infor =ssh_infor_string;
    }
    ssh_infor_string=ssh_merge_qbyte;
}

    this->ssh_infor=this->ssh_infor+"\n Done.\n";
    qDebug()<<QString("Done"); 
}

void install_process::install_misson(std::string user_name,std::string Password,std::string ip_address,std::string pack_name,std::string interface,std::string ip,std::string device){

    qDebug()<<QString::fromStdString(user_name);
    int rc;
    int port = 22;
    char buffer[256];
    int nbytes = 0;
    int verbosity = SSH_LOG_PROTOCOL;
    // Open session and set options
    ssh_session my_ssh_session = ssh_new();
    
    if (my_ssh_session == NULL)
        return;
    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST,ip_address.c_str());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);
    ssh_options_set(my_ssh_session,SSH_OPTIONS_PASSWORD_AUTH,Password.c_str());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER,user_name.c_str());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_CIPHERS_C_S,"aes128-ctr");
    ssh_options_set(my_ssh_session,SSH_OPTIONS_TIMEOUT_USEC,"10");
    rc = ssh_connect(my_ssh_session);
    if (rc != SSH_OK)  
    {
        ssh_free(my_ssh_session);
        return ;
    }
    qDebug()<<"Auth";
    rc = ssh_userauth_password(my_ssh_session, user_name.c_str(), Password.c_str());

    qDebug()<<"rc";
    if (rc != SSH_AUTH_SUCCESS)  
    {
        ssh_free(my_ssh_session);
        qDebug()<<"Auth error";
        return;
    }
    qDebug()<<"channel";

    ssh_channel channel = ssh_channel_new(my_ssh_session);
    if (channel == NULL){
        qDebug()<<"channel is missing pointer";
        return;
    }
        qDebug()<<" open session";
    rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK)
    {
        qDebug()<<"channel get error";
        ssh_free(my_ssh_session);
        ssh_channel_free(channel);
        return ;
    }



    std::string ssh_command ="";


    QByteArray ssh_Qbyte;
    QByteArray ssh_merge_qbyte;
    QString ssh_infor_string;
        if(device=="jetson"){

        //sudo 
        std::string sudo_session = "echo "+Password+" | sudo -S ls -la";
        qDebug()<<QString("ssh_channel_read get-jetson-install"); 

        ssh_command= ". ~/jetson_sensors/install.sh";
        std::string shell_temp_command = "";
        if(this->update_depolyment){
            shell_temp_command = shell_temp_command+" --upgrade ";
        }
        if (this->remove)
        {
            shell_temp_command = shell_temp_command+" -rm ";
        }
        if (this->update)
        {
            shell_temp_command = shell_temp_command+" -u ";
        }
        if (this->install)
        {
            if(pack_name != "auto"){
                shell_temp_command = shell_temp_command+" -i "+pack_name+" --interface "+interface +" --ip "+ip;

            }else{
                shell_temp_command = shell_temp_command+" -i "+pack_name;

            }
        }
        if (this->preserve)
        {
            shell_temp_command = shell_temp_command+" -p ";
        }
        ssh_command = sudo_session+"\n"+ssh_command +shell_temp_command;
        if(ssh_channel_is_open(channel)){
            qDebug()<<"channel ssh_channel_is_open error.";


        }

        rc = ssh_channel_request_exec(channel, ssh_command.c_str());

        if (rc != SSH_OK)
        {
            qDebug()<<"channel request error.";
            qDebug()<<"ssh request command is _"+QString::fromStdString(ssh_command)+" _";
            ssh_channel_close(channel);
            ssh_channel_free(channel);

        }
        qDebug()<<QString("ssh_channel_read install"); 
    }


    if(device=="raspberry pi"){

 
        qDebug()<<QString("ssh_channel_read get-rpi-sensors-install"); 

        ssh_command= ". ~/ros2_docker/install.sh";
        std::string shell_temp_command = "";
        if(this->update_depolyment){
            shell_temp_command = shell_temp_command+" --upgrade ";
        }
        if (this->remove)
        {
            shell_temp_command = shell_temp_command+" -rm ";
        }
        if (this->update)
        {
            shell_temp_command = shell_temp_command+" -u ";
        }
        if (this->install)
        {
            if(pack_name != "auto"){
                shell_temp_command = shell_temp_command+" -i "+pack_name+" --interface "+interface +" --ip "+ip;

            }else{
                shell_temp_command = shell_temp_command+" -i "+pack_name;
            }
        }
        if (this->preserve)
        {
            shell_temp_command = shell_temp_command+" -p ";
        }
        ssh_command = ssh_command +shell_temp_command;
        qDebug()<<QString::fromStdString(ssh_command);
        rc = ssh_channel_request_exec(channel, ssh_command.c_str());

        if (rc != SSH_OK)
        {
            qDebug()<<"channel request error.";
            qDebug()<<"ssh request command is _"+QString::fromStdString(ssh_command)+" _";
            ssh_channel_close(channel);
            ssh_channel_free(channel);
        }
        qDebug()<<QString("ssh_channel_read install"); 
    }

  while (ssh_channel_is_open(channel) &&! ssh_channel_is_eof(channel))
    {
        ssh_Qbyte = QByteArray::fromRawData(buffer,nbytes);
        ssh_merge_qbyte.append(ssh_Qbyte);
        nbytes =  ssh_channel_read(channel, buffer, sizeof(buffer), 0);
        ssh_infor_string=ssh_merge_qbyte;
        if (nbytes <= 0)
        {
            break;
        }
        
        // qDebug().noquote()<<ssh_infor_string;
        this->ssh_infor =ssh_infor_string;
        // chassis
        if(ssh_infor_string.contains("Terminal=true")){
            ssh_channel_close(channel);
            ssh_channel_free(channel);
        }
        // respi sensor
        if(ssh_infor_string.contains("/etc/dhcpcd.conf recovered")){
            ssh_channel_close(channel);
            ssh_channel_free(channel);
        }
        //jetson
        if(ssh_infor_string.contains("Comment=Start ROS2 Application")){
            ssh_channel_close(channel);
            ssh_channel_free(channel);
        }
    }
    ssh_infor_string=ssh_merge_qbyte;
    qDebug().noquote()<<ssh_infor_string;
    this->ssh_infor=this->ssh_infor+"\n Done.\n";
    qDebug()<<QString("Done"); 
}


void install_process::setText(QString contants){

    ui->textBrowser->setText(contants);
}
install_process::~install_process()
{
    delete ui;
}

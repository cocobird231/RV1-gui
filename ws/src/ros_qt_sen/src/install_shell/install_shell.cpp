#include "install_shell.h"
#include <QDebug>
#include <stdio.h>
#include <iostream>
#include <string.h> 
#include <iostream>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QHostAddress>
#include <QtNetwork>
#include <thread>
#include <QMessageBox>
#include "install_device_infor/install_device_infor.h"
#include "install_process/install_process.h"
#include "install_option/install_option.h"
QList<QNetworkAddressEntry> entryList;
QString selected_self_IP;
QJsonDocument install_setting_json_document ;
QList<QString> is_opened_host_address;
QList<QString> is_opened_host_name;
QList<QString> is_opened_host;
QMap<QString ,QString> is_opened_host_map;
QStringList host_list;
QList<QString> subnet_list;

QListWidgetItem* host_name_item =new QListWidgetItem;
QListWidgetItem* mission_install_item ;

std::shared_ptr<QListWidgetItem> online_device_item ;


std::shared_ptr<std::thread> the_thread;

 install_shell::install_shell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::install_shell)
{
    ui->setupUi(this);
    // ui->pushButton_6->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_7->setEnabled(false);

    connect(ui->pushButton, &QPushButton::clicked, this, &install_shell::on_Interface_Update_PushButtun_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &install_shell::on_Interface_Choose_PushButtun_clicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &install_shell::on_update_host_information_push_button_clicked);
    
    //connect(ui->listWidget,&QListWidget::currentItemChanged,this,&install_shell::on_current_online_device_changed);
    // connect(ui->listWidget,&QListWidget::itemClicked,this,&install_shell::on_current_online_device_changed);

    // connect(ui->listWidget_2,&QListWidget::currentItemChanged,this,&install_shell::on_current_mission_install_changed);

    connect(ui->listWidget_3,&QListWidget::itemClicked,this,&install_shell::on_current_host_information_changed);

    connect(ui->pushButton_6,&QPushButton::clicked,this,&install_shell::on_reboot_push_button_clicked);
    connect(ui->pushButton_7,&QPushButton::clicked,this,&install_shell::on_delet_host_information_push_button_clicked);
    connect(ui->pushButton_3,&QPushButton::clicked,this,&install_shell::on_host_check_infor_push_button_clicked);
    connect(ui->pushButton_4,&QPushButton::clicked,this,&install_shell::on_install_option_push_button_clicked);
    connect(ui->pushButton_10,&QPushButton::clicked,this,&install_shell::on_install_mission_dispatch_push_button_clicked);
    connect(ui->pushButton_8,&QPushButton::clicked,this,&install_shell::on_add_mission_pushButton_clicked);
    connect(ui->pushButton_9,&QPushButton::clicked,this,&install_shell::on_delet_mission_pushButton_clicked);
    connect(ui->pushButton_11,&QPushButton::clicked,this,&install_shell::on_save_default_user_push_button);


    QFile install_file("install_setting.json");
    if(!install_file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error,the premission may denied.";
    } else {
        qDebug() <<"install_setting File open!";
    }
    QByteArray install_setting_file = install_file.readAll();
    install_setting_json_document = QJsonDocument::fromJson(install_setting_file);
    QJsonObject root = install_setting_json_document.object();

    if(!(root["default_interface"].toString()=="" || root["default_ip"].toString()==""|| root["default_net_mask"].toString()=="")){
        ui->comboBox->addItem("Interface: "+root["default_interface"].toString()+"/ IP Address: "+root["default_ip"].toString()+"/ NetMask: "+root["default_net_mask"].toString());
        install_file.close();
        
        QList<QNetworkInterface> interface_list = QNetworkInterface::allInterfaces();
        foreach(QNetworkInterface interface,interface_list) 
        {
            entryList= interface.addressEntries();
            foreach(QNetworkAddressEntry entry,entryList)
            {
                //IPV6 drop
                if(entry.netmask().toString().contains("f"))
                    continue;
                QString temp_default_interface ="Interface: "+root["default_interface"].toString()+"/ IP Address: "+root["default_ip"].toString()+"/ NetMask: "+root["default_net_mask"].toString();
                QString temp_interface = "Interface: "+interface.name()+"/ IP Address: "+entry.ip().toString()+"/ NetMask: "+entry.netmask().toString();
                if(!(temp_default_interface ==temp_interface)){
                    ui->comboBox->addItem("Interface: "+interface.name()+"/ IP Address: "+entry.ip().toString()+"/ NetMask: "+entry.netmask().toString());
                }else{
                    ui->comboBox->setCurrentText(temp_default_interface);
                }
            }
        }
            QFile host_list_file("host_list.json");
            if(!host_list_file.open(QIODevice::ReadWrite)) {
                qDebug() << "ip_mapping open error,the premission may denied.";
            } else {
                qDebug() <<"ip_mapping File open!";
            }
            QByteArray host_list_file_BA_file = host_list_file.readAll();
            QJsonDocument host_list_doc = QJsonDocument::fromJson(host_list_file_BA_file);
            QJsonObject root = host_list_doc.object();
            QJsonArray host_name_json_list = root["host_name_array"].toArray();
            for(auto host_name_in_json : host_name_json_list){
                ui->listWidget_3->addItem(host_name_in_json.toString());
            }
            ui->listWidget_3->setCurrentRow(0);
            host_list_file.close();
    }
    ui->lineEdit_5->setText(root["default_user_name"].toString());
    ui->lineEdit_6->setText(root["default_password"].toString());

}

void install_shell::on_reboot_push_button_clicked(){

    int task_count = ui->listWidget_2->count();
    qDebug()<<QString(task_count);
    std::string* mac_array =new std::string[task_count];
    std::string* ip_address_array =new std::string[task_count];
    std::string* Device_array =new std::string[task_count];
    std::string* host_name_array =new std::string[task_count];
    std::string* user_name_array =new std::string[task_count];
    std::string* Password_array =new std::string[task_count];
    std::string* pack_name_array =new std::string[task_count];
    std::string* interface_array =new std::string[task_count];
    std::string* ip_array =new std::string[task_count];


    if(task_count ==0){
        return;
    }
    QFile install_file("install_setting.json");
    if(!install_file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error,the premission may denied.";
    } else {
        qDebug() <<"install_setting File open!";
    }
    QByteArray install_setting_file = install_file.readAll();
    install_setting_json_document = QJsonDocument::fromJson(install_setting_file);
    QJsonObject root = install_setting_json_document.object();
    QJsonObject install_config = root["install_config"].toObject();
    
    for(int i=0;i<task_count;i++){
        QListWidgetItem* listwidget_current = ui->listWidget_2->item(i);
        mac_array[i] =  listwidget_current->text().split("/")[1].toStdString();
        QJsonObject host_object=install_config[ QString::fromStdString(mac_array[i])].toObject();
        if (!install_config.contains(QString::fromStdString(mac_array[i])))
        {
            qDebug()<<QString("install_config no mac in list.");
            return;
        }
        host_name_array[i] = host_object["host_name"].toString().toStdString();
        ip_address_array[i] = host_object["ip_address"].toString().toStdString();
        Device_array[i] = host_object["device"].toString().toStdString();



        user_name_array[i]=host_object["user"].toString().toStdString();
        Password_array[i]=host_object["password"].toString().toStdString();
                qDebug()<<QString("Def");

        qDebug()<<QString::fromStdString(user_name_array[i]) ;
        qDebug()<<QString::fromStdString(Password_array[i]);

        if (user_name_array[i]==""||Password_array[i]=="")
        {
            user_name_array[i]=root["default_user_name"].toString().toStdString();
            Password_array[i] =root["default_password"].toString().toStdString();
        qDebug()<<QString("De2f");
        qDebug()<<QString::fromStdString(user_name_array[i]) ;
        qDebug()<<QString::fromStdString(Password_array[i]);

        }
        pack_name_array[i]=host_object["Package_Name"].toString().toStdString();
        interface_array[i]=host_object["interface"].toString().toStdString();
        ip_array[i]=host_object["IP"].toString().toStdString();

    }
    install_file.close();
    qDebug() <<"install_mission_threads";
    std::shared_ptr<std::thread>* reboot_threads = new std::shared_ptr<std::thread>[task_count];
    for(int i=0;i<task_count;i++){
        std::string host_name_ =host_name_array[i];
        std::string mac_address =mac_array[i];
        std::string ip_address =ip_address_array[i];
        std::string device =Device_array[i];

        std::string user_name_ =user_name_array[i];
        std::string Password_ =Password_array[i];
        std::string pack_name_ =pack_name_array[i];
        std::string interface_ =interface_array[i];
        std::string ip_ =ip_array[i];


        qDebug()<<"test for install";
        qDebug()<<QString::fromStdString(host_name_);
        // install_process* Install_process = new install_process(nullptr,user_name_,Password_,host_name_,mac_address,ip_address,pack_name_,interface_,ip_,device,remove_,update_,install_,preserve_);
        // Install_process->show();
        reboot_threads[i]= std::make_shared<std::thread>(std::bind(&install_shell::reboot_device,this,ip_address,user_name_,Password_));

    }
    for(int i =0;i<task_count;i++){
        reboot_threads[i]->detach();
    }
}

void install_shell::on_save_default_user_push_button(){

    QFile install_file("install_setting.json");
    if(!install_file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error,the premission may denied.";
    } else {
        qDebug() <<"install_setting File open!";
    }
    QByteArray install_setting_file = install_file.readAll();
    install_setting_json_document = QJsonDocument::fromJson(install_setting_file);
    QJsonObject root = install_setting_json_document.object();
    root["default_user_name"] = ui->lineEdit_5->text();
    root["default_password"] = ui->lineEdit_6->text();
    install_setting_json_document.setObject(root);
    install_file.resize(0);
    install_file.write(install_setting_json_document.toJson());
    install_file.close();


}
void install_shell::on_Interface_Update_PushButtun_clicked(){

    QList<QNetworkInterface> interface_list = QNetworkInterface::allInterfaces();
    ui->comboBox->clear();
    foreach(QNetworkInterface interface,interface_list) 
    {
        entryList= interface.addressEntries();
        foreach(QNetworkAddressEntry entry,entryList)
        {
        //IPV6 drop
        if(entry.netmask().toString().contains("f"))
            continue;
        // qDebug()<<"IP Address: "<<entry.ip().toString(); 
        // qDebug()<<"Netmask: "<<entry.netmask().toString(); 
        // qDebug()<<"Broadcast: "<<entry.broadcast().toString();
        if (entry.ip().toString()=="127.0.0.1")
        {
            continue;
        }
        ui->comboBox->addItem("Interface: "+interface.name()+"/ IP Address: "+entry.ip().toString()+"/ NetMask: "+entry.netmask().toString());

        
        }
    }

}
void install_shell::on_Interface_Choose_PushButtun_clicked(){
        qDebug()<<ui->comboBox->currentText();
        if(ui->comboBox->currentText() ==""){
            return;
        }
        if (ui->comboBox->currentText().contains("127.0.0.1"))
        {
            return;
        }
        
        ui->pushButton_2->setEnabled(false);
        int list_count=ui->listWidget->count();

        for (int i = list_count - 1; i >0; --i) {
          ui->listWidget->takeItem(i);
        }
        is_opened_host_address.clear();
        is_opened_host_name.clear();
        is_opened_host.clear();
        is_opened_host_map.clear();
        QString the_item_select = ui->comboBox->currentText();
        the_item_select= the_item_select.remove(" ");
        the_item_select = the_item_select.trimmed();
        QList<QString> select_prop =the_item_select.split("/");
        QString interface_string = select_prop[0].split(":")[1];
        QString IP_address_string = select_prop[1].split(":")[1];
        selected_self_IP = IP_address_string;
        QString Mask = select_prop[2].split(":")[1];

        QJsonObject root = install_setting_json_document.object();
        root["default_interface"] = interface_string;
        root["default_ip"] = IP_address_string;
        root["default_net_mask"] = Mask;
        install_setting_json_document.setObject(root);

        QFile install_file("install_setting.json");
        if(!install_file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error,the premission may denied.";
        } else {
        qDebug() <<"install_setting File open!";
        }
        install_file.resize(0);
        install_file.write(install_setting_json_document.toJson());
        install_file.close();

        subnet_list = getSubnetList(IP_address_string,Mask);
        the_thread = std::make_shared<std::thread>(std::bind(&install_shell::icmp_thread_patch,this,subnet_list));
        the_thread->detach();
}

QList<QString> install_shell::getSubnetList(const QString& ipAddress, const QString& subnetMask) {
    QList<QString> subnetList;

    QHostAddress networkAddress(ipAddress);
    QHostAddress maskAddress(subnetMask);

    quint32 networkAddressInt = networkAddress.toIPv4Address();
    quint32 maskAddressInt = maskAddress.toIPv4Address();

    // Calculate the network address by applying the subnet mask
    quint32 subnetStart = networkAddressInt & maskAddressInt;
    // Calculate the number of addresses in the subnet
    int numAddresses = ~maskAddressInt;

    // Add each subnet address to the list
    for (int i = 1; i < numAddresses ; ++i) {
        quint32 subnet = subnetStart + i;
        QHostAddress subnetAddress(subnet);
        subnetList.append(subnetAddress.toString());
    }

    return subnetList;
}
install_shell::~install_shell()
{   
 
    delete ui;
}


void install_shell::check_ssh_has_open(QString host_name,QString user_name){


    int rc;
    int port = 22;
    int verbosity = SSH_LOG_PROTOCOL;
    // Open session and set options
    ssh_session my_ssh_session = ssh_new();
    if (my_ssh_session == NULL)
        exit(-1);
    
    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST,host_name.toLocal8Bit().data());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER,user_name.toLocal8Bit().data());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_CIPHERS_C_S,"aes128-ctr");
    ssh_options_set(my_ssh_session,SSH_OPTIONS_TIMEOUT_USEC,"10");
    rc = ssh_connect(my_ssh_session);
    if (rc != SSH_OK)  
    {
        qDebug()<< "Error: "+ QString(ssh_get_error(my_ssh_session)); //HERE IS WHERE I GET THE ERROR 
        ssh_free(my_ssh_session);
    }else{
        is_opened_host_address.append(host_name);

    }
}
// void install_shell::on_current_online_device_changed(QListWidgetItem * item){
//     online_device_item =std::make_shared<QListWidgetItem>(*item);
    
// }
void install_shell::on_add_mission_pushButton_clicked(){


    if (ui->listWidget==nullptr)
    {
        return;
    }
    
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    if (items.count()==0)
    {
    QMessageBox mission_install_is_empty;
    mission_install_is_empty.setText("the device install list has not been selected any item.");
    mission_install_is_empty.exec();
    return;
    }else if(items.count()>=2){
        QMessageBox mission_install_is_empty;
        mission_install_is_empty.setText("mutiple select item.");
        mission_install_is_empty.exec();
    return; 
    }

    foreach(QListWidgetItem* item, items)
    {
        QString add_row_string = item->text();
        QString add_string = item->text();

        QList<QListWidgetItem *> find_string_items=ui->listWidget_2->findItems(add_string,Qt::MatchCaseSensitive);
        qDebug()<<QString(find_string_items.length());
        if(find_string_items.length()>=1){
            QMessageBox mission_is_in_list;
            mission_is_in_list.setText("the mission list has contains the Item.");
            mission_is_in_list.exec();
            return;
        }
        ui->listWidget_2->addItem(add_string);
    }


    
}

void install_shell::on_delet_mission_pushButton_clicked(){


QList<QListWidgetItem*> items = ui->listWidget_2->selectedItems();
if (items.count()==0)
{
QMessageBox mission_install_is_empty;
mission_install_is_empty.setText("the device install mission list has not been selected any item.");
mission_install_is_empty.exec();
return;
}
foreach(QListWidgetItem * item, items)
{
    delete ui->listWidget_2->takeItem(ui->listWidget_2->row(item));
}


// if (ui->listWidget_2->count()>1)
// {

//     delete mission_install_item;
// }else{
//     ui->listWidget_2 = new QListWidget;
// }


}
void install_shell::on_current_mission_install_changed(QListWidgetItem * item){
mission_install_item =item;
qDebug()<<item->text();

}
void install_shell::on_host_check_infor_push_button_clicked(){
    if (ui->listWidget==nullptr)
    {
        return;
    }
    
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    if (items.count()==0)
    {
    QMessageBox mission_install_is_empty;
    mission_install_is_empty.setText("the device install list has not been selected any item.");
    mission_install_is_empty.exec();
    return;
    }else if(items.count()>=2){
        QMessageBox mission_install_is_empty;
        mission_install_is_empty.setText("mutiple select item.");
        mission_install_is_empty.exec();
    return; 
    }

    foreach(QListWidgetItem* item, items)
    {
        QString online_Device_text = item->text();
        QString mac_address=item->text().split("/")[1];
        QString host_name=item->text().split("/")[0];
        std::string ip_address = item->text().split("/")[2].toStdString();

        std::string device_type = "";
        QFile host_list_file("host_list.json");
        if(!host_list_file.open(QIODevice::ReadWrite)) {
        qDebug() << "ip_mapping open error,the premission may denied.";
        } else {
        qDebug() <<"ip_mapping File open!";
        }
        QByteArray host_list_file_BA_file = host_list_file.readAll();
        QJsonDocument host_list_doc = QJsonDocument::fromJson(host_list_file_BA_file);
        QJsonObject root = host_list_doc.object();
        QJsonArray host_name_json_list = root["host_name_array"].toArray();
        QJsonObject contant=root["mac_list"].toObject();
        QString DNS_replace = "";
        // if (online_Device_text.contains("/"))
        // {
        //     DNS_replace=online_Device_text.split("/")[0];
        //     hostname= online_Device_text.split("/")[1].toStdString();
        //     for(int i =0;i<host_name_json_list.size();i++){
        //         QJsonObject host_object =contant[host_name_json_list[i].toString()].toObject();
        //         std::string host_ip = host_object["ip_address"].toString().toStdString();
        //         if (host_ip==hostname)
        //         {
        //             device_type=host_object["Device"].toString().toStdString();
        //         }
        //     }
        // }else{
            // hostname= online_Device_text.split(":")[0].toStdString();
        // }
        //need load host and user config in file.
        QFile install_file("install_setting.json");
        if(!install_file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error,the premission may denied.";
        } else {
        qDebug() <<"install_setting File open!";
        }
        QByteArray install_setting_file = install_file.readAll();
        install_setting_json_document = QJsonDocument::fromJson(install_setting_file);
        QJsonObject install_root = install_setting_json_document.object();
        QJsonObject install_config = install_root["install_config"].toObject();
        QJsonObject host;
        // if (DNS_replace !="")
        // {
        //     host = install_config[DNS_replace].toObject();

        // }else{
            host = install_config[mac_address].toObject();
            qDebug()<<mac_address;

        // }
        
        std::string user = host["user"].toString().toStdString();
        std::string password = host["password"].toString().toStdString();

        if(user =="" ||password ==""){
            user =install_root["default_user_name"].toString().toStdString();
            password = install_root["default_password"].toString().toStdString();
            qDebug()<<QString::fromStdString(user);
        }
        device_type = host["device"].toString().toStdString();

        install_setting_json_document.setObject(root);

        install_file.close();
        qDebug()<<QString("test for ssh");
        qDebug()<<QString::fromStdString(ip_address);
        qDebug()<<QString::fromStdString(user);
        qDebug()<<QString::fromStdString(password);
        qDebug()<<QString::fromStdString(device_type);

        check_ssh_device_information(ip_address,user,password,device_type);
    }
}
void install_shell::reboot_device(std::string ip_address ,std::string user_name,std::string Password){

    int rc;
    int port = 22;
    char buffer[256];
    int nbytes;
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
    rc = ssh_userauth_password(my_ssh_session, user_name.c_str(), Password.c_str());
    if (rc != SSH_AUTH_SUCCESS)  
    {
        ssh_free(my_ssh_session);
        QMessageBox exception_ssh;
        exception_ssh.setText("Auth Error");
        exception_ssh.exec();
        return;
    }

    ssh_channel channel = ssh_channel_new(my_ssh_session);
    if (channel == NULL)
        return;
    rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK)
    {
        ssh_free(my_ssh_session);
        ssh_channel_free(channel);
        return ;
    }
    rc = ssh_channel_request_exec(channel, "sudo reboot");

    if (rc != SSH_OK)
    {
    ssh_channel_close(channel);
    ssh_channel_free(channel);
    }
    nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
    QByteArray ssh_Qbyte;
    QByteArray ssh_merge_qbyte;
    while (nbytes > 0)
    {
        ssh_Qbyte = QByteArray::fromRawData(buffer,nbytes);
        ssh_merge_qbyte.append(ssh_Qbyte);
        nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
    }
    QString ssh_infor_string=ssh_merge_qbyte;
    qDebug().noquote()<<ssh_infor_string;
    if (nbytes < 0)
    {
    ssh_channel_close(channel);
    ssh_channel_free(channel);
        qDebug()<< "Error: "+ QString(ssh_get_error(my_ssh_session)); //HERE IS WHERE I GET THE ERROR 
    }

    ssh_disconnect(my_ssh_session);
    ssh_free(my_ssh_session);

}

void install_shell::check_ssh_device_information(std::string ip_address ,std::string user_name,std::string Password,std::string device_type){


    int rc;
    int port = 22;
    char buffer[256];
    int nbytes;
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
    rc = ssh_userauth_password(my_ssh_session, user_name.c_str(), Password.c_str());
    if (rc != SSH_AUTH_SUCCESS)  
    {
        ssh_free(my_ssh_session);
        QMessageBox exception_ssh;
        exception_ssh.setText("Auth Error");
        exception_ssh.exec();
        return;
    }

    ssh_channel channel = ssh_channel_new(my_ssh_session);
    if (channel == NULL)
        return;
    rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK)
    {
        ssh_free(my_ssh_session);
        ssh_channel_free(channel);
        return ;
    }
    QString Device_access_url ="";
    //raspberry pi check ros2_docker
    if(device_type =="raspberry pi"){
        Device_access_url ="ros2_docker/common.yaml";
        rc = ssh_channel_request_exec(channel, "cat ros2_docker/common.yaml");
    }else if (device_type =="jetson")
    {
        Device_access_url ="jetson_sensors/common.yaml";
        rc = ssh_channel_request_exec(channel, "cat jetson_sensors/common.yaml");
    }else if (device_type =="ADLink")
    {
        Device_access_url ="ros2_ws/.modulesettings";

        rc = ssh_channel_request_exec(channel, "cat ros2_ws/.modulesettings");
    }else{
        QMessageBox exception_ssh;
        exception_ssh.setText("請先定義裝置類型");
        exception_ssh.exec();
        return;
    }
    

    if (rc != SSH_OK)
    {
    ssh_channel_close(channel);
    ssh_channel_free(channel);
    }
    nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
    QByteArray ssh_Qbyte;
    QByteArray ssh_merge_qbyte;
    while (nbytes > 0)
    {
        ssh_Qbyte = QByteArray::fromRawData(buffer,nbytes);
        ssh_merge_qbyte.append(ssh_Qbyte);
        nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
    }
    QString ssh_infor_string=ssh_merge_qbyte;
    qDebug().noquote()<<ssh_infor_string;
    //check install information
    if(ssh_infor_string !=""){
    install_device_infor* dialog_device_info = new install_device_infor(nullptr,QString::fromStdString(ip_address),QString::fromStdString(user_name),Device_access_url,ssh_infor_string);
    dialog_device_info->show();
    }else{
        QMessageBox exception_ssh;
        exception_ssh.setText("未安裝任何東西");
        exception_ssh.exec();
    }


    if (nbytes < 0)
    {
    ssh_channel_close(channel);
    ssh_channel_free(channel);
        qDebug()<< "Error: "+ QString(ssh_get_error(my_ssh_session)); //HERE IS WHERE I GET THE ERROR 
    }

    ssh_disconnect(my_ssh_session);
    ssh_free(my_ssh_session);


}
void install_shell::check_icmp_has_open(QString host_name){
            QProcess ping_process;

            QString command_string = "ping "+host_name+" -c 1 -w 1 -W 1 ";
            ping_process.start(command_string,QIODevice::ReadOnly);
            ping_process.waitForFinished(-1);
            QString result = QString::fromLocal8Bit(ping_process.readAllStandardOutput());
            ping_process.kill();
            if(result.contains("ttl")){
                is_opened_host_address.append(host_name);

                QProcess mac_address_process;
                std::string search_mac_address_command_string = "arp -a "+host_name.toStdString();
                QString QS_search_mac_address_command_string = QString::fromStdString(search_mac_address_command_string);
                qDebug()<<QS_search_mac_address_command_string;

                mac_address_process.start(QS_search_mac_address_command_string,QIODevice::ReadOnly);
                mac_address_process.waitForFinished(-1);
                QString mac_result = QString::fromLocal8Bit(mac_address_process.readAllStandardOutput());
                qDebug()<<mac_result;
                if(mac_result.contains("no match found")){
                    return;
                }
                mac_result = mac_result.split("at ")[1].split(" [")[0];
                mac_address_process.kill();
                qDebug()<<mac_result;

                is_opened_host_address.append(host_name);
                // Host Name
                QProcess dns_process;
                QString dns_command_string = "nslookup "+host_name;
                dns_process.start(dns_command_string,QIODevice::ReadOnly);
                dns_process.waitForFinished(-1);
                QString dns_result = QString::fromLocal8Bit(dns_process.readAllStandardOutput());
                dns_process.kill();


                if(dns_result.contains("name = ")){

                    QFile host_list_file("host_list.json");
                    if(!host_list_file.open(QIODevice::ReadWrite)) {
                    qDebug() << "ip_mapping open error,the premission may denied.";
                    } else {
                    qDebug() <<"ip_mapping File open!";
                    }
                    QByteArray host_list_file_BA_file = host_list_file.readAll();
                    QJsonDocument host_list_doc = QJsonDocument::fromJson(host_list_file_BA_file);
                    QJsonObject root = host_list_doc.object();
                    QJsonArray host_name_json_list = root["host_name_array"].toArray();
                    QJsonObject contant=root["mac_list"].toObject();
                    QJsonObject currentItem_object =contant[mac_result].toObject();

                    QFile install_file("install_setting.json");
                    if(!install_file.open(QIODevice::ReadWrite)) {
                    qDebug() << "File open error,the premission may denied.";
                    } else {
                    qDebug() <<"install_setting File open!";
                    }
                    QByteArray install_byte = install_file.readAll();
                    install_setting_json_document = QJsonDocument::fromJson(install_byte);
                    QJsonObject install_root = install_setting_json_document.object();
                    QJsonObject install_config = install_root["install_config"].toObject();
                    QJsonObject host = install_config[mac_result].toObject();
                    QString message_type = host["message_type"].toString();

                    install_file.close();


                    QString DNS_host_name =dns_result.split("name = ")[1].split(".")[0];
                    is_opened_host_name.append(DNS_host_name+"/"+mac_result+"/"+host_name+"/"+message_type);
                    is_opened_host.append(DNS_host_name+"/"+mac_result+"/"+host_name+"/"+message_type);
                    QString function_in_call_host_name  = host_name;
                    is_opened_host_map[DNS_host_name]=function_in_call_host_name;

                }else{
                    //compares host_list.json and fix display Item
                    //and update value with is_opne_host map
                    QFile host_list_file("host_list.json");
                    if(!host_list_file.open(QIODevice::ReadWrite)) {
                    qDebug() << "ip_mapping open error,the premission may denied.";
                    } else {
                    qDebug() <<"ip_mapping File open!";
                    }
                    QByteArray host_list_file_BA_file = host_list_file.readAll();
                    QJsonDocument host_list_doc = QJsonDocument::fromJson(host_list_file_BA_file);
                    QJsonObject root = host_list_doc.object();
                    QJsonArray host_name_json_list = root["host_name_array"].toArray();
                    QJsonObject mac_list = root["mac_list"].toObject();
                    QString Dns_name;


  
                    QFile install_file("install_setting.json");
                    if(!install_file.open(QIODevice::ReadWrite)) {
                    qDebug() << "File open error,the premission may denied.";
                    } else {
                    qDebug() <<"install_setting File open!";
                    }
                    QByteArray install_byte = install_file.readAll();
                    install_setting_json_document = QJsonDocument::fromJson(install_byte);
                    QJsonObject install_root = install_setting_json_document.object();
                    QJsonObject install_config = install_root["install_config"].toObject();
                    QJsonObject host = install_config[mac_result].toObject();
                    QString message_type = host["message_type"].toString();

                    install_file.close();

                    // for(const QString& key : mac_list.keys()) {
                    //     QJsonObject host_obj = mac_list[key].toObject();
                    //     QString ip_value =host_obj["ip_address"].toString();
                    //     // host_name is ip
                    //     QString mac_address_in_list = key.split("/")[1];
                    //     QString host_name_in_list = key.split("/")[0];
                    //     QString ip_address_in_list = key.split("/")[2];

                    //     if (ip_value == host_name){
                    //         Dns_name=ip_value;
                    //     }
                    // }
                    if(Dns_name.isEmpty()){
                        Dns_name ="Unkown";
                    }
                    is_opened_host.append(Dns_name+"/"+mac_result+"/"+host_name+"/"+message_type);
                    is_opened_host_name.append(Dns_name+"/"+mac_result+"/"+host_name+"/"+message_type);
                }
            }

}
void install_shell::icmp_thread_patch(QList<QString> net_list){
    std::shared_ptr<std::thread>* threads = new std::shared_ptr<std::thread>[net_list.length()];
        for(int i =0; i <net_list.length(); i++){
            threads[i] = std::make_shared<std::thread>(std::bind(&install_shell::check_icmp_has_open,this,net_list[i]));
            if (i%50==0 && i!=0){
                for(int j=i-50; j<i;j++){
                    threads[j]->join();
                }
            }
        } 
        for(int i =0; i !=net_list.length(); i++){
            if(threads[i]->joinable()){
            threads[i]->join();
            }
        } 
        ui->pushButton_2->setEnabled(true);
        QFile host_list_file("host_list.json");
        if(!host_list_file.open(QIODevice::ReadWrite)) {
            qDebug() << "ip_mapping open error,the premission may denied.";
        } else {
            qDebug() <<"ip_mapping File open!";
        }

        QByteArray host_list_file_BA_file = host_list_file.readAll();
        QJsonDocument host_list_doc = QJsonDocument::fromJson(host_list_file_BA_file);
        QJsonObject root = host_list_doc.object();
        QJsonArray host_name_json_list = root["host_name_array"].toArray();
        QJsonObject contant=root["mac_list"].toObject();
        QJsonObject host_contant ;
        //有DNS紀錄的
        qDebug()<<is_opened_host_name;
        for(QString host_information : is_opened_host_name){
            qDebug()<<host_information;
            
            QString mac_address = host_information.split("/")[1];
            QString current_host_name = host_information.split("/")[0];
            QString ip_address = host_information.split("/")[2];
            bool check_flag = true;
                for(int i =0;i<=host_name_json_list.size();i++){
                    if(host_name_json_list[i].toString().contains(mac_address)){
                        check_flag =false;
                    } 
                }
                if(check_flag){
                        bool array_duplication_check = false;
                        for(int i =0;i<host_name_json_list.size();i++){
                            if(host_name_json_list[i].toString()==host_information){
                                array_duplication_check = true;
                            };
                        }
                        if(!array_duplication_check){
                            host_name_json_list.append(host_information);
                        }
                        host_contant = contant[mac_address].toObject();
                        host_contant["host_name"]=current_host_name;
                        host_contant["ip_address"]=ip_address;
                        host_contant["manual"] = false;
                        host_contant["Device"] = ui->comboBox_2->itemText(0);
                }else{
                        host_contant = contant[mac_address].toObject();
                        for(int i =0;i<host_name_json_list.size();i++){
                            if(host_name_json_list[i].toString().contains(mac_address)){
                                host_name_json_list.removeAt(i);
                                host_name_json_list.append(host_information);

                            }
                        }
                        host_contant = contant[mac_address].toObject();
                        host_contant["host_name"]=current_host_name;
                        host_contant["ip_address"]=ip_address;
                }
            contant[mac_address] = host_contant;

        }

        qDebug()<<"update file close file.";
        root["mac_list"]=contant;
        root["host_name_array"]=host_name_json_list;
        host_list_doc.setObject(root);
        host_list_file.resize(0);
        host_list_file.write(host_list_doc.toJson());
        host_list_file.close();
        int list_count_3=ui->listWidget_3->count();
        for (int i = list_count_3 - 1; i >= 0; --i) {
            QListWidgetItem *item3 = ui->listWidget_3->takeItem(i);
            delete item3; // Remember to delete the item manually
        }

        for(auto host_name_in_json : host_name_json_list){
                ui->listWidget_3->addItem(host_name_in_json.toString());
        }
                ui->listWidget_3->setCurrentRow(0);

       int list_count_1=ui->listWidget->count();
        for (int i = list_count_1 - 1; i >= 0; --i) {
            QListWidgetItem *item1 = ui->listWidget->takeItem(i);
            delete item1; // Remember to delete the item manually
        }        
        ui->listWidget->addItems(is_opened_host);
}
void install_shell::on_install_mission_dispatch_push_button_clicked(){

    int task_count = ui->listWidget_2->count();
    qDebug()<<QString(task_count);
    std::string* mac_array =new std::string[task_count];
    std::string* ip_address_array =new std::string[task_count];
    std::string* Device_array =new std::string[task_count];
    std::string* host_name_array =new std::string[task_count];
    std::string* user_name_array =new std::string[task_count];
    std::string* Password_array =new std::string[task_count];
    std::string* pack_name_array =new std::string[task_count];
    std::string* interface_array =new std::string[task_count];
    std::string* ip_array =new std::string[task_count];
    bool* remove = new bool[task_count];
    bool* update = new bool[task_count];
    bool* install = new bool[task_count];
    bool* preserve = new bool[task_count];
    bool* update_deployment = new bool[task_count];

    if(task_count ==0){
        return;
    }
    QFile install_file("install_setting.json");
    if(!install_file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error,the premission may denied.";
    } else {
        qDebug() <<"install_setting File open!";
    }
    QByteArray install_setting_file = install_file.readAll();
    install_setting_json_document = QJsonDocument::fromJson(install_setting_file);
    QJsonObject root = install_setting_json_document.object();
    QJsonObject install_config = root["install_config"].toObject();
    
    for(int i=0;i<task_count;i++){
        QListWidgetItem* listwidget_current = ui->listWidget_2->item(i);
        mac_array[i] =  listwidget_current->text().split("/")[1].toStdString();
        QJsonObject host_object=install_config[ QString::fromStdString(mac_array[i])].toObject();
        if (!install_config.contains(QString::fromStdString(mac_array[i])))
        {
            qDebug()<<QString("install_config no mac in list.");
            return;
        }
        host_name_array[i] = host_object["host_name"].toString().toStdString();
        ip_address_array[i] = host_object["ip_address"].toString().toStdString();
        Device_array[i] = host_object["device"].toString().toStdString();
        remove[i] = host_object["remove"].toBool();
        update[i] = host_object["update"].toBool();
        install[i] = host_object["install"].toBool();
        preserve[i] = host_object["preserve"].toBool();
        update_deployment[i] = host_object["update_deployment"].toBool();


        user_name_array[i]=host_object["user"].toString().toStdString();
        Password_array[i]=host_object["password"].toString().toStdString();
                qDebug()<<QString("Def");

        qDebug()<<QString::fromStdString(user_name_array[i]) ;
        qDebug()<<QString::fromStdString(Password_array[i]);

        if (user_name_array[i]==""||Password_array[i]=="")
        {
            user_name_array[i]=root["default_user_name"].toString().toStdString();
            Password_array[i] =root["default_password"].toString().toStdString();
        qDebug()<<QString("De2f");
        qDebug()<<QString::fromStdString(user_name_array[i]) ;
        qDebug()<<QString::fromStdString(Password_array[i]);

        }
        pack_name_array[i]=host_object["Package_Name"].toString().toStdString();
        interface_array[i]=host_object["interface"].toString().toStdString();
        ip_array[i]=host_object["IP"].toString().toStdString();

    }
    install_file.close();
    qDebug() <<"install_mission_threads";
    // std::shared_ptr<std::thread>* install_mission_threads = new std::shared_ptr<std::thread>[task_count];
    for(int i=0;i<task_count;i++){
        std::string host_name_ =host_name_array[i];
        std::string mac_address =mac_array[i];
        std::string ip_address =ip_address_array[i];
        std::string device =Device_array[i];

        std::string user_name_ =user_name_array[i];
        std::string Password_ =Password_array[i];
        std::string pack_name_ =pack_name_array[i];
        std::string interface_ =interface_array[i];

        std::string ip_ =ip_array[i];
        bool remove_ = remove[i];
        bool update_ = update[i];
        bool install_ = install[i];
        bool preserve_ = preserve[i];
        bool update_deployment_ = update_deployment[i];

        qDebug()<<"test for install";
        qDebug()<<QString::fromStdString(host_name_);
        install_process* Install_process = new install_process(nullptr,user_name_,Password_,host_name_,mac_address,ip_address,pack_name_,interface_,ip_,device,remove_,update_,install_,preserve_,update_deployment_);
        Install_process->show();
        // install_mission_threads[i]= std::make_shared<std::thread>(std::bind(&install_shell::install_misson,this,user_name_,Password_,host_name_,pack_name_,interface_,ip_));

    }
    // for(int i =0;i<task_count;i++){
    //     install_mission_threads[i]->detach();
    // }

}
void install_shell::install_misson(std::string user_name,std::string Password,std::string ip_address,std::string pack_name,std::string interface,std::string ip){

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
    if (channel == NULL)
        return;
    rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK)
    {
        ssh_free(my_ssh_session);
        ssh_channel_free(channel);
        return ;
    }
    std::string ssh_command= ". ./ros2_docker/install.sh -i "+pack_name+" --interface "+interface +" --ip "+ip ;
    rc = ssh_channel_request_exec(channel, ssh_command.c_str());

    if (rc != SSH_OK)
    {
    ssh_channel_close(channel);
    ssh_channel_free(channel);
    }
    QByteArray ssh_Qbyte;
    QByteArray ssh_merge_qbyte;
    QString ssh_infor_string;
    qDebug()<<QString("ssh_channel_read"); 

  while (ssh_channel_is_open(channel) &&! ssh_channel_is_eof(channel))
    {
        ssh_Qbyte = QByteArray::fromRawData(buffer,nbytes);
        ssh_merge_qbyte.append(ssh_Qbyte);
        nbytes =  ssh_channel_read(channel, buffer, sizeof(buffer), 0);
        ssh_infor_string=ssh_merge_qbyte;
        if (nbytes >= 0)
        {
            break;
        }
        
        qDebug().noquote()<<ssh_infor_string;
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
    qDebug()<<QString("Done"); 
}



void install_shell::on_current_host_information_changed(QListWidgetItem * item){
    
        host_name_item=item;
        QString host_name = item->text().split("/")[0];
        QString mac_address =item->text().split("/")[1];
        QString ip_address = item->text().split("/")[2];

        QFile host_list_file("host_list.json");
        if(!host_list_file.open(QIODevice::ReadWrite)) {
        qDebug() << "ip_mapping open error,the premission may denied.";
        } else {
        qDebug() <<"ip_mapping File open!";
        }
        QByteArray host_list_file_BA_file = host_list_file.readAll();
        QJsonDocument host_list_doc = QJsonDocument::fromJson(host_list_file_BA_file);
        QJsonObject root = host_list_doc.object();
        QJsonArray host_name_json_list = root["host_name_array"].toArray();
        QJsonObject contant=root["mac_list"].toObject();
        QJsonObject currentItem_object =contant[mac_address].toObject();

        QFile install_file("install_setting.json");
        if(!install_file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error,the premission may denied.";
        } else {
        qDebug() <<"install_setting File open!";
        }
        QByteArray install_byte = install_file.readAll();
        install_setting_json_document = QJsonDocument::fromJson(install_byte);
        QJsonObject install_root = install_setting_json_document.object();
        QJsonObject install_config = install_root["install_config"].toObject();
        QJsonObject host = install_config[mac_address].toObject();
        QString user_name = host["user"].toString();
        QString message_type = host["message_type"].toString();
        QString password = host["password"].toString();
        install_file.close();

        ui->lineEdit_3->setText(user_name);
        ui->lineEdit_4->setText(password);

        ui->lineEdit_2->setText(host_name);
        ui->lineEdit_7->setText(mac_address);
        ui->lineEdit_8->setText(message_type);

        ui->lineEdit->setText(currentItem_object["ip_address"].toString());
        ui->comboBox_2->setCurrentText(currentItem_object["Device"].toString());
        host_list_file.close();
}
void install_shell::on_update_host_information_push_button_clicked(){
    QString mac_address = ui->lineEdit_7->text();
    QString host_name = ui->lineEdit_2->text();
    QString user_name= ui->lineEdit_3->text();
    QString password = ui->lineEdit_4->text();
    QString message_type = ui->lineEdit_8->text();
    QString ip = ui->lineEdit->text();
    QString device = ui->comboBox_2->currentText();
    if(host_name_item ==nullptr){
        return;
    }

        QProcess ping_process;
        QString command_string = "ping "+ip+" -c 1 -w 1 -W 1 ";
        //qDebug()<<command_string;
        ping_process.start(command_string,QIODevice::ReadOnly);
        ping_process.waitForFinished(-1);
        QString result = QString::fromLocal8Bit(ping_process.readAllStandardOutput());
        ping_process.kill();
        if(result.contains("ttl")){
            QFile host_list_file("host_list.json");
            if(!host_list_file.open(QIODevice::ReadWrite)) {
            qDebug() << "ip_mapping open error,the premission may denied.";
            } else {
            qDebug() <<"ip_mapping File open!";
            }
            QByteArray host_list_file_BA_file = host_list_file.readAll();
            QJsonDocument host_list_doc = QJsonDocument::fromJson(host_list_file_BA_file);
            QJsonObject root = host_list_doc.object();
            QJsonArray host_name_json_list = root["host_name_array"].toArray();
            QJsonObject contant=root["mac_list"].toObject();
            QJsonObject host_contant = contant[mac_address].toObject();
            if(host_contant["ip_address"].toString() !=ip ||host_contant["Device"].toString() !=device){
                host_contant["ip_address"] = ip;
                host_contant["Device"] = device;
                contant[mac_address] =host_contant;

                root["mac_list"]=contant;
                host_list_doc.setObject(root);
                host_list_file.resize(0);
                host_list_file.write(host_list_doc.toJson());
            }
            host_list_file.close();
        }else{
            QMessageBox exception_ip_not_found;
            exception_ip_not_found.setText("這個IP無法訪問");
            exception_ip_not_found.exec();
        }



    QFile install_file("install_setting.json");
    if(!install_file.open(QIODevice::ReadWrite)) {
      qDebug() << "File open error,the premission may denied.";
    } else {
      qDebug() <<"install_setting File open!";
    }
    QJsonObject root = install_setting_json_document.object();
    QJsonObject install_config = root["install_config"].toObject();
    QString install_config_mac = mac_address;
    QJsonObject host = install_config[install_config_mac].toObject();

    host["host_name"]=host_name;
    host["ip_address"]=ip;
    host["user"]=user_name;
    host["password"]=password;
    host["message_type"]=message_type;
    host["device"]=device;

    install_config[install_config_mac]=host;
    root["install_config"]=install_config;
    install_setting_json_document.setObject(root);
    install_file.resize(0);

    install_file.write(install_setting_json_document.toJson());
    install_file.close();
    // if(ui->pushButton_2->isEnabled()){
    // on_Interface_Choose_PushButtun_clicked();
    // }

}
// void install_shell::on_creat_host_information_push_button_clicked(){
//     QString host_name = ui->lineEdit_2->text();
//     QString mac_address = ui->lineEdit_7->text();
//     QString user_name= ui->lineEdit_3->text();
//     QString password = ui->lineEdit_4->text();
//     QString ip = ui->lineEdit->text();
//     QString device = ui->comboBox_2->currentText();
//     bool manual = !ui->checkBox->isChecked();
//     QFile host_list_file("host_list.json");
//     if(!host_list_file.open(QIODevice::ReadWrite)) {
//     qDebug() << "ip_mapping open error,the premission may denied.";
//     } else {
//     qDebug() <<"ip_mapping File open!";
//     }
//     QByteArray host_list_file_BA_file = host_list_file.readAll();
//     QJsonDocument host_list_doc = QJsonDocument::fromJson(host_list_file_BA_file);
//     QJsonObject root = host_list_doc.object();
//     QJsonArray host_name_json_list = root["host_name_array"].toArray();
//     QJsonObject contant=root["mac_list"].toObject();
//     QJsonObject host_contant = contant[host_name].toObject();
//     bool array_duplication_check = false;
//     for(int i =0;i<host_name_json_list.size();i++){
//         if(host_name_json_list[i].toString()==host_name){
//             array_duplication_check = true;
//         };
//     }
//     if(!array_duplication_check){
//         host_name_json_list.append(host_name);
//     }
//     host_contant["ip_address"] = ip;
//     host_contant["Device"] = device;
//     host_contant["manual"] = manual;
//     contant[host_name] = host_contant;
//     root["mac_list"]=contant;
//     root["host_name_array"]=host_name_json_list;
//     host_list_doc.setObject(root);
//     host_list_file.resize(0);
//     host_list_file.write(host_list_doc.toJson());
//     host_list_file.close();


//     QFile install_file("install_setting.json");
//     if(!install_file.open(QIODevice::ReadWrite)) {
//       qDebug() << "File open error,the premission may denied.";
//     } else {
//       qDebug() <<"install_setting File open!";
//     }
//     QJsonObject install_root = install_setting_json_document.object();
//     QJsonObject install_config = install_root["install_config"].toObject();
//     QJsonObject host = install_config[host_name].toObject();
//     host["user"]=user_name;
//     host["password"]=password;
//     host["device"]=device;

//     install_config[host_name]=host;
//     install_root["install_config"]=install_config;
//     install_setting_json_document.setObject(install_root);
//     install_file.resize(0);
//     install_file.write(install_setting_json_document.toJson());
//     install_file.close();

//     ui->listWidget_3->addItem(host_name);

//     if(ui->pushButton_2->isEnabled()){
//     on_Interface_Choose_PushButtun_clicked();
//     }
// }

void install_shell::on_delet_host_information_push_button_clicked(){

    if (ui->listWidget_3==nullptr)
    {
        qDebug()<<QString("null");
        return;
        /* code */
    }
    
    QList<QListWidgetItem*> items = ui->listWidget_3->selectedItems();
    if (items.count()==0)
    {
    QMessageBox mission_install_is_empty;
    mission_install_is_empty.setText("the device install list has not been selected any item.");
    mission_install_is_empty.exec();
    return;
    }else if(items.count()>=2){
        QMessageBox mission_install_is_empty;
        mission_install_is_empty.setText("mutiple select item.");
        mission_install_is_empty.exec();
    return; 
    }
    qDebug()<<QString("test");

    foreach(QListWidgetItem* item, items)
    {

    QString host_name = ui->listWidget_3->takeItem(ui->listWidget_3->row(item))->text();;
    QFile host_list_file("host_list.json");
    if(!host_list_file.open(QIODevice::ReadWrite)) {
    qDebug() << "ip_mapping open error,the premission may denied.";
    } else {
    qDebug() <<"ip_mapping File open!";
    }
    QByteArray host_list_file_BA_file = host_list_file.readAll();
    QJsonDocument host_list_doc = QJsonDocument::fromJson(host_list_file_BA_file);
    QJsonObject root = host_list_doc.object();
    QJsonArray host_name_json_list = root["host_name_array"].toArray();
    QJsonObject contant=root["mac_list"].toObject();
    QJsonObject host_contant = contant[host_name].toObject();
    contant.remove(host_name);
    for(int i =0;i<host_name_json_list.size();i++){
        if(host_name_json_list[i].toString()==host_name){
            host_name_json_list.removeAt(i);
        };
    }
    root["mac_list"] = contant;
    root["host_name_array"] = host_name_json_list;
    host_list_doc.setObject(root);
    host_list_file.resize(0);
    host_list_file.write(host_list_doc.toJson());
    host_list_file.close();

    QFile install_file("install_setting.json");
    if(!install_file.open(QIODevice::ReadWrite)) {
      qDebug() << "File open error,the premission may denied.";
    } else {
      qDebug() <<"install_setting File open!";
    }
    QJsonObject install_root = install_setting_json_document.object();
    QJsonObject install_config = install_root["install_config"].toObject();
    install_config.remove(host_name);
    install_root["install_config"]=install_config;
    install_setting_json_document.setObject(install_root);
    install_file.resize(0);
    install_file.write(install_setting_json_document.toJson());
    install_file.close();


    //need fix with listWidget_3
    delete item;
    }



}


void install_shell::on_install_option_push_button_clicked(){

   if (ui->listWidget==nullptr)
    {
        qDebug()<<QString("null");
        return;
        /* code */
    }
    
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    if (items.count()==0)
    {
    QMessageBox mission_install_is_empty;
    mission_install_is_empty.setText("the device install list has not been selected any item.");
    mission_install_is_empty.exec();
    return;
    }else if(items.count()>=2){
        QMessageBox mission_install_is_empty;
        mission_install_is_empty.setText("mutiple select item.");
        mission_install_is_empty.exec();
    return; 
    }
    qDebug()<<QString("test");

    foreach(QListWidgetItem* item, items)
    {
    QString DNS_replace = "";
    QString mac_address = "";
    QString item_text=item->text();
    QJsonObject host;
    QFile install_file("install_setting.json");

    if(!install_file.open(QIODevice::ReadWrite)) {
    qDebug() << "File open error,the premission may denied.";
    } else {
    qDebug() <<"install_setting File open!";
    }
    QByteArray install_byte = install_file.readAll();
    install_setting_json_document = QJsonDocument::fromJson(install_byte);
    QJsonObject install_root = install_setting_json_document.object();
    QJsonObject install_config = install_root["install_config"].toObject();
    QString SetHost = item->text().split("/")[1];
    mac_address=item_text.split("/")[1];



        host = install_config[SetHost].toObject();
        QString user_name = host["user"].toString();
        QString password = host["password"].toString();
        QString ip_config = host["ip"].toString()!=""?host["ip"].toString():"dhcp";
        QString interface = host["interface"].toString()!=""?host["interface"].toString():"eth0";
        QString device = host["device"].toString();
        QString pack_names = host["Package_Name"].toString();
        install_setting_json_document.setObject(install_root);
        install_file.close();
        if(device == ""){
            QMessageBox device_not_found;
            device_not_found.setText("you havent set device.");
            device_not_found.exec();
            return;
        }
        install_option* the_install_option =new install_option(nullptr,mac_address,device,pack_names,interface,ip_config);
        the_install_option->show();
    }

}

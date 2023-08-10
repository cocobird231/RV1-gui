#include "install_shell.h"
#include <QDebug>
#include <stdio.h>

 #include <iostream>

#include <string.h> 
#include<iostream>
#include <QFile>

#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonValue>
#include<QJsonArray>
#include <QHostAddress>
#include <QtNetwork>
#include <thread>
#include <QMessageBox>
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
std::shared_ptr<std::thread> the_thread;

 install_shell::install_shell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::install_shell)
{
    ui->setupUi(this);
    ui->pushButton_6->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->checkBox->setChecked(true);
    connect(ui->pushButton, &QPushButton::clicked, this, &install_shell::on_Interface_Update_PushButtun_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &install_shell::on_Interface_Choose_PushButtun_clicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &install_shell::on_update_host_information_push_button_clicked);
    connect(ui->listWidget,&QListWidget::currentItemChanged,this,&install_shell::on_current_HostName_changed);
    connect(ui->listWidget_3,&QListWidget::currentItemChanged,this,&install_shell::on_current_host_information_changed);
    connect(ui->checkBox,&QCheckBox::stateChanged,this,&install_shell::on_identity_hos_name_manual_state_changed);
    connect(ui->pushButton_6,&QPushButton::clicked,this,&install_shell::on_creat_host_information_push_button_clicked);
    connect(ui->pushButton_7,&QPushButton::clicked,this,&install_shell::on_delet_host_information_push_button_clicked);

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
        // qDebug()<<"IP Address: "<<entry.ip().toString(); 
        // qDebug()<<"Netmask: "<<entry.netmask().toString(); 
        // qDebug()<<"Broadcast: "<<entry.broadcast().toString();
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
    
    // should intall libssh-dev
    // test for ssh lib
    // ssh_session my_ssh_session;
    // int rc;
    // int port = 22;
    // int verbosity = SSH_LOG_PROTOCOL;
    // char *password;
    // // Open session and set options
    // ssh_session my_ssh_session = ssh_new();
    // if (my_ssh_session == NULL)
    //     exit(-1);
    // ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, "192.168.1.157");
    // ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);
    // ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, "tony");
    // ssh_options_set(my_ssh_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
    // ssh_options_set(my_ssh_session, SSH_OPTIONS_CIPHERS_C_S,"aes128-ctr");
    // rc = ssh_connect(my_ssh_session);
    // if (rc != SSH_OK)  
    // {
    //     qDebug()<< "Error: "+ QString(ssh_get_error(my_ssh_session)); //HERE IS WHERE I GET THE ERROR 
    //     ssh_free(my_ssh_session);
    // }

    // Verify the server's identity
    // For the source code of verify_knowhost(), check previous example
/*  if (verify_knownhost(my_ssh_session) < 0)
    {
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        exit(-1);
    }
*/  
    // qDebug()<<"1231231";
    // password = "tony1234";
    // rc = ssh_userauth_password(my_ssh_session, NULL, password);
    // qDebug()<<"rc";
    // if (rc != SSH_AUTH_SUCCESS)  
    // {
    //      qDebug()<< "Error: "+ QString(ssh_get_error(my_ssh_session)); //HERE IS WHERE I GET THE ERROR 
    //     ssh_free(my_ssh_session);
    //     exit(-1);
    // }
    // ssh_disconnect(my_ssh_session);
    // ssh_free(my_ssh_session);

}
void install_shell::on_Interface_Update_PushButtun_clicked(){

    //the_interface_list.clear();
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
        ui->comboBox->addItem("Interface: "+interface.name()+"/ IP Address: "+entry.ip().toString()+"/ NetMask: "+entry.netmask().toString());
        }
    }

}
    void install_shell::on_Interface_Choose_PushButtun_clicked(){
        qDebug()<<"on_Interface_Choose_PushButtun_clicked";
        this->dispatch_mission_refresh();
}
void install_shell::dispatch_mission_refresh(){
        ui->pushButton_2->setEnabled(false);
        int list_count=ui->listWidget->count();
        for (int i = list_count - 1; i >= 0; --i) {
            QListWidgetItem *item = ui->listWidget->takeItem(i);
            delete item; // Remember to delete the item manually
        }
        qDebug()<<".clear";
        is_opened_host_address.clear();
        is_opened_host_name.clear();
        is_opened_host.clear();
        is_opened_host_map.clear();
        qDebug()<<"clear.";

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
        //不確定會被回收時機 一定要+smart pointer
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
    QFile install_file("install_setting.json");
    if(!install_file.open(QIODevice::ReadWrite)) {
      qDebug() << "File open error,the premission may denied.";
    } else {
      qDebug() <<"install_setting File open!";
    }
    qDebug()<<"destory_Install.";
    qDebug()<<install_setting_json_document;
    install_file.resize(0);
    install_file.write(install_setting_json_document.toJson());
    install_file.close();
    delete ui;
}


void install_shell::check_ssh_has_open(QString host_name,QString user_name){


    int rc;
    int port = 22;
    int verbosity = SSH_LOG_PROTOCOL;
    char *password;
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

void install_shell::check_icmp_has_open(QString host_name){
            QProcess ping_process;
            QString command_string = "ping "+host_name+" -c 1 -w 1 -W 1 ";
            //qDebug()<<command_string;
            ping_process.start(command_string,QIODevice::ReadOnly);
            ping_process.waitForFinished(-1);
            QString result = QString::fromLocal8Bit(ping_process.readAllStandardOutput());
            //qDebug()<<result;
            ping_process.kill();
            if(result.contains("ttl")){
                //lookup
                is_opened_host_address.append(host_name);
                QProcess dns_process;
                QString dns_command_string = "nslookup "+host_name;
                //qDebug()<<command_string;
                dns_process.start(dns_command_string,QIODevice::ReadOnly);
                dns_process.waitForFinished(-1);
                QString dns_result = QString::fromLocal8Bit(dns_process.readAllStandardOutput());
                qDebug()<<result;
                dns_process.kill();
                if(dns_result.contains("name = ")){
                QString DNS_host_name =dns_result.split("name = ")[1].split(".")[0];
                is_opened_host_name.append(DNS_host_name);
                is_opened_host.append(DNS_host_name+":"+host_name);
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
                    QJsonObject ip_list = root["IP_list"].toObject();
                    QString Dns_name;
                    for(const QString& key : ip_list.keys()) {
                        QJsonObject host_obj = ip_list[key].toObject();
                        QString value =host_obj["ip_address"].toString();
                        // This host_name is asign by ip;
                        if (value == host_name){
                            Dns_name=key;
                            //"/"is mean manual mappping
                            is_opened_host.append(Dns_name+"/"+host_name);
                        }
                    }
                    if(Dns_name.isEmpty()){
                    is_opened_host.append(host_name+"/"+host_name);
                    }
                    //qDebug()<<"Can not found:"+host_name;
                }
            }

}
void install_shell::icmp_thread_patch(QList<QString> net_list){

    std::shared_ptr<std::thread> threads[net_list.length()];
        bool has_join_thread [net_list.length()] = {false};
        for(int i =0; i <net_list.length(); i++){
            threads[i] = std::make_shared<std::thread>(std::bind(&install_shell::check_icmp_has_open,this,net_list[i]));
            if (i%50==0 && i!=0){
                for(int j=i-50; j<i;j++){
                    threads[j]->join();
                    has_join_thread[j] = true;
                }
            }
        } 

        for(int i =0; i !=net_list.length(); i++){
            if(threads[i]->joinable()){
            threads[i]->join();
            }
        } 
    
        ui->pushButton_2->setEnabled(true);
        // qDebug()<<is_opened_host_address;
        // qDebug()<<is_opened_host_name;
         qDebug()<<"icmp_thread_patch_DOne_thread.";


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
        QJsonObject contant=root["IP_list"].toObject();
                 qDebug()<<"contant.";
        QJsonObject host_contant ;
        //有DNS紀錄的
        for(QString host_name : is_opened_host_name){
                     qDebug()<<host_name;

            if(!host_name_json_list.contains(host_name)){
                qDebug()<<"not todo";

                bool array_duplication_check = false;
                for(int i =0;i<host_name_json_list.size();i++){
                    if(host_name_json_list[i].toString()==host_name){
                        array_duplication_check = true;
                    };
                }
                if(!array_duplication_check){
                    host_name_json_list.append(host_name);
                }
                qDebug()<<"123sdf";
                host_contant = contant[host_name].toObject();
                host_contant["ip_address"]=is_opened_host_map[host_name];
                qDebug()<<"ip_address";
                host_contant["manual"] = false;
                qDebug()<<"manual";

                host_contant["Device"] = ui->comboBox_2->itemText(0);
                qDebug()<<"Device";

                contant[host_name] = host_contant;
            }else{
                //to do
                qDebug()<<"todo";
                if(contant[host_name].toObject()["ip_address"]!=is_opened_host_map[host_name]){
                    bool array_duplication_check = false;
                    for(int i =0;i<host_name_json_list.size();i++){
                        if(host_name_json_list[i].toString()==host_name){
                            array_duplication_check = true;
                        };
                    }
                    if(!array_duplication_check){
                        host_name_json_list.append(host_name);
                    }
                    host_contant = contant[host_name].toObject();
                    host_contant["ip_address"]=is_opened_host_map[host_name];
                    contant[host_name] = host_contant;
                }
            }
        }

        qDebug()<<"update file close file.";
        root["IP_list"]=contant;
        root["host_name_array"]=host_name_json_list;
        host_list_doc.setObject(root);
        host_list_file.resize(0);
        host_list_file.write(host_list_doc.toJson());
        host_list_file.close();
        qDebug()<<"update ui.";


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
        qDebug()<<"done func";

}
void install_shell::on_current_HostName_changed(QListWidgetItem * item){

}
void install_shell::on_current_host_information_changed(QListWidgetItem * item){
        host_name_item=item;
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
        QJsonObject contant=root["IP_list"].toObject();
        QJsonObject currentItem_object =contant[item->text()].toObject();
        ui->lineEdit_2->setText(item->text());
        ui->lineEdit->setText(currentItem_object["ip_address"].toString());
        ui->comboBox_2->setCurrentText(currentItem_object["Device"].toString());
        ui->checkBox->setChecked(!currentItem_object["manual"].toBool());
        host_list_file.close();
}
void install_shell::on_update_host_information_push_button_clicked(){
    QString host_name = ui->lineEdit_2->text();
    QString ip = ui->lineEdit->text();
    QString device = ui->comboBox_2->currentText();
    bool manual = !ui->checkBox->isChecked();

    if(host_name ==host_name_item->text()&& !manual ){
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
            QJsonObject contant=root["IP_list"].toObject();
            QJsonObject host_contant = contant[host_name].toObject();
            if(!(!host_contant["manual"].toBool()&& host_contant["ip_address"] !=ip)){
                host_contant["ip_address"] = ip;
                host_contant["Device"] = device;
                contant[host_name] =host_contant;
                root["IP_list"]=contant;
                host_list_doc.setObject(root);
                host_list_file.resize(0);
                host_list_file.write(host_list_doc.toJson());
            }else{
                QMessageBox exception;
                ui->lineEdit->setText(host_contant["ip_address"].toString());
                exception.setText("DNS取得IP不應該被修改");
                exception.exec();
            }
            host_list_file.close();
        }else{
            QMessageBox exception_ip_not_found;
            exception_ip_not_found.setText("這個IP無法訪問");
            exception_ip_not_found.exec();
        }
    }else if(manual){
        QProcess ping_process;
        QString command_string = "ping "+ip+" -c 1 -w 1 -W 1 ";
        //qDebug()<<command_string;
        ping_process.start(command_string,QIODevice::ReadOnly);
        ping_process.waitForFinished(-1);
        QString result_ = QString::fromLocal8Bit(ping_process.readAllStandardOutput());
        //qDebug()<<result_;
        ping_process.kill();
            if(result_.contains("ttl")){
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
                QJsonObject contant=root["IP_list"].toObject();
                contant.remove(host_name_item->text());
                for(int i =0;i<host_name_json_list.size();i++){
                    if(host_name_json_list[i].toString()==host_name){
                        host_name_json_list.removeAt(i);
                        bool array_duplication_check = false;
                        for(int i =0;i<host_name_json_list.size();i++){
                            if(host_name_json_list[i].toString()==host_name){
                                array_duplication_check = true;
                            };
                        }
                        if(!array_duplication_check){
                            host_name_json_list.append(host_name);
                        }
                    }
                }
                host_name_item->setText(host_name);
                root["host_name_array"] =host_name_json_list;
                QJsonObject host_contant = contant[host_name].toObject();
                host_contant["ip_address"] = ip;
                host_contant["Device"] = device;
                host_contant["manual"]=manual;
                contant[host_name] =host_contant;
                root["IP_list"]=contant;
                host_list_doc.setObject(root);
                host_list_file.resize(0);
                host_list_file.write(host_list_doc.toJson());
                host_list_file.close();

            }else
            {
                QMessageBox exception_ip_not_found;
                exception_ip_not_found.setText("這個IP無法訪問");
                exception_ip_not_found.exec();
            }
    }
    else{
        QMessageBox exception;
        ui->lineEdit_2->setText(host_name_item->text());
        exception.setText("主機名稱不應該被修改");
        exception.exec();
    }
    if(ui->pushButton_2->isEnabled()){
    dispatch_mission_refresh();
    }

}
void install_shell::on_creat_host_information_push_button_clicked(){
    QString host_name = ui->lineEdit_2->text();
    QString ip = ui->lineEdit->text();
    QString device = ui->comboBox_2->currentText();
    bool manual = !ui->checkBox->isChecked();
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
    QJsonObject contant=root["IP_list"].toObject();
    QJsonObject host_contant = contant[host_name].toObject();
    bool array_duplication_check = false;
    for(int i =0;i<host_name_json_list.size();i++){
        if(host_name_json_list[i].toString()==host_name){
            array_duplication_check = true;
        };
    }
    if(!array_duplication_check){
        host_name_json_list.append(host_name);
    }
    host_name_json_list.append(host_name);
    host_contant["ip_address"] = ip;
    host_contant["Device"] = device;
    host_contant["manual"] = manual;
    contant[host_name] = host_contant;
    root["IP_list"]=contant;
    root["host_name_array"]=host_name_json_list;
    host_list_doc.setObject(root);
    host_list_file.resize(0);
    host_list_file.write(host_list_doc.toJson());
    host_list_file.close();
    ui->listWidget_3->addItem(host_name);

    if(ui->pushButton_2->isEnabled()){
    dispatch_mission_refresh();
    }
}

void install_shell::on_delet_host_information_push_button_clicked(){
    QString host_name = host_name_item->text();
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
    QJsonObject contant=root["IP_list"].toObject();
    QJsonObject host_contant = contant[host_name].toObject();
    contant.remove(host_name_item->text());
    for(int i =0;i<host_name_json_list.size();i++){
        if(host_name_json_list[i].toString()==host_name_item->text()){
            host_name_json_list.removeAt(i);
        };
    }
    root["IP_list"] = contant;
    root["host_name_array"] = host_name_json_list;
    host_list_doc.setObject(root);
    host_list_file.resize(0);
    host_list_file.write(host_list_doc.toJson());
    host_list_file.close();
    delete host_name_item;
    ui->listWidget_3->setCurrentRow(0);

}
void install_shell::on_identity_hos_name_manual_state_changed(int state){
    if(state){
        ui->pushButton_6->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
        ui->lineEdit->setEnabled(false);

    }else{
        ui->pushButton_6->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->lineEdit->setEnabled(true);
    }
}
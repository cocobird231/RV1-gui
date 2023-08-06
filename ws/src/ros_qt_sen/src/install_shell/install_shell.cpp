#include "install_shell.h"
#include <QDebug>
#include <string>
#include <stdio.h>

#include <QFile>

#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonValue>
#include<QJsonArray>
#include <QHostAddress>
#include <QtNetwork>

QList<QNetworkAddressEntry> entryList;
QString selected_self_IP;
QJsonDocument install_setting_json_document ;


 install_shell::install_shell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::install_shell)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &install_shell::on_Interface_Update_PushButtun_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &install_shell::on_Interface_Choose_PushButtun_clicked);

    QFile file("install_setting.json");
    if(!file.open(QIODevice::ReadWrite)) {
      qDebug() << "File open error,the premission may denied.";
    } else {
      qDebug() <<"install_setting File open!";
    }
    QByteArray install_setting_file = file.readAll();
    install_setting_json_document = QJsonDocument::fromJson(install_setting_file);
    QJsonObject root = install_setting_json_document.object();

    if(!(root["default_interface"].toString()=="" || root["default_ip"].toString()==""|| root["default_net_mask"].toString()=="")){
    ui->comboBox->addItem("Interface: "+root["default_interface"].toString()+"/ IP Address: "+root["default_ip"].toString()+"/ NetMask: "+root["default_net_mask"].toString());
    file.close();
}
    
    // should intall libssh-dev
    // test for ssh lib
    // ssh_session my_ssh_session;
    int rc;
    int port = 22;
    int verbosity = SSH_LOG_PROTOCOL;
    char *password;
    // Open session and set options
    ssh_session my_ssh_session = ssh_new();
    if (my_ssh_session == NULL)
        exit(-1);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, "raspitest3");
    ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, "tony");
    ssh_options_set(my_ssh_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_CIPHERS_C_S,"aes128-ctr");
    rc = ssh_connect(my_ssh_session);
    if (rc != SSH_OK)  
    {
        qDebug()<< "Error: "+ QString(ssh_get_error(my_ssh_session)); //HERE IS WHERE I GET THE ERROR 
        ssh_free(my_ssh_session);
        exit(-1);
    }
    // Verify the server's identity
    // For the source code of verify_knowhost(), check previous example
/*  if (verify_knownhost(my_ssh_session) < 0)
    {
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        exit(-1);
    }
*/  
    qDebug()<<"1231231";
    password = "tony1234";
    rc = ssh_userauth_password(my_ssh_session, NULL, password);
    qDebug()<<"rc";
    if (rc != SSH_AUTH_SUCCESS)  
    {
         qDebug()<< "Error: "+ QString(ssh_get_error(my_ssh_session)); //HERE IS WHERE I GET THE ERROR 
        ssh_free(my_ssh_session);
        exit(-1);
    }
    ssh_disconnect(my_ssh_session);
    ssh_free(my_ssh_session);
}
void install_shell::on_Interface_Update_PushButtun_clicked(){


        // To find the host name for 4.2.2.1
    QString hostName = "192.168.1.100";
    QHostInfo::lookupHost(hostName, this, SLOT(lookedUpCallback(QHostInfo)));
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

        QFile file("install_setting.json");
        if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error,the premission may denied.";
        } else {
        qDebug() <<"install_setting File open!";
        }
        file.resize(0);
        file.write(install_setting_json_document.toJson());
        file.close();
        QList<QString> subnet_list = getSubnetList(IP_address_string,Mask);
        qDebug()<<subnet_list;

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
    QFile file("install_setting.json");
    if(!file.open(QIODevice::ReadWrite)) {
      qDebug() << "File open error,the premission may denied.";
    } else {
      qDebug() <<"install_setting File open!";
    }
    qDebug()<<"destory_Install.";
    qDebug()<<install_setting_json_document;
    file.resize(0);
    file.write(install_setting_json_document.toJson());
    file.close();
    delete ui;
}


void install_shell::lookedUpCallback(const QHostInfo &host)
{
    if (host.error() != QHostInfo::NoError) {
        qDebug() << "Lookup failed:" << host.errorString();
        return;
    }

    qDebug() << "Found hostName:" << host.hostName();
}
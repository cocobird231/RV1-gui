#include "install_shell.h"
#include <QDebug>
#include <string>
#include <stdio.h>
 install_shell::install_shell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::install_shell)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &install_shell::on_Interface_Update_PushButtun_clicked);
    //should intall libssh-dev
    //test for ssh lib
    ssh_session my_ssh_session;
    int rc;
    int port = 22;
    int verbosity = SSH_LOG_PROTOCOL;
    char *password;
    // Open session and set options
    my_ssh_session = ssh_new();
    if (my_ssh_session == NULL)
        exit(-1);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, "192.168.1.6");
}
void install_shell::on_Interface_Update_PushButtun_clicked(){
    //test for interface scan
    struct ifaddrs * ifAddrStruct=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    while (ifAddrStruct!=NULL) {
        if (ifAddrStruct->ifa_addr->sa_family==AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            QString ifAddressString ="Inteface:"+ QString(ifAddrStruct->ifa_name) + "IPv4 Address:" + addressBuffer;
            qDebug()<<ifAddressString;
        } else if (ifAddrStruct->ifa_addr->sa_family==AF_INET6) { // check it is IP6
            // is a valid IP6 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            QString ifAddressString ="Inteface:" +QString(ifAddrStruct->ifa_name) + "IPv6 Address:" + addressBuffer;
            qDebug()<<ifAddressString;
        } 
        ifAddrStruct=ifAddrStruct->ifa_next;
    }

}

install_shell::~install_shell()
{
    delete ui;
}

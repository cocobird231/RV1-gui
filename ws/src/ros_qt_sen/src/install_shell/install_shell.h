#ifndef INSTALL_SHELL_H
#define INSTALL_SHELL_H

#include <QWidget>
#include "./../../ui_install_shell.h"
#include<QHostInfo>

#include <netinet/in.h> 
#include <arpa/inet.h>
#include <libssh/libssh.h>
#include <sys/types.h>
namespace Ui {
class install_shell;
}

class install_shell : public QWidget
{
    Q_OBJECT

public:
    explicit install_shell(QWidget *parent = nullptr);
    ~install_shell();

private:
    Ui::install_shell *ui;
    void on_Interface_Update_PushButtun_clicked();
    void on_Interface_Choose_PushButtun_clicked();
    QList<QString> getSubnetList(const QString& ipAddress, const QString& subnetMask);
    void check_ssh_has_open(QString host_name,QString user_name);
    void check_icmp_has_open(QString host_name);
    unsigned short cal_chksum(unsigned short *addr, int len);
    int ping( char *ips, int timeout);
    void icmp_thread_patch(QList<QString> net_list);


};

#endif // INSTALL_SHELL_H

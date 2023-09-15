#ifndef INSTALL_SHELL_H
#define INSTALL_SHELL_H

#include <QWidget>
#include "./../../ui_install_shell.h"
#include<QHostInfo>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <libssh/libssh.h>
 
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>
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
    QList<QString> getSubnetList(const QString& ipAddress, const QString& subnetMask);
    void check_ssh_has_open(QString host_name,QString user_name);
    void check_icmp_has_open(QString host_name);
    int ping( char *ips, int timeout);
    void icmp_thread_patch(QList<QString> net_list);
    QList<QString> subnet_list;
    void check_ssh_device_information(std::string host_name ,std::string user_name,std::string Password,std::string device_type);
    void install_misson(std::string user_name,std::string Password,std::string host_name,std::string pack_name,std::string interface,std::string ip);
private slots:
    void on_install_mission_dispatch_push_button_clicked();
    //void on_current_online_device_changed(QListWidgetItem * item);
    void on_Interface_Update_PushButtun_clicked();
    void on_Interface_Choose_PushButtun_clicked();
    void on_update_host_information_push_button_clicked();
    void on_delet_host_information_push_button_clicked();
    void on_current_host_information_changed(QListWidgetItem * item);
    void on_host_check_infor_push_button_clicked();
    void on_install_option_push_button_clicked();
    void on_add_mission_pushButton_clicked();
    void on_delet_mission_pushButton_clicked();
    void on_current_mission_install_changed(QListWidgetItem * item);
    void on_save_default_user_push_button();
};

#endif // INSTALL_SHELL_H

#ifndef INSTALL_SHELL_H
#define INSTALL_SHELL_H

#include <QWidget>
#include "./../../ui_install_shell.h"
#include<QHostInfo>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <libssh/libssh.h>
 #include <vector>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>



#include "vehicle_interfaces/msg/dev_info.hpp"
#include "vehicle_interfaces/srv/dev_info_reg.hpp"
#include "vehicle_interfaces/srv/dev_info_req.hpp"
#include <rclcpp/rclcpp.hpp>

namespace Ui {
class install_shell;
}

class install_shell : public QWidget
{
    Q_OBJECT

public:
    explicit install_shell(QWidget *parent = nullptr);
    class DeviceInforControlNode : public rclcpp::Node{
        public:
            DeviceInforControlNode(const std::string& nodeName, const std::string& DeviceInforServiceName);
            // bool regDeviceInfor(const std::shared_ptr<vehicle_interfaces::srv::DevInfoReg::Request> request, std::shared_ptr<vehicle_interfaces::srv::DevInfoReg::Response> response);
            bool reqDeviceInfor(const vehicle_interfaces::msg::DevInfo& reqDevInfo, std::vector<vehicle_interfaces::msg::DevInfo>& devInfoVec);
        private:
            // std::shared_ptr<rclcpp::Node> regClientNode_;
            // rclcpp::Client<vehicle_interfaces::srv::dev_info_reg>::SharedPtr regClient_;
            std::shared_ptr<rclcpp::Node> reqClientNode_;
            rclcpp::Client<vehicle_interfaces::srv::DevInfoReq>::SharedPtr reqClient_;
    };
    ~install_shell();

private:
    Ui::install_shell *ui;
    QList<QString> getSubnetList(const QString& ipAddress, const QString& subnetMask);
    void check_ssh_has_open(QString host_name,QString user_name);
    void check_icmp_has_open(QString host_name);
    int ping( char *ips, int timeout);
    void icmp_thread_patch(QList<QString> net_list);
    QList<QString> subnet_list;
    void check_ssh_device_information(std::string ip_address ,std::string user_name,std::string Password,std::string device_type);
    void install_misson(std::string user_name,std::string Password,std::string ip_address,std::string pack_name,std::string interface,std::string ip);
    void reboot_device(std::string ip_address ,std::string user_name,std::string Password);

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
    void on_reboot_push_button_clicked();
    void on_scan_ros2_device_infor_push_button();
    void on_quick_upgrade_mission_dispatch_push_button_clicked();
    void on_quick_depoly_mission_dispatch_push_button_clicked();

};

#endif // INSTALL_SHELL_H

#ifndef QOSDEVICEDIALOG_H
#define QOSDEVICEDIALOG_H
#include <rclcpp/rclcpp.hpp>
#include <QDialog>
#include "vehicle_interfaces/msg/qos_profile.hpp"
#include "vehicle_interfaces/msg/qos_update.hpp"
#include "vehicle_interfaces/srv/qos_reg.hpp"
#include "vehicle_interfaces/srv/qos_req.hpp"

namespace Ui {
class QosDeviceDialog;
}

class QosDeviceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QosDeviceDialog(QWidget *parent = nullptr);
    ~QosDeviceDialog();
    class QoSControlNode : public rclcpp::Node{
        private:
            std::shared_ptr<rclcpp::Node> regClientNode_;
            rclcpp::Client<vehicle_interfaces::srv::QosReg>::SharedPtr regClient_;

            std::shared_ptr<rclcpp::Node> reqClientNode_;
            rclcpp::Client<vehicle_interfaces::srv::QosReq>::SharedPtr reqClient_;

            rclcpp::Node::SharedPtr paramNode_;
            rclcpp::Client<rcl_interfaces::srv::SetParametersAtomically>::SharedPtr paramClient_;
        public:
            QoSControlNode(const std::string& nodeName, const std::string& qosServiceName);
            // send qos setting message (Qos profile) response success or not and qid
            bool requestQosReg(const std::shared_ptr<vehicle_interfaces::srv::QosReg::Request>& req);
            //take topic name request QosProfile reponse
            bool requestQosReq(const std::string& topicName, rmw_qos_profile_t& outQoSProfile);
            // set qos server setting enable publish and publish interval
            bool setParam(const rcl_interfaces::msg::Parameter& param);
    };
private:
    std::shared_ptr<rclcpp::Node> name_node;
    bool enable =false;
    void Qos_execut();
    Ui::QosDeviceDialog *ui;

private slots:
    void on_current_topic_name_choose(const QString &text);
    void on_update_topic_name_push_button_clicked();
    void on_add_qos_profile_push_button_clicked();
    void on_remove_qos_profile_push_button_clicked();
    void on_clear_qos_profile_push_button_clicked();
    void on_save_qos_profile_push_button_clicked();
    void on_enable_publish_push_button_clicked();
    void on_set_publish_push_button_clicked();

};

#endif // QOSDEVICEDIALOG_H

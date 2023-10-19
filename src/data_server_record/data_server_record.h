#ifndef DATA_SERVE_RECORD_H
#define DATA_SERVE_RECORD_H

#include <QWidget>
#include <string.h>
#include <rclcpp/rclcpp.hpp>
#include <rcl_interfaces/msg/set_parameters_result.hpp>
#include <rcl_interfaces/msg/parameter.hpp>

#include<chrono>

using namespace std::chrono_literals;
namespace Ui {
class data_server_record;
}

class data_server_record : public QWidget
{
    Q_OBJECT

public:
    explicit data_server_record(QWidget *parent = nullptr);
    ~data_server_record();
    class data_server_node: public rclcpp::Node
    {
        private:
            rclcpp::Node::SharedPtr paramNode_;
            rclcpp::Client<rcl_interfaces::srv::SetParametersAtomically>::SharedPtr paramClient_;
            void _connToService(rclcpp::ClientBase::SharedPtr client);

        public:
            data_server_node(const std::string& nodeName);
            bool _sendRequest(const rcl_interfaces::msg::Parameter& param);


    };
    
private:
    Ui::data_server_record *ui;
    std::shared_ptr<data_server_node> data_server_node_;
    double samplingStep_ms=0;
    double autoSaveTime_s=0;
    double recordTime_s=0;
    bool enabled_record=false;

private slots:
    void on_sampling_step_push_button_clicked();
    void on_Auto_save_time_push_button_clicked();
    void on_record_time_push_button_clicked();
    void on_enable_record_push_button_clicked();
};

#endif // DATA_SERVE_RECORD_H

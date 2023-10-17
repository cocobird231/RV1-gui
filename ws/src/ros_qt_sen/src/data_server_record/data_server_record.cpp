#include "data_server_record.h"
#include "./../../ui_data_server_record.h"
#include <QDoubleValidator>
data_server_record::data_server_record(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::data_server_record)
{
    ui->setupUi(this);

    this->data_server_node_ = std::make_shared<data_server_node>("gui_data_server_node");
    this->data_server_node_->get_parameter("samplingStep_ms", this->samplingStep_ms);
    this->data_server_node_->get_parameter("autoSaveTime_s", this->samplingStep_ms);
    this->data_server_node_->get_parameter("enabled_record", this->enabled_record);
    this->data_server_node_->get_parameter("recordTime_s", this->recordTime_s);
    QValidator *doubleValidator = new QDoubleValidator(0, 100000, 3, this);
    ui->lineEdit->setValidator(doubleValidator);
    ui->lineEdit_2->setValidator(doubleValidator);
    ui->lineEdit_3->setValidator(doubleValidator);


    ui->lineEdit->setText(QString::number(this->samplingStep_ms));
    ui->lineEdit_2->setText(QString::number(this->autoSaveTime_s));
    ui->lineEdit_3->setText(QString::number(this->recordTime_s));

    if(this->enabled_record){
        ui->pushButton_4->setText("Disabled Record");
    }else{
        ui->pushButton_4->setText("Enabled Record");
    }

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_sampling_step_push_button_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(on_Auto_save_time_push_button_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(on_record_time_push_button_clicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(on_enable_record_push_button_clicked()));

}

data_server_record::~data_server_record()
{
    delete ui;
}

data_server_record::data_server_node::data_server_node(const std::string& nodeName)
    :rclcpp::Node(nodeName)
{
    this->paramNode_ = std::make_shared<rclcpp::Node>("gui_param_node");
    this->paramClient_ = paramNode_->create_client<rcl_interfaces::srv::SetParametersAtomically>("/V0/dataserver_0_node/set_parameters_atomically");
    // _connToService(this->paramClient_);
}

void data_server_record::data_server_node::_connToService(rclcpp::ClientBase::SharedPtr client)
{
    while(!client->wait_for_service(std::chrono::seconds(1))){
        if(!rclcpp::ok()){
            RCLCPP_ERROR(this->get_logger(), "client interrupted while waiting for service to appear.");
        }
        RCLCPP_INFO(this->get_logger(), "waiting for service to appear...");
    }
}

bool data_server_record::data_server_node::_sendRequest(const rcl_interfaces::msg::Parameter& param)
{
    auto request = std::make_shared<rcl_interfaces::srv::SetParametersAtomically::Request>();
    request->parameters.push_back(param);
    auto future = this->paramClient_->async_send_request(request);
#if ROS_DISTRO == 0
        if (rclcpp::spin_until_future_complete(this->paramNode_, future, 10s) != rclcpp::executor::FutureReturnCode::SUCCESS)
#else
        if (rclcpp::spin_until_future_complete(this->paramNode_, future, 10s) != rclcpp::FutureReturnCode::SUCCESS)
#endif
    {
        RCLCPP_ERROR(this->get_logger(), "service call failed :(");
        return false;
    }
    auto result = future.get();
    if(result->result.successful){
        RCLCPP_INFO(this->get_logger(), "set parameter successfully");
        return true;
    }
    else{
        RCLCPP_ERROR(this->get_logger(), "set parameter failed");
        return false;
    }
}

void data_server_record::on_sampling_step_push_button_clicked()
{
    this->samplingStep_ms = ui->lineEdit->text().toDouble();
    rcl_interfaces::msg::Parameter param;
    param.name = "samplingStep_ms";
    param.value.type = rcl_interfaces::msg::ParameterType::PARAMETER_DOUBLE;
    param.value.integer_value = this->samplingStep_ms;
    this->data_server_node_->_sendRequest(param);
}
void data_server_record::on_Auto_save_time_push_button_clicked()
{
    this->autoSaveTime_s = ui->lineEdit_2->text().toDouble();
    rcl_interfaces::msg::Parameter param;
    param.name = "autoSaveTime_s";
    param.value.type = rcl_interfaces::msg::ParameterType::PARAMETER_DOUBLE;
    param.value.integer_value = this->autoSaveTime_s;
    this->data_server_node_->_sendRequest(param);
}
void data_server_record::on_record_time_push_button_clicked()
{
    this->recordTime_s = ui->lineEdit_3->text().toDouble();
    rcl_interfaces::msg::Parameter param;
    param.name = "recordTime_s";
    param.value.type = rcl_interfaces::msg::ParameterType::PARAMETER_DOUBLE;
    param.value.integer_value = this->recordTime_s;
    this->data_server_node_->_sendRequest(param);
}

void data_server_record::on_enable_record_push_button_clicked()
{
    if(ui->pushButton_4->text()=="Enabled Record"){
        ui->pushButton_4->setText("Disabled Record");
        this->enabled_record = true;
    }else{
        ui->pushButton_4->setText("Enabled Record");
        this->enabled_record = false;
    }


    rcl_interfaces::msg::Parameter param;
    param.name = "enabled_record";
    param.value.type = rcl_interfaces::msg::ParameterType::PARAMETER_BOOL;
    param.value.bool_value = this->enabled_record;
    this->data_server_node_->_sendRequest(param);
}
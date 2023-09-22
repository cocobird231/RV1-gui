#include "qosdevicedialog.h"
#include <random>
#include "vehicle_interfaces/qos.h"
#include "vehicle_interfaces/params.h"
#include <thread>

#include "./../../ui_qosdevicedialog.h"

std::shared_ptr<std::thread> Qos_thread;

QosDeviceDialog::QosDeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QosDeviceDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("QoS模式設定");
    connect(ui->pushButton_5,&QPushButton::clicked,this,&QosDeviceDialog::on_update_topic_name_push_button_clicked);
    connect(ui->comboBox,&QComboBox::currentTextChanged,this,&QosDeviceDialog::on_current_topic_name_choose);

    // Qos_thread = std::make_shared<std::thread>(std::bind(&QosDeviceDialog::Qos_execut,this));
    // Qos_thread->detach();
    auto params = std::make_shared<vehicle_interfaces::GenericParams>("qoscontrol_params_node");
    auto control = std::make_shared<QoSControlNode>("qoscontrol_0_node", params->qosService);

}

QosDeviceDialog::~QosDeviceDialog()
{
    delete ui;
}
// void QosDeviceDialog::Qos_execut(){
//     rclcpp::init(0, NULL);
//     bool stopF =false;

//     rclcpp::executors::SingleThreadedExecutor* exec = new rclcpp::executors::SingleThreadedExecutor();
//         while (stopF)
//         std::this_thread::sleep_for(500ms);

//     std::random_device rd_;
//     std::mt19937 gen_{rd_()};

//     while (!stopF)
//     {

//     }
//     rclcpp::shutdown();
// }
void QosDeviceDialog::on_update_topic_name_push_button_clicked(){
    ui->comboBox->clear();
    name_node =rclcpp::Node::make_shared("get_name_on_qos");
    auto topic_name_map = name_node->get_topic_names_and_types();;
    QList<QString> topic_list;
    for(const auto& i :topic_name_map){
        topic_list.append(QString::fromStdString(i.first));
    }
    ui->comboBox->addItems(topic_list);
}
void QosDeviceDialog::on_save_qos_profile_push_button_clicked(){

}
void QosDeviceDialog::on_clear_qos_profile_push_button_clicked(){

}
void QosDeviceDialog::on_remove_qos_profile_push_button_clicked(){

}

void QosDeviceDialog::on_add_qos_profile_push_button_clicked(){

}
void QosDeviceDialog::on_current_topic_name_choose(const QString &text){

}


QosDeviceDialog::QoSControlNode::QoSControlNode(const std::string& nodeName, const std::string& qosServiceName) : rclcpp::Node(nodeName){
        this->regClientNode_ = rclcpp::Node::make_shared(nodeName + "_qosreg_client");
        this->regClient_ = this->regClientNode_->create_client<vehicle_interfaces::srv::QosReg>(qosServiceName + "_Reg");

        this->reqClientNode_ = rclcpp::Node::make_shared(nodeName + "_qosreq_client");
        this->reqClient_ = this->reqClientNode_->create_client<vehicle_interfaces::srv::QosReq>(qosServiceName + "_Req");

        this->paramNode_ = rclcpp::Node::make_shared(nodeName + "_qosparam_client");
        this->paramClient_ = this->paramNode_->create_client<rcl_interfaces::srv::SetParametersAtomically>("qosserver_0_node/set_parameters_atomically");
        RCLCPP_INFO(this->get_logger(), "[QoSControlNode] Constructed");
}

bool QosDeviceDialog::QoSControlNode::requestQosReg(const std::shared_ptr<vehicle_interfaces::srv::QosReg::Request>& req){
    RCLCPP_INFO(this->get_logger(), "[QoSControlNode::requestQosReg]");
    auto result = this->regClient_->async_send_request(req);
    #if ROS_DISTRO == 0
        if (rclcpp::spin_until_future_complete(this->regClientNode_, result, 100ms) == rclcpp::executor::FutureReturnCode::SUCCESS)
    #else
        if (rclcpp::spin_until_future_complete(this->regClientNode_, result, 100ms) == rclcpp::FutureReturnCode::SUCCESS)
    #endif
        {
            auto res = result.get();
            RCLCPP_INFO(this->get_logger(), "[QoSControlNode::regQoSRequest] Request: %d, qid: %ld", res->response, res->qid);
            return res->response;
        }
    RCLCPP_INFO(this->get_logger(), "[QoSControlNode::requestQosReg] Request failed.");
    return false;

}


bool QosDeviceDialog::QoSControlNode::setParam(const rcl_interfaces::msg::Parameter& param){
    auto request = std::make_shared<rcl_interfaces::srv::SetParametersAtomically::Request>();
    request->parameters.push_back(param);
    auto result = this->paramClient_->async_send_request(request);
    #if ROS_DISTRO == 0
        if (rclcpp::spin_until_future_complete(this->paramNode_, result, 10s) == rclcpp::executor::FutureReturnCode::SUCCESS)
    #else
        if (rclcpp::spin_until_future_complete(this->paramNode_, result, 10s) == rclcpp::FutureReturnCode::SUCCESS)
    #endif
        {
            auto response = result.get();
            RCLCPP_INFO(this->get_logger(), "[QoSControlNode::setParam] Request: %d, reason: %s", 
                response->result.successful, response->result.reason.c_str());
            return response->result.successful;
        }
    RCLCPP_INFO(this->get_logger(), "[QoSControlNode::setParam] Request failed.");
    return false;
	
}

bool QosDeviceDialog::QoSControlNode::requestQosReq(const std::string& topicName, rmw_qos_profile_t& outQoSProfile){

    auto request = std::make_shared<vehicle_interfaces::srv::QosReq::Request>();
    request->topic_name = topicName;
    auto result = this->reqClient_->async_send_request(request);
    #if ROS_DISTRO == 0
        if (rclcpp::spin_until_future_complete(this->reqClientNode_, result, 100ms) == rclcpp::executor::FutureReturnCode::SUCCESS)
    #else
        if (rclcpp::spin_until_future_complete(this->reqClientNode_, result, 100ms) == rclcpp::FutureReturnCode::SUCCESS)
    #endif
        {
            auto res = result.get();
            RCLCPP_INFO(this->get_logger(), "[QoSControlNode::requestQosReq] Response: %d, qid: %ld", res->response, res->qid);
            if (res->response)
            {
                outQoSProfile = vehicle_interfaces::CvtMsgToRMWQoS(res->qos_profile);
                RCLCPP_INFO(this->get_logger(), "[QoSControlNode::requestQosReq] Profile get: %s, %d", 
                    vehicle_interfaces::getQoSProfEnumName(outQoSProfile.reliability).c_str(), outQoSProfile.depth);
            }
            return res->response;
        }
    RCLCPP_INFO(this->get_logger(), "[QoSControlNode::requestQosReq] Request failed.");
    return false;
}
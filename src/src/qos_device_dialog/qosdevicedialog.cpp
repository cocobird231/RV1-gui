#include "qosdevicedialog.h"
#include <random>
#include "vehicle_interfaces/qos.h"
#include "vehicle_interfaces/params.h"
#include <thread>
#include <QDebug>
#include "./../../ui_qosdevicedialog.h"
#include <string>
#include <unistd.h>
#include <QMessageBox>
std::shared_ptr<std::thread> Qos_thread;

std::shared_ptr<QosDeviceDialog::QoSControlNode> control;
std::shared_ptr<vehicle_interfaces::GenericParams> params;
std::map<std::string, std::vector<std::string>> topic_name_map;
QosDeviceDialog::QosDeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QosDeviceDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("QoS模式設定");
    connect(ui->pushButton,&QPushButton::clicked,this,&QosDeviceDialog::on_save_qos_profile_push_button_clicked);

    connect(ui->pushButton_2,&QPushButton::clicked,this,&QosDeviceDialog::on_add_qos_profile_push_button_clicked);
    connect(ui->pushButton_3,&QPushButton::clicked,this,&QosDeviceDialog::on_remove_qos_profile_push_button_clicked);
    connect(ui->pushButton_4,&QPushButton::clicked,this,&QosDeviceDialog::on_clear_qos_profile_push_button_clicked);

    connect(ui->pushButton_5,&QPushButton::clicked,this,&QosDeviceDialog::on_update_topic_name_push_button_clicked);
    connect(ui->pushButton_6,&QPushButton::clicked,this,&QosDeviceDialog::on_enable_publish_push_button_clicked);
    connect(ui->pushButton_7,&QPushButton::clicked,this,&QosDeviceDialog::on_set_publish_push_button_clicked);
    connect(ui->pushButton_8,&QPushButton::clicked,this,&QosDeviceDialog::on_add_for_message_tpye_option_qos_profile_push_button_clicked);
    connect(ui->pushButton_9,&QPushButton::clicked,this,&QosDeviceDialog::on_remove_for_message_tpye_option_qos_profile_push_button_clicked);
    connect(ui->comboBox,&QComboBox::currentTextChanged,this,&QosDeviceDialog::on_current_topic_name_choose);
    connect(ui->checkBox,&QCheckBox::stateChanged,this,&QosDeviceDialog::on_checkBox_change);
    connect(ui->checkBox_2,&QCheckBox::stateChanged,this,&QosDeviceDialog::on_checkBox_change);
    connect(ui->checkBox_3,&QCheckBox::stateChanged,this,&QosDeviceDialog::on_checkBox_change);
    connect(ui->checkBox_4,&QCheckBox::stateChanged,this,&QosDeviceDialog::on_checkBox_change);
    connect(ui->checkBox_5,&QCheckBox::stateChanged,this,&QosDeviceDialog::on_checkBox_change);
    connect(ui->checkBox_6,&QCheckBox::stateChanged,this,&QosDeviceDialog::on_checkBox_change);
    connect(ui->checkBox_7,&QCheckBox::stateChanged,this,&QosDeviceDialog::on_checkBox_change);
    connect(ui->checkBox_8,&QCheckBox::stateChanged,this,&QosDeviceDialog::on_checkBox_change);
    connect(ui->checkBox_9,&QCheckBox::stateChanged,this,&QosDeviceDialog::on_checkBox_change);
    connect(ui->checkBox_10,&QCheckBox::stateChanged,this,&QosDeviceDialog::on_checkBox_change);

    QValidator *UIntDepthValidator = new QIntValidator(0, 999, this);
    ui->lineEdit->setValidator(UIntDepthValidator);
    QValidator *DoubleValidator = new QDoubleValidator(0,100000,7,this);
    ui->lineEdit_2->setValidator(DoubleValidator);
    ui->lineEdit_3->setValidator(DoubleValidator);
    ui->lineEdit_4->setValidator(DoubleValidator);
    ui->lineEdit_5->setValidator(DoubleValidator);


    params = std::make_shared<vehicle_interfaces::GenericParams>("qoscontrol_params_node");
    control = std::make_shared<QoSControlNode>("gui_qos_0_node", "/V0/qos_0");



}

QosDeviceDialog::~QosDeviceDialog()
{
    delete ui;
}

void QosDeviceDialog::on_set_publish_push_button_clicked(){

    auto param = rcl_interfaces::msg::Parameter();
    param.name = "publish_interval_ms";
    param.value.type = rcl_interfaces::msg::ParameterType::PARAMETER_DOUBLE;
    param.value.double_value = std::stod(ui->lineEdit_5->text().toStdString());
    control->setParam(param);
    bool qos_requst_success= control->setParam(param);
    if (!qos_requst_success)
    {
        qDebug()<<"Enable publish request not success.";
    }

}

void QosDeviceDialog::on_enable_publish_push_button_clicked(){

    auto param = rcl_interfaces::msg::Parameter();
    param.name = "enabled_publish";
    param.value.type = rcl_interfaces::msg::ParameterType::PARAMETER_BOOL;
    enable = !enable;
    if (enable)
    {
        ui->pushButton_6->setText("Disable Publish");

    }else{
        ui->pushButton_6->setText("Enable Publish");

    }
    param.value.bool_value = enable;
    bool qos_requst_success= control->setParam(param);
    if (!qos_requst_success)
    {
        qDebug()<<"Enable publish request not success.";
    }
            
}

void QosDeviceDialog::on_update_topic_name_push_button_clicked(){
    ui->comboBox->clear();
    if(name_node== nullptr){
        name_node =rclcpp::Node::make_shared("get_name_on_qos");
    }
    topic_name_map = name_node->get_topic_names_and_types();;
    QList<QString> topic_list;
    for(const auto& i :topic_name_map){
        QString topic_string = QString::fromStdString(i.first);
        if (topic_string.split("/").length()>2)
        {
        topic_list.append(QString::fromStdString(i.first));
        qDebug()<<QString::fromStdString(i.first);   
        }
    
    }
    ui->comboBox->addItems(topic_list);
    
}
void QosDeviceDialog::on_checkBox_change(){

    QList<QString> message_types; 
    if(ui->checkBox->isChecked()){
        message_types.append(ui->checkBox->text());
    }
    if(ui->checkBox_2->isChecked()){
        message_types.append(ui->checkBox_2->text());
    }
    if(ui->checkBox_3->isChecked()){
        message_types.append(ui->checkBox_3->text());
    }
    if(ui->checkBox_4->isChecked()){
        message_types.append(ui->checkBox_4->text());
    }
    if(ui->checkBox_5->isChecked()){
        message_types.append(ui->checkBox_5->text());
    }
    if(ui->checkBox_6->isChecked()){
        message_types.append(ui->checkBox_6->text());
    }
    if(ui->checkBox_7->isChecked()){
        message_types.append(ui->checkBox_7->text());
    }
    if(ui->checkBox_8->isChecked()){
        message_types.append(ui->checkBox_8->text());
    }
    if(ui->checkBox_9->isChecked()){
        message_types.append(ui->checkBox_9->text());
    }
    if(ui->checkBox_10->isChecked()){
        message_types.append(ui->checkBox_10->text());
    }

    QList<QString> containts_node_name_topic_list;
    for(const auto& i :topic_name_map){
        QString topic_name_string =QString::fromStdString(i.first);
        int name_slash_contains = topic_name_string.split("/").length();
        // the name slash contains above 3 is currect formate
        if (name_slash_contains >= 3)
        {
            // qDebug()<<QString(name_slash_contains);
            bool contain_current_text_flag=false;
            for (int j = 0; j < i.second.size(); j++)
            {
                QString node_name =QString::fromStdString(i.second[j]);
                for(QString message_type :message_types){
                    if(node_name.contains(message_type)){
                        contain_current_text_flag = true;
                    }
                }
            }
            if(contain_current_text_flag){
                containts_node_name_topic_list.append(QString::fromStdString(i.first));
            }
        }
    }
    ui->comboBox->clear();
    ui->comboBox->addItems(containts_node_name_topic_list);
}
void QosDeviceDialog::on_save_qos_profile_push_button_clicked(){
    vehicle_interfaces::srv::QosReg::Request req;
    req.save_qmap = true;
    bool qos_requst_success = control->requestQosReg(std::make_shared<vehicle_interfaces::srv::QosReg::Request>(req));
    if (!qos_requst_success)
    {
        qDebug()<<"save requestQosReq not success.";
        QMessageBox SaveMeassage;
        SaveMeassage.setText("儲存失敗");
        SaveMeassage.exec();
    }
}
void QosDeviceDialog::on_clear_qos_profile_push_button_clicked(){
    vehicle_interfaces::srv::QosReg::Request req;
    req.clear_profiles = true;
    bool qos_requst_success = control->requestQosReg(std::make_shared<vehicle_interfaces::srv::QosReg::Request>(req));
    if (!qos_requst_success)
    {
        qDebug()<<"clear requestQosReq not success.";
        QMessageBox ClearMeassage;
        ClearMeassage.setText("清除失敗");
        ClearMeassage.exec();
    }
}
void QosDeviceDialog::on_remove_qos_profile_push_button_clicked(){
        vehicle_interfaces::srv::QosReg::Request req;
        req.topic_name = ui->comboBox->currentText().toStdString();
        req.remove_profile = true;
        bool qos_requst_success = control->requestQosReg(std::make_shared<vehicle_interfaces::srv::QosReg::Request>(req));
        if (!qos_requst_success)
        {
            qDebug()<<"remove requestQosReq not success.";
            QMessageBox RemoveMeassage;
            RemoveMeassage.setText("移除失敗");
            RemoveMeassage.exec();
        }
}

void QosDeviceDialog::on_add_qos_profile_push_button_clicked(){

    vehicle_interfaces::srv::QosReg::Request req;
    req.topic_name = ui->comboBox->currentText().toStdString();
    req.qos_profile.history = ui->comboBox_2->currentIndex();
    req.qos_profile.depth = ui->lineEdit->text().toInt();
    req.qos_profile.reliability = ui->comboBox_3->currentIndex();
    req.qos_profile.durability = ui->comboBox_4->currentIndex();

    req.qos_profile.deadline_ms = ui->lineEdit_2->text().toDouble();
    req.qos_profile.lifespan_ms = ui->lineEdit_3->text().toDouble();
    req.qos_profile.liveliness = ui->comboBox_5->currentIndex();

    req.qos_profile.liveliness_lease_duration_ms = ui->lineEdit_4->text().toDouble();
    bool qos_requst_success = control->requestQosReg(std::make_shared<vehicle_interfaces::srv::QosReg::Request>(req));
    if (!qos_requst_success)
    {
        qDebug()<<"Add requestQosReq not success.";
        QMessageBox AddMeassage;
        AddMeassage.setText("新增失敗");
        AddMeassage.exec();
    }

}
void QosDeviceDialog::on_remove_for_message_tpye_option_qos_profile_push_button_clicked(){


    QList<QString> message_types; 
    if(ui->checkBox->isChecked()){
        message_types.append(ui->checkBox->text());
    }
    if(ui->checkBox_2->isChecked()){
        message_types.append(ui->checkBox_2->text());
    }
    if(ui->checkBox_3->isChecked()){
        message_types.append(ui->checkBox_3->text());
    }
    if(ui->checkBox_4->isChecked()){
        message_types.append(ui->checkBox_4->text());
    }
    if(ui->checkBox_5->isChecked()){
        message_types.append(ui->checkBox_5->text());
    }
    if(ui->checkBox_6->isChecked()){
        message_types.append(ui->checkBox_6->text());
    }
    if(ui->checkBox_7->isChecked()){
        message_types.append(ui->checkBox_7->text());
    }
    if(ui->checkBox_8->isChecked()){
        message_types.append(ui->checkBox_8->text());
    }
    if(ui->checkBox_9->isChecked()){
        message_types.append(ui->checkBox_9->text());
    }
    if(ui->checkBox_10->isChecked()){
        message_types.append(ui->checkBox_10->text());
    }
    for(QString message_type :message_types){
        remove_for_message_type(message_type);
    }

}
void QosDeviceDialog::remove_for_message_type( QString message_type){

    if(name_node== nullptr){
        name_node =rclcpp::Node::make_shared("get_name_on_qos");
    }
    topic_name_map = name_node->get_topic_names_and_types();;
    QList<QString> containts_node_name_topic_list;
    for(const auto& i :topic_name_map){
        QString topic_name_string =QString::fromStdString(i.first);
        int name_slash_contains = topic_name_string.split("/").length();
        // the name slash contains above 3 is currect formate
        if (name_slash_contains >= 3)
        {
            // qDebug()<<QString(name_slash_contains);
            bool contain_current_text_flag=false;
            for (int j = 0; j < i.second.size(); j++)
            {
                QString node_name =QString::fromStdString(i.second[j]);
                if(node_name.contains(message_type)){
                    contain_current_text_flag = true;
                }

            }
            if(contain_current_text_flag || message_type.contains("All")){
                containts_node_name_topic_list.append(QString::fromStdString(i.first));
            }
        }
    }
    for(QString topic :containts_node_name_topic_list){
        vehicle_interfaces::srv::QosReg::Request req;
        req.topic_name = topic.toStdString();
        req.remove_profile = true;
        usleep(100000);
        bool qos_requst_success = control->requestQosReg(std::make_shared<vehicle_interfaces::srv::QosReg::Request>(req));
        if (!qos_requst_success)
        {
            qDebug()<<"remove requestQosReq not success.";
            QMessageBox RemoveMeassage;
            RemoveMeassage.setText("移除失敗");
            RemoveMeassage.exec();
        }
    }
}
void QosDeviceDialog::add_for_message_type( QString message_type){

    if(name_node== nullptr){
        name_node =rclcpp::Node::make_shared("get_name_on_qos");
    }
    topic_name_map = name_node->get_topic_names_and_types();;
    QList<QString> containts_node_name_topic_list;
    for(const auto& i :topic_name_map){
        QString topic_name_string =QString::fromStdString(i.first);
        int name_slash_contains = topic_name_string.split("/").length();
        // the name slash contains above 3 is currect formate
        if (name_slash_contains >= 3)
        {
            // qDebug()<<QString(name_slash_contains);
            bool contain_current_text_flag=false;
            for (int j = 0; j < i.second.size(); j++)
            {
                QString node_name =QString::fromStdString(i.second[j]);
                if(node_name.contains(message_type)){
                    contain_current_text_flag = true;
                }

            }
            if(contain_current_text_flag || message_type.contains("All")){
                containts_node_name_topic_list.append(QString::fromStdString(i.first));
            }
        }
    }
    for(QString topic :containts_node_name_topic_list){

        vehicle_interfaces::srv::QosReg::Request req;
        req.topic_name = topic.toStdString();

        req.qos_profile.history = ui->comboBox_2->currentIndex();
        req.qos_profile.depth = ui->lineEdit->text().toInt();
        req.qos_profile.reliability = ui->comboBox_3->currentIndex();
        req.qos_profile.durability = ui->comboBox_4->currentIndex();

        req.qos_profile.deadline_ms = ui->lineEdit_2->text().toDouble();
        req.qos_profile.lifespan_ms = ui->lineEdit_3->text().toDouble();
        req.qos_profile.liveliness = ui->comboBox_5->currentIndex();

        req.qos_profile.liveliness_lease_duration_ms = ui->lineEdit_4->text().toDouble();


        qDebug()<<"Add"+topic;
        sleep(1);
        bool qos_requst_success = control->requestQosReg(std::make_shared<vehicle_interfaces::srv::QosReg::Request>(req));
        if (!qos_requst_success)
        {
            qDebug()<<"Add"+topic+" requestQosReq not success.";
            QMessageBox AddMeassage;
            AddMeassage.setText("新增失敗");
            AddMeassage.exec();
        }
    }
}

void QosDeviceDialog::on_add_for_message_tpye_option_qos_profile_push_button_clicked(){

    QList<QString> message_types; 
    if(ui->checkBox->isChecked()){
        message_types.append(ui->checkBox->text());
    }
    if(ui->checkBox_2->isChecked()){
        message_types.append(ui->checkBox_2->text());
    }
    if(ui->checkBox_3->isChecked()){
        message_types.append(ui->checkBox_3->text());
    }
    if(ui->checkBox_4->isChecked()){
        message_types.append(ui->checkBox_4->text());
    }
    if(ui->checkBox_5->isChecked()){
        message_types.append(ui->checkBox_5->text());
    }
    if(ui->checkBox_6->isChecked()){
        message_types.append(ui->checkBox_6->text());
    }
    if(ui->checkBox_7->isChecked()){
        message_types.append(ui->checkBox_7->text());
    }
    if(ui->checkBox_8->isChecked()){
        message_types.append(ui->checkBox_8->text());
    }
    if(ui->checkBox_9->isChecked()){
        message_types.append(ui->checkBox_9->text());
    }
    if(ui->checkBox_10->isChecked()){
        message_types.append(ui->checkBox_10->text());
    }
    for(QString message_type :message_types){
        add_for_message_type(message_type);
    }
}
void QosDeviceDialog::on_current_topic_name_choose(const QString &text){
    qDebug()<<text;
    std::string topic_string =text.toStdString();
    rmw_qos_profile_t qos_profile;
    bool response_success = control->requestQosReq(topic_string,qos_profile);
    if(!response_success){
        qDebug()<<"requestQosReq not success.";
        ui->comboBox_2->setCurrentIndex(0);
        ui->lineEdit->setText("");
        ui->comboBox_3->setCurrentIndex(0);
        ui->comboBox_4->setCurrentIndex(0);
        ui->lineEdit_2->setText("");
        ui->lineEdit_3->setText("");
        ui->comboBox_5->setCurrentIndex(0);
        ui->lineEdit_4->setText("");
    }else{
        ui->comboBox_2->setCurrentIndex(qos_profile.history);
        ui->lineEdit->setText(QString::fromStdString(std::to_string(qos_profile.depth)));
        ui->comboBox_3->setCurrentIndex(qos_profile.reliability);
        ui->comboBox_4->setCurrentIndex(qos_profile.durability);
        ui->lineEdit_2->setText(QString::fromStdString(std::to_string(  vehicle_interfaces::CvtRMWTimeToMsg(qos_profile.deadline))));
        ui->lineEdit_3->setText(QString::fromStdString(std::to_string(vehicle_interfaces::CvtRMWTimeToMsg(qos_profile.lifespan))));
        ui->comboBox_5->setCurrentIndex(qos_profile.liveliness);
        ui->lineEdit_4->setText(QString::fromStdString(std::to_string(  vehicle_interfaces::CvtRMWTimeToMsg(qos_profile.liveliness_lease_duration))));
        //set ui 
    }
}


QosDeviceDialog::QoSControlNode::QoSControlNode(const std::string& nodeName, const std::string& qosServiceName) : rclcpp::Node(nodeName){
        this->regClientNode_ = rclcpp::Node::make_shared(nodeName + "_qosreg_client");
        this->regClient_ = this->regClientNode_->create_client<vehicle_interfaces::srv::QosReg>(qosServiceName + "_Reg");

        this->reqClientNode_ = rclcpp::Node::make_shared(nodeName + "_qosreq_client");
        this->reqClient_ = this->reqClientNode_->create_client<vehicle_interfaces::srv::QosReq>(qosServiceName + "_Req");

        this->paramNode_ = rclcpp::Node::make_shared(nodeName + "_qosparam_client");
        this->paramClient_ = this->paramNode_->create_client<rcl_interfaces::srv::SetParametersAtomically>("/V0/qosserver_0_node/set_parameters_atomically");
        RCLCPP_INFO(this->get_logger(), "[QoSControlNode] Constructed");

        // bool stopF = false;
        // vehicle_interfaces::ConnToService(this->regClient_, stopF);
        // vehicle_interfaces::ConnToService(this->reqClient_, stopF);
        // vehicle_interfaces::ConnToService(this->paramClient_, stopF);
}

bool QosDeviceDialog::QoSControlNode::requestQosReg(const std::shared_ptr<vehicle_interfaces::srv::QosReg::Request>& req){
        RCLCPP_INFO(this->get_logger(), "[QoSControlNode::requestQosReg]");
        auto result = this->regClient_->async_send_request(req);
#if ROS_DISTRO == 0
        if (rclcpp::spin_until_future_complete(this->regClientNode_, result, 500ms) == rclcpp::executor::FutureReturnCode::SUCCESS)
#else
        if (rclcpp::spin_until_future_complete(this->regClientNode_, result, 500ms) == rclcpp::FutureReturnCode::SUCCESS)
#endif
        {
            auto res = result.get();
            RCLCPP_INFO(this->get_logger(), "[QoSControlNode::requestQosReg] Request: %d, qid: %ld", res->response, res->qid);
            return res->response;
        }
        QMessageBox TimeOutMeassage;
        TimeOutMeassage.setText("RegService逾期未回覆");
        TimeOutMeassage.exec();
        RCLCPP_INFO(this->get_logger(), "[QoSControlNode::requestQosReg] Request failed.");
        return false;

}


bool QosDeviceDialog::QoSControlNode::setParam(const rcl_interfaces::msg::Parameter& param){
		auto request = std::make_shared<rcl_interfaces::srv::SetParametersAtomically::Request>();
		request->parameters.push_back(param);

		auto result = this->paramClient_->async_send_request(request);
#if ROS_DISTRO == 0
        if (rclcpp::spin_until_future_complete(this->paramNode_, result, 3s) == rclcpp::executor::FutureReturnCode::SUCCESS)
#else
        if (rclcpp::spin_until_future_complete(this->paramNode_, result, 3s) == rclcpp::FutureReturnCode::SUCCESS)
#endif
        {
            auto response = result.get();
            RCLCPP_INFO(this->get_logger(), "[QoSControlNode::setParam] Request: %d, reason: %s", 
                response->result.successful, response->result.reason.c_str());
			return response->result.successful;
        }
        QMessageBox TimeOutMeassage;
        TimeOutMeassage.setText("Param Service逾期未回覆");
        TimeOutMeassage.exec();
        RCLCPP_INFO(this->get_logger(), "[QoSControlNode::setParam] Request failed.");
		return false;

}

bool QosDeviceDialog::QoSControlNode::requestQosReq(const std::string& topicName, rmw_qos_profile_t& outQoSProfile){
        auto request = std::make_shared<vehicle_interfaces::srv::QosReq::Request>();
        request->topic_name = topicName;
        auto result = this->reqClient_->async_send_request(request);
#if ROS_DISTRO == 0
        if (rclcpp::spin_until_future_complete(this->reqClientNode_, result, 1000ms) == rclcpp::executor::FutureReturnCode::SUCCESS)
#else
        if (rclcpp::spin_until_future_complete(this->reqClientNode_, result, 1000ms) == rclcpp::FutureReturnCode::SUCCESS)
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
        QMessageBox TimeOutMeassage;
        TimeOutMeassage.setText("ReqService逾期未回覆");
        TimeOutMeassage.exec();
        RCLCPP_INFO(this->get_logger(), "[QoSControlNode::requestQosReq] Request failed.");
        return false;
}
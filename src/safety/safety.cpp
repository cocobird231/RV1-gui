#include "safety.h"
#include "./../ui_safety.h"
#include <QSvgRenderer>
#include <QDebug>
#include <QPainter> 
#include <QFile>
#include <rclcpp/rclcpp.hpp>
#include <thread>
#include <chrono>
#include <functional>
#include <cstdio>
#include <atomic>
#include <unistd.h>
#include "vehicle_interfaces/params.h"

using namespace std::chrono_literals;

std::shared_ptr<safety::SafetyNode> the_safety;
std::shared_ptr<vehicle_interfaces::GenericParams> params_safety;
safety::safety(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::safety)
{
    ui->setupUi(this);

    
    QSvgRenderer render ;
    QFile file("./car.svg"); 
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file); 
        out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl; 
        out << "<svg id=\"圖層_1\" data-name=\"圖層 1\" xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 520.5 489\">" << endl;
        out << "  <defs>" << endl;
        out << "    <style>" << endl;
        out << "      .cls-1 {" << endl;
        out << "        stroke-width: 0px;" << endl;
        out << "      }" << endl;
        out << "    </style>" << endl;
        out << "  </defs>" << endl;
        out << "  <path class=\"cls-1\" d=\"M180.48,178.09c1.94-5.75,4.29-10.3,8.57-13.37,2.48-1.77,3.19-3.76,3.17-6.61-.09-14.25-.01-28.49-.07-42.74-.01-3,.32-5.39,3.98-6.12.88-.17,2.02-2.2,1.97-3.32-.49-12.22,5.5-21.12,14.12-28.91,8.39-7.59,17.76-12.03,29.41-11.72,14.61.39,29.25.45,43.85-.02,12.61-.41,22.4,4.87,31.11,13.18,7.82,7.45,12.96,16.09,12.55,27.37-.04,1.18,1.19,3.19,2.22,3.47,3.11.88,3.71,2.8,3.69,5.61-.06,14.37.02,28.74-.06,43.11-.02,2.82.58,4.85,3.11,6.63,4.31,3.04,6.61,7.63,8.69,13.48-4.66-1.01-8.59-1.89-12.53-2.72-5.24-1.1-5.27-1.09-5.27,4.21,0,36.74,0,73.48-.04,110.22,0,2.59.13,4.5,3.36,5.18,1.12.23,2.57,2.48,2.59,3.82.19,15.62.12,31.24.16,46.86,0,2.66-1.13,4.03-3.75,4.76-1.24.35-2.77,1.72-3.11,2.93-2.08,7.4-6.73,12.12-14.03,14.28-4.91,1.45-9.82,2.9-14.8,4.09-2.51.6-3.48,1.76-3.47,4.36.03,10.37,1.29,9.11-9.56,9.22-2.92.03-6.1-.65-7.29,3.38-.17.59-1.68,1.1-2.57,1.11-8.75.09-17.49.11-26.24.01-.98-.01-2.64-.68-2.8-1.34-.89-3.66-3.65-3.17-6.24-3.17-9.5-.01-8.56.66-8.38-8.46.06-3.21-1.27-4.29-4.14-4.98-5.7-1.36-11.34-2.99-16.94-4.75-6.61-2.07-10.71-6.7-12.45-13.36-.53-2.03-1.32-3.33-3.62-3.54-2.59-.23-3.5-1.98-3.5-4.45.03-15.62.03-31.24.01-46.86,0-2.34.98-3.88,3.33-4.24,2.2-.34,2.78-1.59,2.78-3.65-.04-37.61-.04-75.23,0-112.84,0-2.8-.8-3.9-3.76-3.16-4.34,1.08-8.76,1.89-14.05,3.01ZM263.45,190.53c0,.37,0,.74,0,1.11,14.99,0,29.99-.08,44.98.07,2.91.03,4.22-.77,4.85-3.7,2.13-9.89,4.47-19.73,6.85-29.56.75-3.12.25-5.43-2.98-6.62-6.55-2.4-12.97-5.3-19.7-7.05-14.67-3.81-29.74-3.63-44.73-3.05-14.71.56-29.05,3.06-42.39,9.87-3.13,1.6-4.02,3.61-3.23,6.91,2.34,9.71,4.65,19.44,6.73,29.21.69,3.25,2.19,4.12,5.39,4.01,14.74-.53,29.48-.82,44.23-1.19ZM315.79,324.98c-6.21,7.8-14.36,10.53-22.82,11.53-11.74,1.39-23.62,2.51-35.41,2.28-16.38-.31-33.12-.62-46.46-13.42-3.24,5.63-3.63,11.51-3.29,17.49.4,7.13,3.89,12.16,10.43,15.16,30.3,13.89,60.57,13.92,90.85-.05,6.39-2.95,9.86-7.87,10.31-14.85.39-6.09.11-12.08-3.61-18.14ZM221.19,260.12c0,12.98,0,25.97,0,38.95,0,4.37.02,8.74.08,13.11.03,2.12,1.12,3.14,3.31,3.14,2.12,0,3.32-.86,3.41-3.04.04-1,.08-2,.08-2.99,0-30.59,0-61.18,0-91.76,0-2.75-.05-5.49-.03-8.24.02-2.86-1.57-3.62-4.12-3.39-3.3.29-2.68,2.83-2.69,4.8-.06,16.48-.03,32.96-.04,49.44ZM306.06,261.03c0-12.98,0-25.96,0-38.94,0-4.37-.03-8.74-.09-13.1-.03-2.13-1.14-3.08-3.32-3.11-2.17-.02-3.31.82-3.37,3-.04,1.12-.07,2.25-.07,3.37,0,28.46,0,56.92,0,85.38,0,4.74-.07,9.49.08,14.23.09,3.02,2.79,4.77,5.06,3.13,1.09-.79,1.63-2.96,1.65-4.52.11-16.48.07-32.95.08-49.43ZM326.96,172.77l-1.37-.25c-1.78,3.93-3.56,7.87-5.35,11.8-2.79,6.1-4.13,12.41-3.94,19.22.31,10.97.07,21.96.1,32.94,0,1.43.21,2.85.32,4.34,7.88-1.76,10.44-4.75,10.44-11.75,0-17.35,0-34.69,0-52.04,0-1.42-.12-2.84-.19-4.26ZM201.61,172.59c-.36.06-.72.13-1.09.19-.14.81-.4,1.62-.4,2.42-.02,19.21-.03,38.41.04,57.62,0,1.14.37,2.76,1.16,3.32,2.67,1.89,5.61,3.41,9.14,5.47.17-2.34.36-3.77.37-5.2.02-12.35.06-24.69,0-37.04-.05-10.01-5.53-18.08-9.22-26.78ZM200.52,241.36v49.88c6.12-.92,10.25-4.9,10.29-9.88.08-10.37.07-20.74-.03-31.11-.01-1.25-.41-3.02-1.28-3.64-2.57-1.85-5.47-3.25-8.99-5.25ZM326.81,241.54c-2.21,1.12-3.66,2.03-5.24,2.61-4.3,1.57-5.46,4.56-5.29,9,.33,9.08.07,18.19.12,27.28.03,5.82,4.12,10.12,10.41,10.72v-49.62ZM200.4,331.49c8.91-6.4,14.11-29.09,9.36-40.3-1.41.74-2.76,1.58-4.21,2.17-4.21,1.72-5.83,4.54-5.58,9.28.44,8.2.11,16.45.13,24.68,0,1.29.17,2.58.29,4.17ZM317.22,291.65c-4.38,11.39.6,33.12,9.52,39.7.16-1.7.41-3.1.41-4.5.03-7.86.01-15.71.01-23.57,0-7.03-2.62-10.09-9.94-11.64ZM263.21,222.85v-.02c10.1,0,20.21.07,30.31-.08,1.32-.02,2.63-1.18,3.95-1.81-1.29-.66-2.56-1.36-3.87-1.97-.31-.14-.74-.03-1.11-.03-19.34,0-38.67,0-58.01,0-.99,0-2.06-.08-2.96.25-.69.25-1.58,1.07-1.61,1.67-.02.57.86,1.5,1.52,1.71,1.03.34,2.21.26,3.33.26,9.48.02,18.96,0,28.44,0ZM263.65,300.15c9.73,0,19.46.09,29.18-.09,1.56-.03,3.1-1.2,4.65-1.85-1.56-.65-3.11-1.3-4.67-1.94-.11-.04-.25,0-.37,0-19.2,0-38.41,0-57.61.01-1.24,0-2.51.06-3.69.38-.54.15-1.22,1.03-1.22,1.57,0,.55.67,1.42,1.22,1.59,1.04.32,2.21.32,3.32.33,9.73.02,19.45.01,29.18.01ZM295.36,78.68c-.28.02-.56.03-.84.05-.12.42-.36.86-.33,1.27.95,15.67,1.9,31.35,2.91,47.02.16,2.48.36,5,.96,7.39.21.84,1.67,1.74,2.64,1.85.53.06,1.67-1.42,1.78-2.3.22-1.7.04-3.49-.19-5.21-1.74-13.22-3.52-26.43-5.32-39.64-.48-3.48-1.07-6.95-1.62-10.42ZM232.99,79.39c-.34-.04-.68-.07-1.01-.11-.28,1.18-.67,2.35-.83,3.54-1.89,13.7-3.77,27.41-5.58,41.12-.42,3.21-.76,6.45-.8,9.67-.01.93,1.16,1.88,1.79,2.82.96-.79,2.14-1.42,2.79-2.41.49-.74.3-1.93.37-2.92.7-10.07,1.42-20.15,2.07-30.23.46-7.16.81-14.33,1.2-21.49Z\"/></svg>" << endl;
        file.close(); 
    }
    

    bool load = render.load(QString("./car.svg"));
    qDebug() << "load = " << load;

    QSize size = render.defaultSize();
    QPixmap *pix = new QPixmap(size.width(), size.height());
    pix->fill(Qt::transparent);
    
    QPainter *painter = new QPainter(pix);
    render.render(painter);
    ui->label->setPixmap(*pix);
    ui->label->setScaledContents(true);
    ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label->setAlignment(Qt::AlignCenter);

    // left front
    ui->label_2->setText("");
    ui->label_2->setStyleSheet("background-color: #90D151;");
    ui->label_10->setText("");
    ui->label_10->setStyleSheet("background-color: #90D151;");

    // front
    ui->label_3->setText("");
    ui->label_3->setStyleSheet("background-color: #90D151;");

    // right front
    ui->label_4->setText("");
    ui->label_4->setStyleSheet("background-color: #90D151;");
    ui->label_11->setText("");
    ui->label_11->setStyleSheet("background-color: #90D151;");

    // left
    ui->label_5->setText("");
    ui->label_5->setStyleSheet("background-color: #90D151;");

    //right 
    ui->label_6->setText("");
    ui->label_6->setStyleSheet("background-color: #90D151;");

    // left back
    ui->label_7->setText("");
    ui->label_7->setStyleSheet("background-color: #90D151;");
    ui->label_13->setText("");
    ui->label_13->setStyleSheet("background-color: #90D151;");

    // back
    ui->label_8->setText("");
    ui->label_8->setStyleSheet("background-color: #90D151;");

    // right back
    ui->label_9->setText("");
    ui->label_9->setStyleSheet("background-color: #90D151;");
    ui->label_12->setText("");
    ui->label_12->setStyleSheet("background-color: #90D151;");

    params_safety = std::make_shared<vehicle_interfaces::GenericParams>("safetyserver_params_node");
    the_safety = std::make_shared<SafetyNode>("gui_safety_0_node", "/V0/safety_0");

    this->th1 = std::thread(std::bind(&safety::_timer0Callback, this));
    this->th2 = std::thread(std::bind(&safety::_timer1Callback, this));
    this->th1.detach();
    this->th2.detach();
    QObject::connect(&EmpTimmer, &QTimer::timeout,this, &safety::refreshUI);
    EmpTimmer.start(100);

}
void safety::refreshUI(){
    if (emPs[4] > 0.8){
        ui->label_2->setText("");
        ui->label_2->setStyleSheet("background-color: #FF0000;");
        ui->label_10->setText("");
        ui->label_10->setStyleSheet("background-color: #FF0000;");
    }else if(emPs[4] > 0.5){
        ui->label_2->setText("");
        ui->label_2->setStyleSheet("background-color: #FFC000;");
        ui->label_10->setText("");
        ui->label_10->setStyleSheet("background-color: #FFC000;");
    }else{
        ui->label_2->setText("");
        ui->label_2->setStyleSheet("background-color: #90D151;");
        ui->label_10->setText("");
        ui->label_10->setStyleSheet("background-color: #90D151;");
    }

    if (emPs[0] > 0.8){
        ui->label_3->setText("");
        ui->label_3->setStyleSheet("background-color: #FF0000;");
    }else if(emPs[0] > 0.5){
        ui->label_3->setText("");
        ui->label_3->setStyleSheet("background-color: #FFC000;");
    }
    else{
        ui->label_3->setText("");
        ui->label_3->setStyleSheet("background-color: #90D151;");
    }

    if (emPs[5] > 0.8){
        ui->label_4->setText("");
        ui->label_4->setStyleSheet("background-color: #FF0000;");
        ui->label_11->setText("");
        ui->label_11->setStyleSheet("background-color: #FF0000;");
    }else if(emPs[5] > 0.5){
        ui->label_4->setText("");
        ui->label_4->setStyleSheet("background-color: #FFC000;");
        ui->label_11->setText("");
        ui->label_11->setStyleSheet("background-color: #FFC000;");
    }
    else{
        ui->label_4->setText("");
        ui->label_4->setStyleSheet("background-color: #90D151;");
        ui->label_11->setText("");
        ui->label_11->setStyleSheet("background-color: #90D151;");
    }

    if (emPs[2] > 0.8){
        ui->label_5->setText("");
        ui->label_5->setStyleSheet("background-color: #FF0000;");
    }else if(emPs[2] > 0.5){
        ui->label_5->setText("");
        ui->label_5->setStyleSheet("background-color: #FFC000;");
    }
    else{
        ui->label_5->setText("");
        ui->label_5->setStyleSheet("background-color: #90D151;");
    }

    if (emPs[6] > 0.8){
        ui->label_6->setText("");
        ui->label_6->setStyleSheet("background-color: #FF0000;");
    }else if(emPs[6] > 0.5){
        ui->label_6->setText("");
        ui->label_6->setStyleSheet("background-color: #FFC000;");
    }
    else{
        ui->label_6->setText("");
        ui->label_6->setStyleSheet("background-color: #90D151;");
    }

    if (emPs[7] > 0.8){
        ui->label_7->setText("");
        ui->label_7->setStyleSheet("background-color: #FF0000;");
        ui->label_13->setText("");
        ui->label_13->setStyleSheet("background-color: #FF0000;");
    }else if(emPs[7] > 0.5){
        ui->label_7->setText("");
        ui->label_7->setStyleSheet("background-color: #FFC000;");
        ui->label_13->setText("");
        ui->label_13->setStyleSheet("background-color: #FFC000;");
    }
    else{
        ui->label_7->setText("");
        ui->label_7->setStyleSheet("background-color: #90D151;");
        ui->label_13->setText("");
        ui->label_13->setStyleSheet("background-color: #90D151;");
    }

    if (emPs[1] > 0.8){
        ui->label_8->setText("");
        ui->label_8->setStyleSheet("background-color: #FF0000;");
    }else if(emPs[1] > 0.5){
        ui->label_8->setText("");
        ui->label_8->setStyleSheet("background-color: #FFC000;");
    }
    else{
        ui->label_8->setText("");
        ui->label_8->setStyleSheet("background-color: #90D151;");
    }

    if (emPs[3] > 0.8){
        ui->label_9->setText("");
        ui->label_9->setStyleSheet("background-color: #FF0000;");
        ui->label_12->setText("");
        ui->label_12->setStyleSheet("background-color: #FF0000;");
    }else if(emPs[3] > 0.5){
        ui->label_9->setText("");
        ui->label_9->setStyleSheet("background-color: #FFC000;");
        ui->label_12->setText("");
        ui->label_12->setStyleSheet("background-color: #FFC000;");
    }
    else{
        ui->label_9->setText("");
        ui->label_9->setStyleSheet("background-color: #90D151;");
        ui->label_12->setText("");
        ui->label_12->setStyleSheet("background-color: #90D151;");
    }

}
void safety::_timer0Callback(){
        while (true)
        {
        sleep(0.02);
        static std::uniform_real_distribution<> uniDistrib{0.0, 1.0};
        the_safety->setEmergency(this->nodeName_, uniDistrib(this->gen_), safety::EmergencyScoreDirection::FORWARD, 500.0);
        
        }
        

}
void safety::_timer1Callback(){
    while (true)
    {
        sleep(0.1);
        if (the_safety->getEmergency("nearest", this->emPs))
            printf("[SafetyTestNode::_timer1Callback] %1.2f %1.2f %1.2f %1.2f %1.2f %1.2f %1.2f %1.2f\n", 
                    this->emPs[0], this->emPs[1], this->emPs[2], this->emPs[3], this->emPs[4], this->emPs[5], this->emPs[6], this->emPs[7]);
        else
            printf("[SafetyTestNode::_timer1Callback] getEmergency error.\n");
    }
    
}
    
 bool safety::SafetyNode::_regSurroundEmergency(vehicle_interfaces::srv::SafetyReg::Request::SharedPtr request)
    {
        auto result = this->regClient_->async_send_request(request);
#if ROS_DISTRO == 0
        if (rclcpp::spin_until_future_complete(this->regClientNode_, result, 20ms) == rclcpp::executor::FutureReturnCode::SUCCESS)
#else
        if (rclcpp::spin_until_future_complete(this->regClientNode_, result, 20ms) == rclcpp::FutureReturnCode::SUCCESS)
#endif
        {
            auto response = result.get();
            if (response->response)
                return true;
        }
        return false;
    }

 bool safety::SafetyNode::_reqSurroundEmergency(vehicle_interfaces::srv::SafetyReq::Request::SharedPtr request, std::vector<std::string>& deviceIDs, std::vector<vehicle_interfaces::msg::SurroundEmergency>& emergencies)
    {
        auto result = this->reqClient_->async_send_request(request);
#if ROS_DISTRO == 0
        if (rclcpp::spin_until_future_complete(this->reqClientNode_, result, 20ms) == rclcpp::executor::FutureReturnCode::SUCCESS)
#else
        if (rclcpp::spin_until_future_complete(this->reqClientNode_, result, 20ms) == rclcpp::FutureReturnCode::SUCCESS)
#endif
        {
            
            auto response = result.get();

            if (response->response)
            {
                deviceIDs = response->device_id_vec;
                emergencies = response->emergency_scores;
                return true;
            }
        }

        return false;
    }

bool safety::SafetyNode::setEmergency(std::string deviceID, float emP, safety::EmergencyScoreDirection direction, float lifetime_ms = 500.0)
    {
        if (!this->nodeEnableF_)
            return false;
        vehicle_interfaces::msg::SurroundEmergency score;
        score.emergency_percentages[direction] = emP;
        score.lifetime_ms = lifetime_ms;
        auto request = std::make_shared<vehicle_interfaces::srv::SafetyReg::Request>();
        request->device_id_vec.push_back(deviceID);
        request->emergency_scores.push_back(score);
        return this->_regSurroundEmergency(request);
    }

bool safety::SafetyNode:: setEmergency(std::string deviceID, std::array<float, 8> emPs, float lifetime_ms = 500.0)
    {
        if (!this->nodeEnableF_)
            return false;
        vehicle_interfaces::msg::SurroundEmergency score;
        score.emergency_percentages = emPs;
        score.lifetime_ms = lifetime_ms;
        auto request = std::make_shared<vehicle_interfaces::srv::SafetyReg::Request>();
        request->device_id_vec.push_back(deviceID);
        request->emergency_scores.push_back(score);
        return this->_regSurroundEmergency(request);
    }
bool safety::SafetyNode:: setEmergencies(std::map<std::string, vehicle_interfaces::msg::SurroundEmergency> emergencies)
    {
        if (!this->nodeEnableF_)
            return false;
        auto request = std::make_shared<vehicle_interfaces::srv::SafetyReg::Request>();
        for (const auto& [nodeName, emergency] : emergencies)
        {
            request->device_id_vec.push_back(nodeName);
            request->emergency_scores.push_back(emergency);
        }
        return this->_regSurroundEmergency(request);
    }
bool safety::SafetyNode:: getEmergency(std::string deviceID, float& outEmP, EmergencyScoreDirection direction)
    {
        if (!this->nodeEnableF_)
            return false;
        auto request = std::make_shared<vehicle_interfaces::srv::SafetyReq::Request>();
        request->device_id = deviceID;
        std::vector<std::string> resIDs;
        std::vector<vehicle_interfaces::msg::SurroundEmergency> resEmPs;
        try
        {
            if (this->_reqSurroundEmergency(request, resIDs, resEmPs) && resIDs.back() == deviceID)
            {
                outEmP = resEmPs.back().emergency_percentages[direction];
                return true;
            }
        }
        catch(...)
        {
            RCLCPP_ERROR(this->get_logger(), "[SafetyNode::getEmergency] Request %s[%d] error.", deviceID.c_str(), direction);
        }
        return false;
    }
bool safety::SafetyNode:: getEmergency(std::string deviceID, std::array<float, 8>& outEmPs)
    {
        if (!this->nodeEnableF_)
            return false;
        auto request = std::make_shared<vehicle_interfaces::srv::SafetyReq::Request>();
        request->device_id = deviceID;
        std::vector<std::string> resIDs;
        std::vector<vehicle_interfaces::msg::SurroundEmergency> resEmPs;
        try
        {
            bool result = this->_reqSurroundEmergency(request, resIDs, resEmPs);
            if (result && resIDs.back() == deviceID)
            {
                outEmPs = resEmPs.back().emergency_percentages;

                return true;
            }
        }
        catch(...)
        {

            RCLCPP_ERROR(this->get_logger(), "[SafetyNode::getEmergency] Request %s[all] error.", deviceID.c_str());
        }
        return false;
    }
bool safety::SafetyNode::getEmergencies(std::map<std::string, vehicle_interfaces::msg::SurroundEmergency>& emergencies)
    {
        if (!this->nodeEnableF_)
            return false;
        auto request = std::make_shared<vehicle_interfaces::srv::SafetyReq::Request>();
        request->device_id = "all";
        std::vector<std::string> resIDs;
        std::vector<vehicle_interfaces::msg::SurroundEmergency> resEmPs;
        try
        {
            if (this->_reqSurroundEmergency(request, resIDs, resEmPs))
            {
                int sz = resIDs.size();
                for (int i = 0; i < sz; i++)
                {
                    emergencies[resIDs.back()] = resEmPs.back();
                    resIDs.pop_back();
                    resEmPs.pop_back();
                }
                return true;
            }
        }
        catch(...)
        {
            RCLCPP_ERROR(this->get_logger(), "[SafetyNode::getEmergency] Request all[all] error.");
        }
        return false;
    }
safety::SafetyNode::SafetyNode(const std::string& nodeName, const std::string& safetyServiceName) : rclcpp::Node(nodeName)
{
        if (safetyServiceName == "")
        {
            RCLCPP_WARN(this->get_logger(), "[SafetyNode] Ignored.");
            return;
        }
        this->regClientNode_ = rclcpp::Node::make_shared(nodeName + "_safetyreg_client");
        this->regClient_ = this->regClientNode_->create_client<vehicle_interfaces::srv::SafetyReg>(safetyServiceName + "_Reg");

        this->reqClientNode_ = rclcpp::Node::make_shared(nodeName + "_safetyreq_client");
        this->reqClient_ = this->reqClientNode_->create_client<vehicle_interfaces::srv::SafetyReq>(safetyServiceName + "_Req");

        this->nodeEnableF_ = true;
        RCLCPP_INFO(this->get_logger(), "[SafetyNode] Constructed.");
} 

safety::~safety() 
{
    delete ui;
}

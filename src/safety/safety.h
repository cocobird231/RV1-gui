#ifndef SAFETY_H
#define SAFETY_H

#include <QWidget>
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <map>

#include <thread>
#include <mutex>

#include "rclcpp/rclcpp.hpp"
#include "vehicle_interfaces/msg/surround_emergency.hpp"
#include "vehicle_interfaces/srv/safety_reg.hpp"
#include "vehicle_interfaces/srv/safety_req.hpp"

#include "vehicle_interfaces/msg/wheel_state.hpp"
#include <random>
#include <rclcpp/rclcpp.hpp>
#include <QTimer>
namespace Ui {
class safety;
}

class safety : public QWidget
{
    Q_OBJECT

public:
    explicit safety(QWidget *parent = nullptr);
    ~safety();
    enum EmergencyScoreDirection { 
        FORWARD = 0, 
        BACKWARD, 
        LEFT, 
        RIGHT, 
        FORWARD_LEFT, 
        FORWARD_RIGHT, 
        BACKWARD_LEFT, 
        BACKWARD_RIGHT
    };
    std::array<float, 8> emPs;
    class SafetyNode :  public rclcpp::Node
    {
        private:
            std::shared_ptr<rclcpp::Node> regClientNode_;
            rclcpp::Client<vehicle_interfaces::srv::SafetyReg>::SharedPtr regClient_;
            std::shared_ptr<rclcpp::Node> reqClientNode_;
            rclcpp::Client<vehicle_interfaces::srv::SafetyReq>::SharedPtr reqClient_;
            bool _regSurroundEmergency(vehicle_interfaces::srv::SafetyReg::Request::SharedPtr request);
            bool _reqSurroundEmergency(vehicle_interfaces::srv::SafetyReq::Request::SharedPtr request, std::vector<std::string>& deviceIDs, std::vector<vehicle_interfaces::msg::SurroundEmergency>& emergencies);
        public:
            SafetyNode(const std::string& nodeName, const std::string& safetyServiceName);
            bool setEmergency(std::string deviceID, float emP, safety::EmergencyScoreDirection direction, float lifetime_ms );
            bool setEmergency(std::string deviceID, std::array<float, 8> emPs, float lifetime_ms);
            bool setEmergencies(std::map<std::string, vehicle_interfaces::msg::SurroundEmergency> emergencies);
            bool getEmergency(std::string deviceID, float& outEmP, safety::EmergencyScoreDirection direction);
            bool getEmergency(std::string deviceID, std::array<float, 8>& outEmPs);
            bool getEmergencies(std::map<std::string, vehicle_interfaces::msg::SurroundEmergency>& emergencies);
            std::atomic<bool> nodeEnableF_;

    };

    
private:
    Ui::safety *ui;
    void _timer0Callback();
    void _timer1Callback();
    rclcpp::TimerBase::SharedPtr timer0_;
    rclcpp::TimerBase::SharedPtr timer1_;
    std::random_device rd_;
    std::mt19937 gen_{rd_()};
    std::string nodeName_;
    QTimer EmpTimmer;
    std::thread th1 , th2;
    void refreshUI();
    };

#endif // SAFETY_H

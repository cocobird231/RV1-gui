#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <map>
#include <set>
#include <random>

#include "rclcpp/rclcpp.hpp"
#include "vehicle_interfaces/msg/distance.hpp"
#include "vehicle_interfaces/msg/environment.hpp"
#include "vehicle_interfaces/msg/gps.hpp"
#include "vehicle_interfaces/msg/id_table.hpp"
#include "vehicle_interfaces/msg/imu.hpp"
#include "vehicle_interfaces/msg/wheel_state.hpp"
#include "vehicle_interfaces/srv/id_server.hpp"
#include "vehicle_interfaces/timesync.h"

#define NODE_PUBLISH_PRINT

class Params : public rclcpp::Node
{
public:
    std::string topic_GPS_nodeName = "gps_publisher_node";
    std::string topic_GPS_topicName = "topic_GPS";
    float topic_GPS_pubInterval = 0.5;
    std::string topic_IMU_nodeName = "imu_publisher_node";
    std::string topic_IMU_topicName = "topic_IMU";
    float topic_IMU_pubInterval = 0.05;
    std::string topic_ENV_nodeName = "env_publisher_node";
    std::string topic_ENV_topicName = "topic_ENV";
    float topic_ENV_pubInterval = 1;
    std::string topic_Ultrasound_nodeName = "ultrasound_publisher_node";
    std::string topic_Ultrasound_topicName = "topic_Ultrasound";
    float topic_Ultrasound_pubInterval = 0.05;
    std::string topic_WheelState_nodeName = "wheelstate_publisher_node";
    std::string topic_WheelState_topicName = "topic_WheelState";
    float topic_WheelState_pubInterval = 0.1;
    std::string topic_IDTable_nodeName = "idtable_publisher_node";
    std::string topic_IDTable_topicName = "topic_IDTable";
    float topic_IDTable_pubInterval = 0.5;
    std::string mainNodeName = "sensorsim_node";

private:
    void _getParams()
    {
        this->get_parameter("topic_GPS_nodeName", this->topic_GPS_nodeName);
        this->get_parameter("topic_GPS_topicName", this->topic_GPS_topicName);
        this->get_parameter("topic_GPS_pubInterval", this->topic_GPS_pubInterval);
        this->get_parameter("topic_IMU_nodeName", this->topic_IMU_nodeName);
        this->get_parameter("topic_IMU_topicName", this->topic_IMU_topicName);
        this->get_parameter("topic_IMU_pubInterval", this->topic_IMU_pubInterval);
        this->get_parameter("topic_ENV_nodeName", this->topic_ENV_nodeName);
        this->get_parameter("topic_ENV_topicName", this->topic_ENV_topicName);
        this->get_parameter("topic_ENV_pubInterval", this->topic_ENV_pubInterval);
        this->get_parameter("topic_Ultrasound_nodeName", this->topic_Ultrasound_nodeName);
        this->get_parameter("topic_Ultrasound_topicName", this->topic_Ultrasound_topicName);
        this->get_parameter("topic_Ultrasound_pubInterval", this->topic_Ultrasound_pubInterval);
        this->get_parameter("topic_WheelState_nodeName", this->topic_WheelState_nodeName);
        this->get_parameter("topic_WheelState_topicName", this->topic_WheelState_topicName);
        this->get_parameter("topic_WheelState_pubInterval", this->topic_WheelState_pubInterval);
        this->get_parameter("topic_IDTable_nodeName", this->topic_IDTable_nodeName);
        this->get_parameter("topic_IDTable_topicName", this->topic_IDTable_topicName);
        this->get_parameter("topic_IDTable_pubInterval", this->topic_IDTable_pubInterval);
        this->get_parameter("mainNodeName", this->mainNodeName);
    }

public:
    Params(std::string nodeName) : Node(nodeName)
    {
        this->declare_parameter<std::string>("topic_GPS_nodeName", this->topic_GPS_nodeName);
        this->declare_parameter<std::string>("topic_GPS_topicName", this->topic_GPS_topicName);
        this->declare_parameter<float>("topic_GPS_pubInterval", this->topic_GPS_pubInterval);
        this->declare_parameter<std::string>("topic_IMU_nodeName", this->topic_IMU_nodeName);
        this->declare_parameter<std::string>("topic_IMU_topicName", this->topic_IMU_topicName);
        this->declare_parameter<float>("topic_IMU_pubInterval", this->topic_IMU_pubInterval);
        this->declare_parameter<std::string>("topic_ENV_nodeName", this->topic_ENV_nodeName);
        this->declare_parameter<std::string>("topic_ENV_topicName", this->topic_ENV_topicName);
        this->declare_parameter<float>("topic_ENV_pubInterval", this->topic_ENV_pubInterval);
        this->declare_parameter<std::string>("topic_Ultrasound_nodeName", this->topic_Ultrasound_nodeName);
        this->declare_parameter<std::string>("topic_Ultrasound_topicName", this->topic_Ultrasound_topicName);
        this->declare_parameter<float>("topic_Ultrasound_pubInterval", this->topic_Ultrasound_pubInterval);
        this->declare_parameter<std::string>("topic_WheelState_nodeName", this->topic_WheelState_nodeName);
        this->declare_parameter<std::string>("topic_WheelState_topicName", this->topic_WheelState_topicName);
        this->declare_parameter<float>("topic_WheelState_pubInterval", this->topic_WheelState_pubInterval);
        this->declare_parameter<std::string>("topic_IDTable_nodeName", this->topic_IDTable_nodeName);
        this->declare_parameter<std::string>("topic_IDTable_topicName", this->topic_IDTable_topicName);
        this->declare_parameter<float>("topic_IDTable_pubInterval", this->topic_IDTable_pubInterval);
        this->declare_parameter<std::string>("mainNodeName", this->mainNodeName);
        this->_getParams();
    }
};

class SimulatorNode : public rclcpp::Node
{
private:
    rclcpp::Publisher<vehicle_interfaces::msg::GPS>::SharedPtr gpsPub_;
    rclcpp::Publisher<vehicle_interfaces::msg::IMU>::SharedPtr imuPub_;
    rclcpp::Publisher<vehicle_interfaces::msg::Environment>::SharedPtr envPub_;
    rclcpp::Publisher<vehicle_interfaces::msg::Distance>::SharedPtr ultrasoundPub_;
    rclcpp::Publisher<vehicle_interfaces::msg::WheelState>::SharedPtr wsPub_;
    rclcpp::Publisher<vehicle_interfaces::msg::IDTable>::SharedPtr idtablePub_;

    Timer* gpsTimer_;
    Timer* imuTimer_;
    Timer* envTimer_;
    Timer* ultrasoundTimer_;
    Timer* wsTimer_;
    Timer* idtableTimer_;

    std::string nodeName_;
    
    std::random_device rd_;
    std::mt19937 gen_{rd_()};

private:
    void _gpsTimerCallback()
    {
        static std::normal_distribution<> gaussDistrib{0, 0.02};

        static float lat = 25.033637;
        static float lon = 121.521235;

        lat += gaussDistrib(this->gen_) * 0.1;
        lon += gaussDistrib(this->gen_) * 0.1;
        
        static uint64_t frameCnt = 0;
        auto msg = vehicle_interfaces::msg::GPS();
        msg.header.priority = vehicle_interfaces::msg::Header::PRIORITY_SENSOR;
        msg.header.device_type = vehicle_interfaces::msg::Header::DEVTYPE_GPS;
        msg.header.device_id = this->nodeName_;
        msg.header.frame_id = frameCnt++;
        msg.header.stamp_type = vehicle_interfaces::msg::Header::STAMPTYPE_NONE_UTC_SYNC;
        msg.header.stamp = this->get_clock()->now();

        msg.gps_status = vehicle_interfaces::msg::GPS::GPS_STABLE;
        msg.latitude = lat;
        msg.longitude = lon;

        this->gpsPub_->publish(msg);
#ifdef NODE_PUBLISH_PRINT
        RCLCPP_INFO(this->get_logger(), "lat: %f\tlon: %f", msg.latitude, msg.longitude);
#endif
    }

    void _imuTimerCallback()
    {
        static std::normal_distribution<> gaussDistrib{0, 0.02};

        static std::array<float, 3> acc = {0, 0, 1};
        static std::array<float, 3> gyro = {0, 0, 0};

        for (int i = 0; i < 3; i++)
        {
            acc[i] += gaussDistrib(this->gen_);
            gyro[i] += gaussDistrib(this->gen_);
        }
        
        static uint64_t frameCnt = 0;
        auto msg = vehicle_interfaces::msg::IMU();
        msg.header.priority = vehicle_interfaces::msg::Header::PRIORITY_SENSOR;
        msg.header.device_type = vehicle_interfaces::msg::Header::DEVTYPE_IMU;
        msg.header.device_id = this->nodeName_;
        msg.header.frame_id = frameCnt++;
        msg.header.stamp_type = vehicle_interfaces::msg::Header::STAMPTYPE_NONE_UTC_SYNC;
        msg.header.stamp = this->get_clock()->now();

        msg.unit_type = vehicle_interfaces::msg::IMU::UNIT_ACC_GS | vehicle_interfaces::msg::IMU::UNIT_ROT_DPS;
        msg.linear_acceleration = acc;
        msg.angular_velocity = gyro;

        this->imuPub_->publish(msg);
#ifdef NODE_PUBLISH_PRINT
        RCLCPP_INFO(this->get_logger(), "acc: %f %f %f\tgyro: %f %f %f", msg.linear_acceleration[0], msg.linear_acceleration[1], msg.linear_acceleration[2], 
                                                                        msg.angular_velocity[0], msg.angular_velocity[1], msg.angular_velocity[2]);
#endif
    }

    void _envTimerCallback()
    {
        static std::normal_distribution<> gaussDistrib{0, 0.1};

        static float temp = 25.0;
        static float rh = 50.0;
        static float press = 1013.0;

        temp += gaussDistrib(this->gen_) * 0.5;
        rh += gaussDistrib(this->gen_) * 0.1;
        press += gaussDistrib(this->gen_) * 0.1;
        
        static uint64_t frameCnt = 0;
        auto msg = vehicle_interfaces::msg::Environment();
        msg.header.priority = vehicle_interfaces::msg::Header::PRIORITY_SENSOR;
        msg.header.device_type = vehicle_interfaces::msg::Header::DEVTYPE_ENVIRONMENT;
        msg.header.device_id = this->nodeName_;
        msg.header.frame_id = frameCnt++;
        msg.header.stamp_type = vehicle_interfaces::msg::Header::STAMPTYPE_NONE_UTC_SYNC;
        msg.header.stamp = this->get_clock()->now();

        msg.unit_type = vehicle_interfaces::msg::Environment::UNIT_TEMP_CELSIUS | vehicle_interfaces::msg::Environment::UNIT_PRESS_MBAR;
        msg.temperature = temp;
        msg.relative_humidity = rh;
        msg.pressure = press;

        this->envPub_->publish(msg);
#ifdef NODE_PUBLISH_PRINT
        RCLCPP_INFO(this->get_logger(), "temp: %f\trh: %f\t press: %f", msg.temperature, msg.relative_humidity, msg.pressure);
#endif
    }

    void _ultrasoundTimerCallback()
    {
        static std::normal_distribution<> gaussDistrib{0, 0.1};

        static float dist = 5.0;

        dist += gaussDistrib(this->gen_);
        
        static uint64_t frameCnt = 0;
        auto msg = vehicle_interfaces::msg::Distance();
        msg.header.priority = vehicle_interfaces::msg::Header::PRIORITY_SENSOR;
        msg.header.device_type = vehicle_interfaces::msg::Header::DEVTYPE_ULTRASONIC;
        msg.header.device_id = this->nodeName_;
        msg.header.frame_id = frameCnt++;
        msg.header.stamp_type = vehicle_interfaces::msg::Header::STAMPTYPE_NONE_UTC_SYNC;
        msg.header.stamp = this->get_clock()->now();

        msg.unit_type = vehicle_interfaces::msg::Distance::UNIT_METER;
        msg.min = 0.2;
        msg.max = 8.0;
        msg.distance = dist;

        this->ultrasoundPub_->publish(msg);
#ifdef NODE_PUBLISH_PRINT
        RCLCPP_INFO(this->get_logger(), "dist: %f", msg.distance);
#endif
    }

    void _wsTimerCallback()
    {
        static std::normal_distribution<> gaussDistrib{0, 0.1};

        static int wheelState = 0;
        static int throttle = 100;
        static int gear = vehicle_interfaces::msg::WheelState::GEAR_PARK;
        static int gearStateVar = 1;

        static rclcpp::Time st = this->get_clock()->now();

        if ((this->get_clock()->now() - st).nanoseconds() > 3000000000.0)
        {
            if (gear == vehicle_interfaces::msg::WheelState::GEAR_PARK)
                gearStateVar = 1;
            else if (gear == vehicle_interfaces::msg::WheelState::GEAR_DRIVE)
                gearStateVar = -1;
            gear += gearStateVar;
            st = this->get_clock()->now();
        }

        wheelState += gaussDistrib(this->gen_) * 10;
        throttle += gaussDistrib(this->gen_) * 0.1;
        wheelState = wheelState < -32768 ? -32768 : (wheelState > 32767 ? 32767 : wheelState);
        throttle = throttle < 0 ? 0 : throttle;
        
        static uint64_t frameCnt = 0;
        auto msg = vehicle_interfaces::msg::WheelState();
        msg.header.priority = vehicle_interfaces::msg::Header::PRIORITY_CONTROL;
        msg.header.device_type = vehicle_interfaces::msg::Header::DEVTYPE_STEERINGWHEEL;
        msg.header.device_id = this->nodeName_;
        msg.header.frame_id = frameCnt++;
        msg.header.stamp_type = vehicle_interfaces::msg::Header::STAMPTYPE_NONE_UTC_SYNC;
        msg.header.stamp = this->get_clock()->now();

        msg.gear = gear;
        msg.steering = wheelState;
        msg.pedal_throttle = throttle;
        msg.pedal_brake = 0;
        msg.pedal_clutch = 0;


        this->wsPub_->publish(msg);
#ifdef NODE_PUBLISH_PRINT
        RCLCPP_INFO(this->get_logger(), "%01d|%05d %03d %03d %03d|%03d %03d", msg.gear, 
                                        msg.steering, msg.pedal_throttle, msg.pedal_brake, msg.pedal_clutch, 
                                        msg.button, msg.func);
#endif
    }

    void _idtableTimerCallback()
    {
        static std::uniform_int_distribution<> uniformDistrib{0, 63};

        static std::set<std::string> idSet;

        std::string genID = "device_" + std::to_string(uniformDistrib(this->gen_));

        if (idSet.find(genID) != idSet.end())
            idSet.erase(genID);
        else
            idSet.insert(genID);

        std::vector<std::string> idtable(idSet.begin(), idSet.end());
        
        static uint64_t frameCnt = 0;
        auto msg = vehicle_interfaces::msg::IDTable();
        msg.header.priority = vehicle_interfaces::msg::Header::PRIORITY_INFO;
        msg.header.device_type = vehicle_interfaces::msg::Header::DEVTYPE_IDTABLE;
        msg.header.device_id = this->nodeName_;
        msg.header.frame_id = frameCnt++;
        msg.header.stamp_type = vehicle_interfaces::msg::Header::STAMPTYPE_NONE_UTC_SYNC;
        msg.header.stamp = this->get_clock()->now();

        msg.idtable = idtable;

        this->idtablePub_->publish(msg);
#ifdef NODE_PUBLISH_PRINT
        std::string outputStr = "";
        for (const auto& i : msg.idtable)
            outputStr = outputStr + "\t" + i;
        RCLCPP_INFO(this->get_logger(), "table: %s", outputStr.c_str());
#endif
    }

public:
    SimulatorNode(Params& params) : rclcpp::Node(params.mainNodeName)
    {
        this->nodeName_ = params.mainNodeName;
        if (params.topic_GPS_pubInterval > 0)
        {
            this->gpsPub_ = this->create_publisher<vehicle_interfaces::msg::GPS>(params.topic_GPS_topicName, 10);
            this->gpsTimer_ = new Timer(params.topic_GPS_pubInterval * 1000.0, std::bind(&SimulatorNode::_gpsTimerCallback, this));
            this->gpsTimer_->start();
        }

        if (params.topic_IMU_pubInterval > 0)
        {
            this->imuPub_ = this->create_publisher<vehicle_interfaces::msg::IMU>(params.topic_IMU_topicName, 10);
            this->imuTimer_ = new Timer(params.topic_IMU_pubInterval * 1000.0, std::bind(&SimulatorNode::_imuTimerCallback, this));
            this->imuTimer_->start();
        }

        if (params.topic_ENV_pubInterval > 0)
        {
            this->envPub_ = this->create_publisher<vehicle_interfaces::msg::Environment>(params.topic_ENV_topicName, 10);
            this->envTimer_ = new Timer(params.topic_ENV_pubInterval * 1000.0, std::bind(&SimulatorNode::_envTimerCallback, this));
            this->envTimer_->start();
        }

        if (params.topic_Ultrasound_pubInterval > 0)
        {
            this->ultrasoundPub_ = this->create_publisher<vehicle_interfaces::msg::Distance>(params.topic_Ultrasound_topicName, 10);
            this->ultrasoundTimer_ = new Timer(params.topic_Ultrasound_pubInterval * 1000.0, std::bind(&SimulatorNode::_ultrasoundTimerCallback, this));
            this->ultrasoundTimer_->start();
        }

        if (params.topic_WheelState_pubInterval > 0)
        {
            this->wsPub_ = this->create_publisher<vehicle_interfaces::msg::WheelState>(params.topic_WheelState_topicName, 10);
            this->wsTimer_ = new Timer(params.topic_WheelState_pubInterval * 1000.0, std::bind(&SimulatorNode::_wsTimerCallback, this));
            this->wsTimer_->start();
        }

        if (params.topic_IDTable_pubInterval > 0)
        {
            this->idtablePub_ = this->create_publisher<vehicle_interfaces::msg::IDTable>(params.topic_IDTable_topicName, 10);
            this->idtableTimer_ = new Timer(params.topic_IDTable_pubInterval * 1000.0, std::bind(&SimulatorNode::_idtableTimerCallback, this));
            this->idtableTimer_->start();
        }
    }
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    Params params("sensorsim_params_node");
    auto simNode = std::make_shared<SimulatorNode>(params);
    rclcpp::spin(simNode);
    return EXIT_SUCCESS;
}
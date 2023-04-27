#ifndef SENSORMODEL_H
#define SENSORMODEL_H

#include <string>
using namespace std;

//It just bulid for All sensor interface to implement the model.
namespace SensorModel {

//It is for header field.
class SensorsBaseClass
{
public:
    int priority =0;
    int device_type =0;
    string device_id="";
    int stamp_type =0;
    double stamp_sec =0;

};
// And it is for Data field with sensor.
//for ultrasonic sensor for distance.
class Distance :public SensorsBaseClass
{
public:
    int unit_type = 1;
    float min=0;
    float max=0;
    float distance=0;

};

class Environment:public SensorsBaseClass
{
public:
    int unit_type = 0;
    float temperature;
    float relative_humidity;
    float pressure;
};

class GPS:public SensorsBaseClass
{
public:
    int gps_status = 0;
    float latitude = 0;
    float longitude = 0;

};
class IMU:public SensorsBaseClass
{
public:
    int unit_type;
    float orientation[4];
    float angular_velocity[3];
    float linear_acceleration[3];
};

class MotorAxle:public SensorsBaseClass
{
public:
    int dir;
    float pwm;
    int parking;

};
class MotorSteering:public SensorsBaseClass
{
public:
    int unit_type = 0;
    float min;
    float max;
    float center;
    float value;
};

class WheelState:public SensorsBaseClass
{
public:
    int gear = 0;
    int steering = 0;
    int pedal_throttle = 0;
    int pedal_brake = 0;
    int pedal_clutch = 0;
    int button = 0;
    int func = 0;
};

}
#endif

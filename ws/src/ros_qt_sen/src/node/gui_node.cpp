#include"../include/ros_qt_sen/gui_node.h"
#include <string>
#include<QDebug>
using std::placeholders::_1;

gui_node::gui_node()

{
    node = rclcpp::Node::make_shared("gui_subscriber");
    topic_Ultrasound_subscription_ = node->create_subscription<vehicle_interfaces::msg::Distance>("topic_Ultrasound", 10, std::bind(&gui_node::topic_Ultrasound_callback, this, _1));
    topic_Environment_subscription_=node->create_subscription<vehicle_interfaces::msg::Environment>("topic_ENV", 10, std::bind(&gui_node::topic_env_callback, this, _1));
}
void gui_node::run(){

    rclcpp::WallRate loop_rate(30);
    while(rclcpp:: ok()){

        rclcpp::spin_some(node);
        loop_rate.sleep();
    }


}

void gui_node::topic_env_callback(const vehicle_interfaces::msg::Environment::SharedPtr environment ){

    env_dataCount++;
    temperature_points.append(QPointF((double)env_dataCount,environment->temperature));
    relative_humidity_points.append(QPointF((double)env_dataCount,environment->relative_humidity));
    pressure_points.append(QPointF((double)env_dataCount,environment->pressure));
    if (env_dataCount > 100)
    {
        for(int i= 0;i<env_dataCount;i++){

            temperature_points[i].setX(temperature_points[i].x() - 1.0);
            relative_humidity_points[i].setX(relative_humidity_points[i].x() - 1.0);
            pressure_points[i].setX(pressure_points[i].x() - 1.0);

        }
        temperature_points.pop_front();
        relative_humidity_points.pop_front();
        pressure_points.pop_front();
        env_dataCount=env_dataCount-1;
    }

}

void gui_node:: topic_Ultrasound_callback(const vehicle_interfaces::msg::Distance::SharedPtr distance)
{
    dataCount++;
    Distance_points.append(QPointF((double)dataCount,distance->distance));

    if (dataCount > 100)
    {
        for(int i= 0;i<dataCount;i++){

            Distance_points[i].setX(Distance_points[i].x() - 1.0);
        }
        Distance_points.pop_front();
        dataCount=dataCount-1;
    }
}



void gui_node::update(QAbstractSeries *series, int seriesIndex)
{
    if (series) {
        QLineSeries *LineSeries = static_cast<QLineSeries *>(series);
        //topic_Ultrasound
        if(seriesIndex ==0){
        LineSeries->replace(Distance_points);
        }
        //topic_ENV_temperature_points
        if(seriesIndex ==1){
        LineSeries->replace(temperature_points);

        }
        //topic_ENV_relative_humidity_points
        if(seriesIndex ==2){
        LineSeries->replace(relative_humidity_points);
        }
        //topic_ENV_pressure_points
        if(seriesIndex ==3){
        LineSeries->replace(pressure_points);
        }
        //topic_IMU_linear_acceleration_x_points
        if(seriesIndex ==4){
        LineSeries->replace(linear_acceleration_x_points);
        }
        //topic_IMU_linear_acceleration_x_points
        if(seriesIndex ==5){
        LineSeries->replace(linear_acceleration_y_points);
        }
        //topic_IMU_linear_acceleration_z_points
        if(seriesIndex ==6){
        LineSeries->replace(linear_acceleration_z_points);
        }
        //topic_IMU_angular_velocity_x_points
        if(seriesIndex ==7){
        LineSeries->replace(angular_velocity_x_points);
        }
        //topic_IMU_angular_velocity_y_points
        if(seriesIndex ==8){
        LineSeries->replace(angular_velocity_y_points);
        }
        //topic_IMU_angular_velocity_z_points
        if(seriesIndex ==9){
        LineSeries->replace(angular_velocity_z_points);
        }
        
    }
}
void gui_node::handleSceneChanged()
{
    m_dataUpdater.start();
}
void gui_node::updateAllSeries()
{
    //static int frameCount = 0;
    //static QString labelText = QStringLiteral("FPS: %1");

    for (int i = 0; i < m_seriesList.size(); i++){
        update(m_seriesList[i], i);
}
    // frameCount++;
    // int elapsed = m_fpsTimer.elapsed();
    // if (elapsed >= 1000) {
    //     elapsed = m_fpsTimer.restart();
    //     qreal fps = qreal(0.1 * int(10000.0 * (qreal(frameCount) / qreal(elapsed))));
    //     frameCount = 0;
    // }
}

void gui_node::startUpdates(const QList<QLineSeries *> &seriesList)
{
    m_seriesList = seriesList;

    m_dataUpdater.setInterval(0);
    m_dataUpdater.setSingleShot(true);
    QObject::connect(&m_dataUpdater, &QTimer::timeout,
                     this, &gui_node::updateAllSeries);

    m_fpsTimer.start();
    updateAllSeries();
}


gui_node::~gui_node(){

    rclcpp::shutdown();
}
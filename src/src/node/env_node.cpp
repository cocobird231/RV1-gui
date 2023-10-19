#include"../../include/node/env_node.h"
#include <string>
#include<QDebug>
using std::placeholders::_1;

env_node::env_node()

{
    rclcpp::init(0,NULL);
    node = rclcpp::Node::make_shared("gui_subscriber");
    topic_Environment_subscription_=node->create_subscription<vehicle_interfaces::msg::Environment>("topic_ENV", 10, std::bind(&env_node::topic_env_callback, this, _1));
}
void env_node::run(){

    rclcpp::WallRate loop_rate(30);
    while(rclcpp:: ok()){

        rclcpp::spin_some(node);
        loop_rate.sleep();
    }


}

void env_node::topic_env_callback(const vehicle_interfaces::msg::Environment::SharedPtr environment ){

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





void env_node::update(QAbstractSeries *series, int seriesIndex)
{
    if (series) {
        QLineSeries *LineSeries = static_cast<QLineSeries *>(series);

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

        
    }
}
void env_node::handleSceneChanged()
{
    m_dataUpdater.start();
}
void env_node::updateAllSeries()
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

void env_node::startUpdates(const QList<QLineSeries *> &seriesList)
{
    m_seriesList = seriesList;

    m_dataUpdater.setInterval(0);
    m_dataUpdater.setSingleShot(true);
    QObject::connect(&m_dataUpdater, &QTimer::timeout,
                     this, &env_node::updateAllSeries);

    m_fpsTimer.start();
    updateAllSeries();
}


env_node::~env_node(){

    rclcpp::shutdown();
}
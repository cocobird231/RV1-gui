#ifndef GUI_NODE_H
#define GUI_NODE_H
#include <QObject>
#include "rclcpp/rclcpp.hpp"
#include "vehicle_interfaces/msg/distance.hpp"
#include "vehicle_interfaces/msg/environment.hpp"

#include <memory>
#include "sensorModel.h"
#include <string>
#include <QThread>
#include <QtCore/QObject>
#include <QtCharts/QLineSeries>
#include <QtWidgets/QLabel>
#include <QtCore/QElapsedTimer>
#include <QtCore/QTimer>
#include <QtCharts/QChartView>

using namespace QtCharts;
class gui_node : public QThread
{
    Q_OBJECT

public:
    explicit gui_node();
    ~gui_node();
    void startUpdates(const QList<QLineSeries *> &seriesList);

public slots:
    void update(QAbstractSeries *series, int seriesIndex);
    void handleSceneChanged();
    void updateAllSeries();
protected:
    void run();
private:
    void topic_Ultrasound_callback(const vehicle_interfaces::msg::Distance::SharedPtr distance);
    void topic_env_callback(const vehicle_interfaces::msg::Environment::SharedPtr environment );

    rclcpp::Subscription<vehicle_interfaces::msg::Distance>::SharedPtr topic_Ultrasound_subscription_;
    rclcpp::Subscription<vehicle_interfaces::msg::Environment>::SharedPtr topic_Environment_subscription_;



    std::shared_ptr<rclcpp::Node> node;
    //topic_Ultrasound
    QList<QPointF> Distance_points;
    //topic_ENV
    QList<QPointF> temperature_points,relative_humidity_points,pressure_points ;
    //topic_IMU
    QList<QPointF> linear_acceleration_x_points,linear_acceleration_y_points,linear_acceleration_z_points;
    QList<QPointF> angular_velocity_x_points,angular_velocity_y_points ,angular_velocity_z_points ;

    QList<QList<QList<QPointF>>> m_data;
    int m_index;
    QList<QLineSeries *> m_seriesList;
    QLabel *m_fpsLabel;
    QElapsedTimer m_fpsTimer;
    QTimer m_dataUpdater;
    int dataCount = 0;

    int env_dataCount = 0;

};
#endif

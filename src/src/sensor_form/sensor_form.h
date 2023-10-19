#ifndef FORM_H
#define FORM_H
#include "../include/node/gui_node.h"
#include <QtCharts/QLineSeries>
#include <QtWidgets/QLayout>

#include "./../../ui_sensor_form.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsScene>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>

#include <QtCharts/QLogValueAxis>
#include <QDebug>
#include "rclcpp/rclcpp.hpp"
#include <QWidget>

namespace Ui {
class sensor_form;
}

class sensor_form : public QWidget
{
    Q_OBJECT

public:
    explicit sensor_form(QWidget *parent = nullptr);
    ~sensor_form();
    std::shared_ptr<gui_node> node_;
    std::thread ros_spin_thread_;
private:
    Ui::sensor_form *ui;
    gui_node* main_gui_node;
    QList<QPointF> DistanceSeries;
    QLineSeries*  m_series;
    QList<QLineSeries *> seriesList;
    QList<QGraphicsScene *> senderList;
    QString test = "";
    QChart* Distance_chart ;
    QChartView* Distance_chartView;
    QChart* temperature_chart ;
    QChartView* temperature_chartView;
    QChart* relative_humidity_chart ;
    QChartView* relative_humidity_chartView;
    QChart* pressure_chart ;
    QChartView* pressure_chartView;
    std::shared_ptr<rclcpp::Node> name_node;
private slots:
    void on_comboBox_currentIndexChanged(const QString&);
    void on_PushButtun_clicked();
};

#endif // FORM_H

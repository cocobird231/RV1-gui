#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "../include/ros_qt_sen/gui_node.h"
#include <QMainWindow>
#include <QtCharts/QLineSeries>
#include <QtWidgets/QLayout>
#include <QGraphicsScene>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
using namespace QtCharts;
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::shared_ptr<gui_node> node_;
    std::thread ros_spin_thread_;

private:
    Ui::MainWindow *ui;
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


private slots:
    void on_comboBox_currentIndexChanged(const QString&);

};
#endif // MAINWINDOW_H

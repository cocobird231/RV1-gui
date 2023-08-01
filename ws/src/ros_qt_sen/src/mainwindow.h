#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qos_device_dialog/qosdevicedialog.h"
#include "sensor_form/sensor_form.h"
#include "install_shell/install_shell.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_QosPushButton_clicked();
    void on_SensorPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QosDeviceDialog *qosdevicedialog = new QosDeviceDialog;
    sensor_form *the_sensor_form = new sensor_form;
    install_shell *the_install_shell = new install_shell;

};
#endif // MAINWINDOW_H

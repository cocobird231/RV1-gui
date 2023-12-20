#include "mainwindow.h"
#include "./../ui_mainwindow.h"
#include <rclcpp/rclcpp.hpp>
#include <thread>
#include <unistd.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_QosPushButton_clicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::on_SensorPushButton_clicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::on_data_server_record_puchButton_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::on_install_shell_PushButton_clicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::on_image_display_PushButton_clicked);
    name_node =rclcpp::Node::make_shared("get_the_name");
    QObject::connect(&timmer, &QTimer::timeout,this, &MainWindow::refresh_topic_name_list);
    QObject::connect(&device_timer, &QTimer::timeout,this, &MainWindow::refresh_device_info);
    device_timer.start(10000);
    timmer.start(1000);
}
MainWindow::~MainWindow()
{
    the_sensor_form->close();
    qosdevicedialog->close();
    the_install_shell->close();
    delete ui;

}
void MainWindow::refresh_device_info()
{
    device_info_message="";
    the_install_shell->reqDevInfo.node_name = "all";
    bool  reqSuccess = the_install_shell->DeviceInforcontrol->reqDeviceInfor(the_install_shell->reqDevInfo,the_install_shell->devInfoVec);
    if(reqSuccess){
        for (const vehicle_interfaces::msg::DevInfo & i : the_install_shell->devInfoVec){
            // qDebug()<<QString::fromStdString(i.hostname)+"／"+QString::fromStdString(i.mac_addr)+"／"+QString::fromStdString(i.ipv4_addr)+"／"+QString::fromStdString(i.node_name);
            device_info_message=device_info_message+QString::fromStdString(i.hostname)+"／"+QString::fromStdString(i.mac_addr)+"／"+QString::fromStdString(i.ipv4_addr)+"／"+QString::fromStdString(i.node_name)+"\n";
        }
        ui->textBrowser_2->setText(device_info_message);
    }
}
void MainWindow::refresh_topic_name_list(){


        // ui->textBrowser->clear();
        this->topic="";
        auto topic_name_list = name_node->get_topic_names_and_types();
        for(const auto& i :topic_name_list){
            this->topic=this->topic +QString::fromStdString(i.first.c_str());
            this->topic=this->topic +"\n";

        }
        ui->textBrowser->setText(this->topic);

}
void MainWindow::on_QosPushButton_clicked(){
    qosdevicedialog->show();
}
void MainWindow::on_SensorPushButton_clicked(){
    the_sensor_form= new sensor_form;
    the_sensor_form->show();
}
void MainWindow::on_data_server_record_puchButton_clicked(){
    the_data_server_record->show();
}
void MainWindow::on_install_shell_PushButton_clicked(){
    the_install_shell->show();
}
void MainWindow::on_image_display_PushButton_clicked(){
    Image_form *the_image_form = new Image_form;
    the_image_form->show();
}
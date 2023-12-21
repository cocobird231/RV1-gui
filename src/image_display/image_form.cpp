#include "image_form.h"
#include "./../ui_image_form.h"
#include <QImage>
#include <vehicle_interfaces/msg/image.hpp>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsView>
#include <QDebug>
#include <thread>
#include <rclcpp/rclcpp.hpp>
#include <opencv2/opencv.hpp>


Image_form::Image_form(QWidget *parent,int image_id) :
    QWidget(parent),
    ui(new Ui::Image_form)
{
    ui->setupUi(this);
    
    node_name = "get_image"+std::to_string(image_id);
    connect(ui->pushButton, &QPushButton::clicked, this, &Image_form::refresh_topic_name_list);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Image_form::connect_image_topic);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &Image_form::on_pushButton_clicked);

}

Image_form::~Image_form()
{
    
    delete ui;
    image_spin.~thread();
}
void Image_form::refresh_topic_name_list(){
    ui->comboBox->clear();
    auto topic_name_list = node->get_topic_names_and_types();
    for(const auto& i :topic_name_list){
        if(QString::fromStdString(i.second[0].c_str()).contains("Image"))
        ui->comboBox->addItem(QString::fromStdString(i.first.c_str()));
    }

}
void Image_form::connect_image_topic(){
    node =rclcpp::Node::make_shared(node_name);

    auto qos = rclcpp::QoS(rclcpp::KeepLast(10));
    qos.best_effort();
    qos.durability_volatile();
    qos.reliable();
    image_sub = node->create_subscription<vehicle_interfaces::msg::Image>(ui->comboBox->currentText().toStdString(), qos, std::bind(&Image_form::image_callback, this, std::placeholders::_1));
    qDebug()<<ui->comboBox->currentText();

    image_spin = std::thread(std::bind(&Image_form::run, this));
    image_spin.detach();
}
void Image_form::run(){

        rclcpp::spin(node);

}
void Image_form::image_callback(const vehicle_interfaces::msg::Image::SharedPtr msg){

    cv::Mat recvMat_,resizedMat_;
    std::vector<uchar> data = msg->data;
    recvMat_ = cv::imdecode(data, 1);
    // resize
    cv::resize(recvMat_,resizedMat_,cv::Size(1280,720));
    // mat to qimage
    QImage image = QImage((const unsigned char*)(resizedMat_.data),resizedMat_.cols,resizedMat_.rows,QImage::Format_RGB888);
    // qimage to qpixmap
    QPixmap pixmap = QPixmap::fromImage(image);
    // qpixmap to qgraphicspixmapitem
    // QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
    // // qgraphicspixmapitem to qgraphicsscene
    // QGraphicsScene *scene = new QGraphicsScene();
    // scene->addItem(item);
    // ui->graphicsView->setScene(scene);
    ui->label->setGeometry(30,110,ui->label->width(),ui->label->height());
    ui->label->setPixmap(pixmap);
}

// stop
void Image_form::on_pushButton_clicked()
{
    image_sub.reset();
    image_spin.~thread();
    node.~__shared_ptr();
}
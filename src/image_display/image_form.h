#ifndef IMAGE_FORM_H
#define IMAGE_FORM_H

#include <QWidget>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <vehicle_interfaces/msg/image.hpp>

namespace Ui {
class Image_form;
}

class Image_form : public QWidget
{
    Q_OBJECT

public:
    explicit Image_form(QWidget *parent = nullptr);
    ~Image_form();
    void image_callback(const vehicle_interfaces::msg::Image::SharedPtr msg);
    void run();
    rclcpp::Subscription<vehicle_interfaces::msg::Image>::SharedPtr image_sub;

private:
    Ui::Image_form *ui;
    // name node
    rclcpp::Node::SharedPtr node;
    QList<std::string>   topic_name_list;
    QString topic;
    std::thread image_spin;

private slots:
    void refresh_topic_name_list();
    void connect_image_topic();
    void on_pushButton_clicked();
};

#endif // IMAGE_FORM_H

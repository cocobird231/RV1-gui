#ifndef INSTALL_DEVICE_INFOR_H
#define INSTALL_DEVICE_INFOR_H

#include <QWidget>
 #include <QProcess>
namespace Ui {
class install_device_infor;
}

class install_device_infor : public QWidget
{
    Q_OBJECT

public:
    explicit install_device_infor(QWidget *parent = nullptr,QString ip_address="",QString user_name="",QString Device_type_URL="",QString infor="");
    ~install_device_infor();

private:
    Ui::install_device_infor *ui;
    QString Ip_address="";
    QString User_name="";
    QString Device_type_URL="";
    
private slots:
    void on_close_push_button_clicked();
    void on_open_expolrer_push_button();

};

#endif // INSTALL_DEVICE_INFOR_H

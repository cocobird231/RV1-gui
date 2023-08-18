#ifndef INSTALL_DEVICE_INFOR_H
#define INSTALL_DEVICE_INFOR_H

#include <QWidget>

namespace Ui {
class install_device_infor;
}

class install_device_infor : public QWidget
{
    Q_OBJECT

public:
    explicit install_device_infor(QWidget *parent = nullptr,QString host_name="",QString infor="");
    ~install_device_infor();

private:
    Ui::install_device_infor *ui;
private slots:
    void on_close_push_button_clicked();
};

#endif // INSTALL_DEVICE_INFOR_H

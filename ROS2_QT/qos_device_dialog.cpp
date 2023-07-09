#include "qos_device_dialog.h"
#include "ui_qos_device_dialog.h"

qos_device_dialog::qos_device_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::qos_device_dialog)
{
    ui->setupUi(this);
}

qos_device_dialog::~qos_device_dialog()
{
    delete ui;
}

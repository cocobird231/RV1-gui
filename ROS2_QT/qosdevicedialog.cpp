#include "qosdevicedialog.h"
#include "ui_qosdevicedialog.h"

QosDeviceDialog::QosDeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QosDeviceDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("QoS模式設定");
}

QosDeviceDialog::~QosDeviceDialog()
{
    delete ui;
}

#ifndef QOS_DEVICE_DIALOG_H
#define QOS_DEVICE_DIALOG_H

#include <QDialog>

namespace Ui {
class qos_device_dialog;
}

class qos_device_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit qos_device_dialog(QWidget *parent = nullptr);
    ~qos_device_dialog();

private:
    Ui::qos_device_dialog *ui;
};

#endif // QOS_DEVICE_DIALOG_H

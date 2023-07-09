#ifndef QOSDEVICEDIALOG_H
#define QOSDEVICEDIALOG_H

#include <QDialog>

namespace Ui {
class QosDeviceDialog;
}

class QosDeviceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QosDeviceDialog(QWidget *parent = nullptr);
    ~QosDeviceDialog();

private:
    Ui::QosDeviceDialog *ui;
};

#endif // QOSDEVICEDIALOG_H

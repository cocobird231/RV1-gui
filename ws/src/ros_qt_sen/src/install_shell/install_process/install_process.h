#ifndef INSTALL_PROCESS_H
#define INSTALL_PROCESS_H

#include <QWidget>

namespace Ui {
class install_process;
}

class install_process : public QWidget
{
    Q_OBJECT

public:
    explicit install_process(QWidget *parent = nullptr,QString host_name="");
    ~install_process();
    void setText(QString contants);

private:
    Ui::install_process *ui;
private:
};

#endif // INSTALL_PROCESS_H

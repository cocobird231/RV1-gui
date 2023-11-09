#ifndef install_common_H
#define install_common_H

#include <QWidget>

namespace Ui {
class install_common;
}

class install_common : public QWidget
{
    Q_OBJECT

public:
    explicit install_common(QWidget *parent = nullptr);
    ~install_common();

private:
    Ui::install_common *ui;
private slots:
    void on_device_select_pushbutton_clicked();
    void on_save_pushbutton_clicked();

};

#endif // install_common_H

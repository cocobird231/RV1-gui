#ifndef INSTALL_OPTION_H
#define INSTALL_OPTION_H

#include <QWidget>

namespace Ui {
class install_option;
}

class install_option : public QWidget
{
    Q_OBJECT

public:
    explicit install_option(QWidget *parent = nullptr,QString mac_address="",QString device="",QString pack_name="",QString interface="",QString ip="");
    ~install_option();

private:
    Ui::install_option *ui;
    QString Mac_address="";
    QString Device="";
    QString Pack_name="";
    QString Interface="";
    QString Ip="";
    bool remove = false;
    bool update = false;
    bool install = false;
    bool preserve =false;
    bool update_depolyment = false;
private slots:
    void on_save_and_close_push_button_clicked();
    void on_close_push_button_clicked();
    void on_reset_push_button_clicked();
};

#endif // INSTALL_OPTION_H

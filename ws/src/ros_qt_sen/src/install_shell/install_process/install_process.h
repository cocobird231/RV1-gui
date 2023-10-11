#ifndef INSTALL_PROCESS_H
#define INSTALL_PROCESS_H

#include <QWidget>
#include <QtCore/QElapsedTimer>
#include <QtCore/QTimer>
namespace Ui {
class install_process;
class thread_install_process;
}

class install_process : public QWidget
{
    Q_OBJECT

public:
    explicit install_process(QWidget *parent = nullptr,std::string user_name="",std::string Password="",std::string host_name="",std::string mac_address="",std::string ip_address="",std::string pack_name="",std::string interface="",std::string ip="",std::string device="",bool remove = false, bool update =false,bool install = false,bool preserve =false,bool update_depolyment=false,bool depoly=false);
    ~install_process();
    void setText(QString contants);
    void depoly(std::string user_name,std::string Password,std::string ip_address,std::string pack_name,std::string interface,std::string ip,std::string device);

private:
    Ui::install_process *ui;
    QString ssh_infor="";
    QTimer timmer;
    std::string device="";
    std::string mac_address = "";
    bool remove = false;
    bool update = false;
    bool install = false;
    bool preserve =false;
    bool update_depolyment = false;
private slots:
    void install_misson(std::string user_name,std::string Password,std::string ip_address,std::string pack_name,std::string interface,std::string ip,std::string device);
    void set_text_broswer();
    void on_close_push_button_clicked();

};


#endif // INSTALL_PROCESS_H

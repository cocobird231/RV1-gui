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
    explicit install_process(QWidget *parent = nullptr,std::string user_name="",std::string Password="",std::string host_name="",std::string mac_address="",std::string ip_address="",std::string pack_name="",std::string interface="",std::string ip="");
    ~install_process();
    void setText(QString contants);

private:
    Ui::install_process *ui;
    QString ssh_infor="";
    QTimer timmer;

private slots:
    void install_misson(std::string user_name,std::string Password,std::string ip_address,std::string pack_name,std::string interface,std::string ip);
    void set_text_broswer();
    void on_close_push_button_clicked();

};


#endif // INSTALL_PROCESS_H

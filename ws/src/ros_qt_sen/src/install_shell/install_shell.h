#ifndef INSTALL_SHELL_H
#define INSTALL_SHELL_H

#include <QWidget>
#include "./../../ui_install_shell.h"
#include<QHostInfo>

#include <netinet/in.h> 
#include <arpa/inet.h>
#include <libssh/libssh.h>
#include <sys/types.h>
namespace Ui {
class install_shell;
}

class install_shell : public QWidget
{
    Q_OBJECT

public:
    explicit install_shell(QWidget *parent = nullptr);
    ~install_shell();

private:
    Ui::install_shell *ui;
    void on_Interface_Update_PushButtun_clicked();
    void on_Interface_Choose_PushButtun_clicked();
    QList<QString> getSubnetList(const QString& ipAddress, const QString& subnetMask);
private slots:
        void lookedUpCallback(const QHostInfo &host);

};

#endif // INSTALL_SHELL_H
